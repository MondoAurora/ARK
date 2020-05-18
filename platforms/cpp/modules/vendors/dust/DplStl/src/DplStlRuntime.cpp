#include "DplStl.h"

#include <iostream>


using namespace std;

int ival = 0;


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

    setBootToken(DustUnitMindDialog::DustConstChangeClear, DUST_CHANGE_CLEAR);
    setBootToken(DustUnitMindDialog::DustConstChangeRefSet, DUST_CHANGE_REF_SET);
    setBootToken(DustUnitMindDialog::DustConstChangeRefRemove, DUST_CHANGE_REF_REMOVE);

    return DUST_RESULT_ACCEPT;
}

DustResultType DplStlRuntime::DustResourceRelease()
{
    return DUST_RESULT_ACCEPT;
}

DustEntity DplStlRuntime::getToken(DustEntity parent,  const char* name)
{
    DustEntity txtParent = parent ? getRef(parent, DUST_BOOT_REF_GLOBALID) : DUST_ENTITY_INVALID;
    return pRTC->getTextToken(txtParent, name);
}

DplStlDataEntity* DplStlRuntime::registerGlobalEntity(DustEntity txtToken, DustEntity primaryType, DustEntity parent, DustEntity constId)
{
    DplStlDataEntity* pEntity = store.getEntity(constId, primaryType);
    globalEntites[txtToken] = pEntity->id;

    pEntity->changeRef(DUST_CHANGE_REF_SET, DUST_BOOT_REF_GLOBALID, txtToken);
    if ( parent ) {
        pEntity->changeRef(DUST_CHANGE_REF_SET, DUST_BOOT_REF_OWNER, parent);
    }

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

int DplStlRuntime::getInteger(DustEntity entity, DustEntity token, int defValue)
{
    return ival;
}

double DplStlRuntime::getReal(DustEntity entity, DustEntity token, double defValue)
{
    return 0;
}

void DplStlRuntime::setInteger(DustEntity entity, DustEntity token, int val)
{
    ival = val;
    cout << "test data set to " << val << endl;
}

void DplStlRuntime::setReal(DustEntity entity, DustEntity token, double val)
{
}


long DplStlRuntime::getRefCount(DustEntity entity, DustEntity token)
{
    return 0;
}

DustEntity DplStlRuntime::getRefKey(DustEntity entity, DustEntity token, long idx)
{
    return DUST_ENTITY_INVALID;
}

DustEntity DplStlRuntime::getRef(DustEntity entity, DustEntity token, long key)
{
   DplStlDataEntity *pEntity = resolveEntity(entity);
   DplStlDataVariant *pVar = pEntity->getVariant(DUST_CHANGE_, token);

    return pVar ? pVar->value.valRef->eTarget : DUST_ENTITY_INVALID;
}

bool DplStlRuntime::setRef(DustEntity entity, DustEntity token, DustEntity target, long key)
{
   DplStlDataEntity *pEntity = resolveEntity(entity);

   pEntity->changeRef(DUST_CHANGE_REF_SET, token, target, key);

    return false;
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

