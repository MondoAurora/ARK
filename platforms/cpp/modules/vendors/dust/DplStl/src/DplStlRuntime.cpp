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

DustEntity DplStlRuntime::getToken(DustEntity parent,  const char* name)
{
    DustEntity txtParent = parent;
    return pRTC->getTextToken(txtParent, name);
}

DplStlDataEntity* DplStlRuntime::registerGlobalEntity(DustEntity txtToken, DustEntity primaryType, DustEntity parent, DustEntity constId)
{
    DplStlDataEntity* pEntity = store.getEntity(constId, primaryType);
    globalEntites[txtToken] = pEntity->id;

    // TODO register parent link and globalId

    return pEntity;
}

DustEntity DplStlRuntime::getUnit(const char* name) {
    DustEntity txtToken = getToken(0, name);
    DustEntity unit = findEntity(globalEntites, txtToken);

    if ( !unit ) {
            DplStlDataEntity* pEntity = registerGlobalEntity(txtToken, DUST_BOOT_TYPE_UNIT);
            unit = pEntity->id;
    }

    return unit;
}

DustEntity DplStlRuntime::getIdeaEntity(DustEntity unit, const char* name, DustIdeaType ideaType, DustEntity constId)
{
    DustEntity txtToken = getToken(unit, name);
    DustEntity idea = findEntity(globalEntites, txtToken);

    if ( !idea ) {
            DplStlDataEntity* pEntity = registerGlobalEntity(txtToken, ideaType, unit, constId);
            idea = pEntity->id;
    }

    return idea;
}

DustEntity DplStlRuntime::getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType, DustEntity constId)
{
    DustEntity txtToken = getToken(type, name);
    DustEntity member = findEntity(globalEntites, txtToken);

    if ( !member ) {
            DplStlDataEntity* pEntity = registerGlobalEntity(txtToken, DUST_BOOT_TYPE_MEMBER, type, constId);
            member = pEntity->id;
    }

    return member;
}



DplStlDataEntity* DplStlRuntime::resolveEntity(DustEntity entity) {
    return store.getEntity(entity);
}


DustEntity DplStlRuntime::createEntity(DustEntity primaryType)
{
    return store.getEntity(DUST_ENTITY_APPEND, primaryType)->id;
}

int DplStlRuntime::getInt(DustEntity entity, DustEntity token, int defValue)
{
    return ival;
}

double DplStlRuntime::getDouble(DustEntity entity, DustEntity token, double defValue)
{
    return 0;
}

void DplStlRuntime::setInt(DustEntity entity, DustEntity token, int val)
{
    ival = val;
    cout << "test data set to " << val << endl;
}

void DplStlRuntime::setDouble(DustEntity entity, DustEntity token, double val)
{
}


unsigned int DplStlRuntime::getRefCount(DustEntity entity, DustEntity token)
{
    return 0;
}

DustEntity DplStlRuntime::getRefKey(DustEntity entity, DustEntity token, int idx)
{
    return DUST_ENTITY_INVALID;
}

DustEntity DplStlRuntime::getRef(DustEntity entity, DustEntity token, int key)
{
    return DUST_ENTITY_INVALID;
}

bool DplStlRuntime::setRef(DustEntity entity, DustEntity token, DustEntity target, int key)
{
    return false;
}

void* DplStlRuntime::getNative(DustEntity entity, DustEntity type)
{
    DplStlDataEntity *pEntity = resolveEntity(entity);
    void* ret = mapOptGet(pEntity->native, type);

    if ( !ret ) {
        DustModule *pMod = pRTC->getModuleForType(type);

        if ( pMod ) {
            ret = pMod->createNative(type);
            if ( ret ) {
                pEntity->native[type] = ret;
            }
        }
    }

    return ret;
}




DustProcessResult DplStlRuntime::DustResourceInit()
{
    return DUST_PROCESS_ACCEPT;
}
DustProcessResult DplStlRuntime::DustResourceRelease()
{
    return DUST_PROCESS_ACCEPT;
}

DustProcessResult DplStlRuntime::DustActionExecute()
{
    return DUST_PROCESS_NOTIMPLEMENTED;
}

