#include "DustRuntime.h"

#include <iostream>

using namespace std;

DustRuntime *apiRuntime = 0;

extern "C" void initModule(DustRuntime *pRuntime)
{
    if (!apiRuntime)
    {
        apiRuntime = pRuntime;
    }
}

void DustModule::registerFactory(DustFactoryLogic *pFactory) {
    DustEntity typeId = pFactory->DustFactoryGetType();
    logicFactories[typeId] = pFactory;

    cout << "registerFactory " << typeId << " id: " << &logicFactories << " count: " << logicFactories.size() << endl;

}

void DustModule::registerAlgorithm(DustEntity agent, DustEntity implRoot) {
    algorithms[agent] = implRoot;
}

bool DustModule::isNativeProvided(DustEntity typeId) {
    cout << "isNativeProvided " << typeId << " id: " << &logicFactories << " count: " << logicFactories.size() << endl;

    return mapContains(logicFactories, typeId);
}
void* DustModule::createNative(DustEntity typeId) {
    DustFactoryLogic *pf = mapOptGet(logicFactories, typeId);
    return pf->DustFactoryCreate();
}
void DustModule::releaseNative(DustEntity typeId, void* pNativeObject) {
    DustFactoryLogic *pf = mapOptGet(logicFactories, typeId);
    return pf->DustFactoryDestroy(pNativeObject);
}
DustResultType DustModule::dispatchCommand(DustEntity typeId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param ){
    DustFactoryLogic *pf = mapOptGet(logicFactories, typeId);
    return pf->DustFactoryDispatch(pLogic, cmd, param);
}


DustToken::operator DustEntity()
{
    if ( DUST_ENTITY_APPEND == entity )
    {
        entity = DustData::getTokenEntity(this);
    }
    return entity;
}


DustRef::DustRef(DustCtxType ctx)
: entity(ctx), pToken(0)
{}
DustRef::operator DustEntity()
{
    return entity ? pToken ? DustData::getRef(entity, *pToken) : entity : DUST_ENTITY_INVALID;
}
DustRef& DustRef::operator >> (DustToken &token)
{
    if ( pToken ) {
        entity = DUST_ENTITY_INVALID;
        pToken = 0;
    } else if ( token.getCollType() == DUST_COLL_SINGLE ) {
        entity = DustData::getRef(entity, token);
    } else {
        pToken = &token;
    }
    return *this;
}
DustRef& DustRef::operator >> (long key) {
    if ( pToken ) {
        entity = DustData::getRef(entity, *pToken, DUST_ENTITY_INVALID, key);
        pToken = 0;
    } else {
        entity = DUST_ENTITY_INVALID;
    }
        return *this;
}



void DustRuntime::setBootToken(DustToken &token, DustEntity entity)
{
    DustEntity e = DustData::getTokenEntity(&token, entity);
    token.entity = e;
}

DustEntity DustData::getTokenEntity(DustToken* pToken, DustEntity constId)
{
    switch ( pToken->primaryType )
    {
    case DUST_IDEA_UNIT:
        return apiRuntime->getUnit(pToken->name, constId);
    case DUST_IDEA_MEMBER:
        return apiRuntime->getMemberEntity(*(pToken->parent), pToken->name, pToken->valType, pToken->collType, constId);
    default:
        return apiRuntime->getTokenEntity(*(pToken->parent), pToken->name, pToken->primaryType, constId);
    }
}

DustEntity DustData::createEntity(DustEntity primaryType)
{
    DustAccessData ad(DUST_ACCESS_CREATE, DUST_ENTITY_INVALID, primaryType);
    return apiRuntime->access(ad) ? ad.entity : DUST_ENTITY_INVALID;
}

bool DustData::deleteEntity(DustEntity entity) {
    DustAccessData ad(DUST_ACCESS_DELETE, entity, DUST_ENTITY_INVALID);
    return apiRuntime->access(ad);
}


long DustData::getMemberCount(DustEntity entity, DustEntity token)
{
    return apiRuntime->getMemberCount(entity, token);
}
DustEntity DustData::getMemberKey(DustEntity entity, DustEntity token, long idx)
{
    return apiRuntime->getMemberKey(entity, token, idx);
}
bool DustData::clearMember(DustEntity entity, DustEntity token)
{
    DustAccessData ad(DUST_ACCESS_CLEAR, entity, token);
    return apiRuntime->access(ad);
}
bool DustData::moveMember(DustEntity entity, DustEntity token, long keyFrom, long keyTo)
{
    DustAccessData ad(DUST_ACCESS_MOVE, entity, token, keyFrom, keyTo);
    return apiRuntime->access(ad);
}

long DustData::getInteger(DustEntity entity, DustEntity token, long defValue, long key)
{
    DustAccessData ad(DUST_ACCESS_GET, entity, token, key);
    return apiRuntime->access(ad) ? ad.valLong : defValue;
}
double DustData::getReal(DustEntity entity, DustEntity token, double defValue, long key)
{
    DustAccessData ad(DUST_ACCESS_GET, entity, token, key);
    return apiRuntime->access(ad) ? ad.valDouble : defValue;
}
DustEntity DustData::getRef(DustEntity entity, DustEntity token, DustEntity defValue, long key)
{
    DustAccessData ad(DUST_ACCESS_GET, entity, token, key);
    return apiRuntime->access(ad) ? ad.valLong : defValue;
}


bool DustData::setInteger(DustEntity entity, DustEntity token, long val, long key)
{
    DustAccessData ad(entity, token, val, key);
    return apiRuntime->access(ad);
}
bool DustData::setReal(DustEntity entity, DustEntity token, double val, long key)
{
    DustAccessData ad(entity, token, val, key);
    return apiRuntime->access(ad);
}
bool DustData::setRef(DustEntity entity, DustEntity token, DustEntity target, long key)
{
    DustAccessData ad(entity, token, target, key);
    return apiRuntime->access(ad);
}

bool DustData::removeInteger(DustEntity entity, DustEntity token, long val, long key)
{
    DustAccessData ad(DUST_ACCESS_REMOVE, entity, token, val, key);
    return apiRuntime->access(ad);
}
bool DustData::removeReal(DustEntity entity, DustEntity token, double val, long key)
{
    DustAccessData ad(DUST_ACCESS_REMOVE, entity, token, val, key);
    return apiRuntime->access(ad);
}
bool DustData::removeRef(DustEntity entity, DustEntity token, DustEntity target, long key)
{
    DustAccessData ad(DUST_ACCESS_REMOVE, entity, token, target, key);
    return apiRuntime->access(ad);
}

void* DustData::getNative(DustEntity entity, DustEntity type, bool createIfMissing)
{
    return apiRuntime->getNative(entity, type, createIfMissing);
}
