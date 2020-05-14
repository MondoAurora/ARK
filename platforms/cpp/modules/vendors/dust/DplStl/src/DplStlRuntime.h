#ifndef DPLSTLRUNTIME_H_INCLUDED
#define DPLSTLRUNTIME_H_INCLUDED

#include <DustRuntime.h>

#include "DplStlData.h"

extern "C" class DplStlRuntime: public DustRuntime
{
    DustRuntimeConnector* pRTC;

    DplStlDataStore store;
    map<DustEntity, DustEntity> globalEntites;

    DustEntity optGetMetaEntity(DustEntity parent,  const char* name);
    DplStlDataEntity* resolveEntity(DustEntity entity);

    DustEntity getToken(DustEntity parent,  const char* name);
    DplStlDataEntity* registerGlobalEntity(DustEntity txtToken, DustEntity primaryType, DustEntity parent = DUST_ENTITY_INVALID, DustEntity constId = DUST_ENTITY_INVALID);


public:
    DplStlRuntime();
    virtual ~DplStlRuntime();

    virtual void setConnector(DustRuntimeConnector* pConn);

    virtual DustEntity getUnit(const char* name);
    virtual DustEntity getIdeaEntity(DustEntity unit, const char* name, DustIdeaType ideaType, DustEntity constId = DUST_ENTITY_INVALID);
    virtual DustEntity getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType = DUST_COLL_SINGLE, DustEntity constId = DUST_ENTITY_INVALID);

    virtual DustEntity createEntity(DustEntity primaryType);

// Entity value access
    virtual int getInt(DustEntity entity, DustEntity token, int defValue);
    virtual double getDouble(DustEntity entity, DustEntity token, double defValue);

    virtual void setInt(DustEntity entity, DustEntity token, int val);
    virtual void setDouble(DustEntity entity, DustEntity token, double val);

// Entity reference access
    virtual unsigned int getRefCount(DustEntity entity, DustEntity token);
    virtual DustEntity getRefKey(DustEntity entity, DustEntity token, int idx);
    virtual DustEntity getRef(DustEntity entity, DustEntity token, int key = DUST_ENTITY_APPEND);

    virtual bool setRef(DustEntity entity, DustEntity token, DustEntity target, int key = DUST_ENTITY_APPEND);

// Entity native content access
    virtual void* getNative(DustEntity entity, DustEntity type);

    virtual DustProcessResult DustResourceInit();
    virtual DustProcessResult DustResourceRelease();
    virtual DustProcessResult DustActionExecute();
};

#endif /* DPLSTLRUNTIME_H_INCLUDED */
