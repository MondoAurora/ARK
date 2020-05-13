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

DustEntity DplStlRuntime::optGetMetaEntity(DustEntity parent,  const char* name)
{
    DustEntity txtToken = pRTC->getTextToken(0, name);
    return mapOptGetDef(globalEntites, txtToken, DUST_ENTITY_INVALID);
}

DustEntity DplStlRuntime::getUnit(const char* name) {
    DustEntity unit = optGetMetaEntity(0, name);

    if ( !unit ) {

    }

    return unit;
}

DustEntity DplStlRuntime::getIdeaEntity(DustEntity unit, const char* name, DustIdeaType ideaType, DustEntity constId)
{
    return DUST_ENTITY_INVALID;
}

DustEntity DplStlRuntime::getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType, DustEntity constId)
{
    return DUST_ENTITY_INVALID;
}




DustEntity DplStlRuntime::createEntity(DustEntity primaryType)
{
    return DUST_ENTITY_INVALID;
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
    DustModule *pMod = pRTC->getModuleForType(type);

    return pMod ? pMod->createNative(type) : NULL;
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

