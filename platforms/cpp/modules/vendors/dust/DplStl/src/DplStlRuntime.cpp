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

map<long, DustToken*> bootEntites;
typedef map<long, DustToken*>::iterator BootIterator;

void setBootInfo(DustToken &token, long id)
{
    bootEntites[id] = &token;
}


DustResultType DplStlRuntime::DustResourceInit()
{
    cout << "Booting runtime" << endl;

    setBootInfo(DustUnitMindText::DustTypePlainText, DUST_BOOT_TYPE_PLAINTEXT);

    setBootInfo(DustUnitMindModel::DustTypeEntity, DUST_BOOT_TYPE_ENTITY);
    setBootInfo(DustUnitMindModel::DustRefUnit, DUST_BOOT_REF_UNIT);
    setBootInfo(DustUnitMindModel::DustIntId, DUST_BOOT_INT_ID);
    setBootInfo(DustUnitMindModel::DustRefPrimaryType, DUST_BOOT_REF_PRIMARYTYPE);
    setBootInfo(DustUnitMindModel::DustRefGlobalId, DUST_BOOT_REF_GLOBALID);
    setBootInfo(DustUnitMindModel::DustRefOwner, DUST_BOOT_REF_OWNER);
    setBootInfo(DustUnitMindModel::DustRefTags, DUST_BOOT_REF_TAGS);

    setBootInfo(DustUnitMindIdea::DustTypeType, DUST_IDEA_TYPE);
    setBootInfo(DustUnitMindIdea::DustTypeMember, DUST_IDEA_MEMBER);
    setBootInfo(DustUnitMindIdea::DustTypeAgent, DUST_IDEA_AGENT);
    setBootInfo(DustUnitMindIdea::DustTypeTag, DUST_IDEA_TAG);

    setBootInfo(DustUnitMindIdea::DustConstValInteger, DUST_VAL_INTEGER);
    setBootInfo(DustUnitMindIdea::DustConstValReal, DUST_VAL_REAL);
    setBootInfo(DustUnitMindIdea::DustConstValRef, DUST_VAL_REF);

    setBootInfo(DustUnitMindIdea::DustConstCollSingle, DUST_COLL_SINGLE);
    setBootInfo(DustUnitMindIdea::DustConstCollSet, DUST_COLL_SET);
    setBootInfo(DustUnitMindIdea::DustConstCollArr, DUST_COLL_ARR);
    setBootInfo(DustUnitMindIdea::DustConstCollMap, DUST_COLL_MAP);

    setBootInfo(DustUnitMindNarrative::DustConstResultReject, DUST_RESULT_REJECT);
    setBootInfo(DustUnitMindNarrative::DustConstResultRead, DUST_RESULT_READ);
    setBootInfo(DustUnitMindNarrative::DustConstResultAccept, DUST_RESULT_ACCEPT);
    setBootInfo(DustUnitMindNarrative::DustConstResultAcceptPass, DUST_RESULT_ACCEPT_PASS);
    setBootInfo(DustUnitMindNarrative::DustConstResultAcceptRead, DUST_RESULT_ACCEPT_READ);

    setBootInfo(DustUnitMindDialog::DustConstAccessGet, DUST_ACCESS_GET);
    setBootInfo(DustUnitMindDialog::DustConstAccessSet, DUST_ACCESS_SET);
    setBootInfo(DustUnitMindDialog::DustConstAccessMove, DUST_ACCESS_MOVE);
    setBootInfo(DustUnitMindDialog::DustConstAccessRemove, DUST_ACCESS_REMOVE);
    setBootInfo(DustUnitMindDialog::DustConstAccessClear, DUST_ACCESS_CLEAR);

    for (BootIterator it = bootEntites.begin(); it != bootEntites.end(); ++it)
    {
        DustToken* pT = it->second;
        if ( DUST_IDEA_MEMBER == pT->getIdeaType() )
        {
            store.tokenInfo[it->first] = new DustTokenInfo(pT->getValType(), pT->getCollType());
        }
    }

    for (BootIterator it = bootEntites.begin(); it != bootEntites.end(); ++it)
    {
        setBootToken( *(it->second), it->first);
    }

    bootEntites.clear();

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

    DustAccessData ad(entity, DUST_BOOT_REF_GLOBALID, txtToken);
    pEntity->access(ad);

    if ( parent )
    {
        ad.setValLong(DUST_BOOT_REF_OWNER, parent);
        pEntity->access(ad);
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

        DustAccessData ad(idea, DUST_BOOT_REF_UNIT, unit);
        pEntity->access(ad);
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

        DustEntity unit = DustData::getRef(type, DUST_BOOT_REF_UNIT);
        if ( unit )
        {
            DustAccessData ad(member, DUST_BOOT_REF_UNIT, unit);
            pEntity->access(ad);
        }
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
            c = pVar->pColl ? pVar->pColl->size() : 1;
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
            if ( pVar && pVar->pColl && ( (unsigned) idx < pVar->pColl->size()))
            {
                key = pVar->pColl->at(idx)->valRef->eKey;
            }
        }
    }

    return key;
}

bool DplStlRuntime::accessMember(DustAccessData &ad)
{
    DplStlDataEntity *pEntity = resolveEntity(ad.entity);
    return pEntity ? pEntity->access(ad) : false;
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

