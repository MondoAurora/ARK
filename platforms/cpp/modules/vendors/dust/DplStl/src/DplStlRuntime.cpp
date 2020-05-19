#include "DplStl.h"

#include <iostream>


using namespace std;

DplStlRuntime::DplStlRuntime()
    :store(DUST_LAST_CONST_RUNTIME)
{
}

DplStlRuntime::~DplStlRuntime()
{
}

void DplStlRuntime::setConnector(DustRuntimeConnector* pConn)
{
    pRTC = pConn;
}

DustResultType DplStlRuntime::DustResourceInit()
{
    cout << "Booting runtime" << endl;

    setBootToken(DustUnitMindText::DustTypePlainText, DUST_BOOT_TYPE_PLAINTEXT);

    setBootToken(DustUnitMindModel::DustTypeEntity, DUST_BOOT_TYPE_ENTITY);
    setBootToken(DustUnitMindModel::DustRefGlobalId, DUST_BOOT_REF_GLOBALID);
    setBootToken(DustUnitMindModel::DustRefOwner, DUST_BOOT_REF_OWNER);

    setBootToken(DustUnitMindIdea::DustTypeType, DUST_IDEA_TYPE);
    setBootToken(DustUnitMindIdea::DustTypeMember, DUST_IDEA_MEMBER);
    setBootToken(DustUnitMindIdea::DustTypeAgent, DUST_IDEA_AGENT);
    setBootToken(DustUnitMindIdea::DustTypeConst, DUST_IDEA_CONST);
    setBootToken(DustUnitMindIdea::DustTypeTag, DUST_IDEA_TAG);

    setBootToken(DustUnitMindIdea::DustConstValInteger, DUST_VAL_INTEGER);
    setBootToken(DustUnitMindIdea::DustConstValReal, DUST_VAL_REAL);
    setBootToken(DustUnitMindIdea::DustConstValRef, DUST_VAL_REF);

    setBootToken(DustUnitMindIdea::DustConstCollSet, DUST_COLL_SET);
    setBootToken(DustUnitMindIdea::DustConstCollArr, DUST_COLL_ARR);
    setBootToken(DustUnitMindIdea::DustConstCollMap, DUST_COLL_MAP);

    setBootToken(DustUnitMindNarrative::DustConstResultReject, DUST_RESULT_REJECT);
    setBootToken(DustUnitMindNarrative::DustConstResultRead, DUST_RESULT_READ);
    setBootToken(DustUnitMindNarrative::DustConstResultAccept, DUST_RESULT_ACCEPT);
    setBootToken(DustUnitMindNarrative::DustConstResultAcceptPass, DUST_RESULT_ACCEPT_PASS);
    setBootToken(DustUnitMindNarrative::DustConstResultAcceptRead, DUST_RESULT_ACCEPT_READ);

    setBootToken(DustUnitMindDialog::DustConstAccessGet, DUST_ACCESS_GET);
    setBootToken(DustUnitMindDialog::DustConstAccessSet, DUST_ACCESS_SET);
    setBootToken(DustUnitMindDialog::DustConstAccessMove, DUST_ACCESS_MOVE);
    setBootToken(DustUnitMindDialog::DustConstAccessRemove, DUST_ACCESS_REMOVE);
    setBootToken(DustUnitMindDialog::DustConstAccessClear, DUST_ACCESS_CLEAR);

    return DUST_RESULT_ACCEPT;
}

DustResultType DplStlRuntime::DustResourceRelease()
{
    return DUST_RESULT_ACCEPT;
}

DustEntity DplStlRuntime::getToken(DustEntity parent,  const char* name)
{
    DustEntity txtParent = parent ? DustData::getRef(parent, DUST_BOOT_REF_GLOBALID) : DUST_ENTITY_INVALID;
    return pRTC->getTextToken(txtParent, name);
}

DplStlDataEntity* DplStlRuntime::registerGlobalEntity(DustEntity txtToken, DustEntity primaryType, DustEntity parent, DustEntity constId)
{
    DplStlDataEntity* pEntity = store.getEntity(constId, primaryType);
    DustEntity entity = pEntity->id;
    globalEntites[txtToken] = entity;

    DustData::setRef(entity, DUST_BOOT_REF_GLOBALID, txtToken);
    if ( parent ) {
        DustData::setRef(entity, DUST_BOOT_REF_OWNER, parent);
    }
//    pEntity->changeRef(DUST_ACCESS_SET, DUST_BOOT_REF_GLOBALID, txtToken);
//    if ( parent )
//    {
//        pEntity->changeRef(DUST_ACCESS_SET, DUST_BOOT_REF_OWNER, parent);
//    }

    return pEntity;
}

DustEntity DplStlRuntime::getUnit(const char* name, DustEntity constId)
{
    DustEntity txtToken = getToken(0, name);
    DustEntity unit = findEntity(globalEntites, txtToken);

    if ( !unit )
    {
        DplStlDataEntity* pEntity = registerGlobalEntity(txtToken, DUST_IDEA_UNIT, DUST_ENTITY_INVALID, constId);
        unit = pEntity->id;
    }

    return unit;
}

DustEntity DplStlRuntime::getIdeaEntity(DustEntity unit, const char* name, DustIdeaType ideaType, DustEntity constId)
{
    DustEntity txtToken = getToken(unit, name);
    DustEntity idea = findEntity(globalEntites, txtToken);

    if ( !idea )
    {
        DplStlDataEntity* pEntity = registerGlobalEntity(txtToken, ideaType, unit, constId);
        idea = pEntity->id;
    }

    return idea;
}

DustEntity DplStlRuntime::getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType, DustEntity constId)
{
    DustEntity txtToken = getToken(type, name);
    DustEntity member = findEntity(globalEntites, txtToken);

    if ( !member )
    {
        DplStlDataEntity* pEntity = registerGlobalEntity(txtToken, DUST_IDEA_MEMBER, type, constId);
        member = pEntity->id;
    }

    return member;
}


DplStlDataEntity* DplStlRuntime::resolveEntity(DustEntity entity)
{
    return store.getEntity(entity);
}


DustEntity DplStlRuntime::createEntity(DustEntity primaryType)
{
    return store.getEntity(DUST_ENTITY_APPEND, primaryType)->id;
}

long DplStlRuntime::getMemberCount(DustEntity entity, DustEntity token)
{
    long c = 0;

    DplStlDataEntity *pEntity = resolveEntity(entity);
    if ( pEntity )
    {
        DplStlDataVariant *pVar = pEntity->getVariant(token, false);
        if ( pVar )
        {
            c = pVar->collection ? pVar->collection->size() : 1;
        }
    }

    return c;
}

DustEntity DplStlRuntime::getMemberKey(DustEntity entity, DustEntity token, long idx)
{
    DustEntity key = DUST_ENTITY_INVALID;

    if ( 0 <= idx )
    {

        DplStlDataEntity *pEntity = resolveEntity(entity);
        if ( pEntity )
        {
            DplStlDataVariant *pVar = pEntity->getVariant(token, false);
            if ( pVar && pVar->collection && ( (unsigned) idx < pVar->collection->size()))
            {
                key = pVar->collection->at(idx)->valRef->eKey;
            }
        }
    }

    return key;
}

bool DplStlRuntime::accessMember(DustAccessData &ad)
{
    DplStlDataEntity *pEntity = resolveEntity(ad.entity);

    return pEntity ? pEntity->access(ad) : false;

//    if ( !pEntity )
//    {
//        return false;
//    }
//
//    DplStlDataVariant *pVar = pEntity->getVariant(ad.token, DUST_ACCESS_SET == ad.access);
//
//    if ( pVar )
//    {
//        if ( DUST_ACCESS_GET == ad.access )
//        {
//            ret = true;
//            switch ( pVar->valType )
//            {
//            case DUST_VAL_INTEGER:
//                ad.valLong = pVar->value.valLong;
//                break;
//            case DUST_VAL_REAL:
//                ad.valDouble = pVar->value.valDouble;
//                break;
//            case DUST_VAL_REF:
//                ad.valLong = pVar->value.valRef->eTarget;
//                break;
//            case DUST_VAL_:
//                ret = false;
//                break;
//            }
//        }
//        else
//        {
//            ret = pEntity->access(ad, pVar);
//        }
//    }
//
//    return ret;
}



void* DplStlRuntime::getNative(DustEntity entity, DustEntity type)
{
    DplStlDataEntity *pEntity = resolveEntity(entity);
    void* ret = mapOptGet(pEntity->native, type);

    if ( !ret )
    {
        DustModule *pMod = pRTC->getModuleForType(type);

        if ( pMod )
        {
            ret = pMod->createNative(type);
            if ( ret )
            {
                pEntity->native[type] = ret;
            }
        }
    }

    return ret;
}

DustResultType DplStlRuntime::DustActionExecute()
{
    return DUST_RESULT_NOTIMPLEMENTED;
}

