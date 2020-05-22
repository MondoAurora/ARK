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

    DustEntity getTextToken(DustEntity parent,  const char* name);
    void optSetParent(DustAccessData &ad, DplStlDataEntity* pEntity, DustEntity parent);

    DplStlDataEntity* registerGlobalEntity(DustEntity txtToken, DustEntity primaryType, DustEntity parent = DUST_ENTITY_INVALID, DustEntity constId = DUST_ENTITY_APPEND);

public:
    DplStlRuntime();
    virtual ~DplStlRuntime();

    virtual void setConnector(DustRuntimeConnector* pConn);

    virtual DustEntity getUnit(const char* name, DustEntity constId = DUST_ENTITY_APPEND);
    virtual DustEntity getTokenEntity(DustEntity unit, const char* name, DustEntity primaryType, DustEntity constId = DUST_ENTITY_APPEND);
    virtual DustEntity getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType = DUST_COLL_SINGLE, DustEntity constId = DUST_ENTITY_APPEND);

    virtual DustEntity createEntity(DustEntity primaryType);

    virtual long getMemberCount(DustEntity entity, DustEntity token);
    virtual DustEntity getMemberKey(DustEntity entity, DustEntity token, long idx);

   	virtual bool accessMember(DustAccessData &access);

// Entity native content access
    virtual void* getNative(DustEntity entity, DustEntity type);

    virtual DustResultType DustResourceInit();
    virtual DustResultType DustResourceRelease();
    virtual DustResultType DustActionExecute();
};

#endif /* DPLSTLRUNTIME_H_INCLUDED */
