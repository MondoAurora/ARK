#ifndef DPLSTLRUNTIME_H_INCLUDED
#define DPLSTLRUNTIME_H_INCLUDED

#include <DustRuntime.h>

#include "DplStlData.h"
#include "DplStlAgentsRuntime.h"

extern "C" class DplStlRuntime: public DustRuntime
{
    DustRuntimeConnector* pRTC;

    long accCount;
    long accUSec;

    static DplStlRuntime* pRuntime;

    DplStlDataStore store;
    map<DustEntity, DustEntity> globalEntites;

   	map<DustEntity, DustEntity> agentResolution;

    DustNativeLogic *pScheduler;
	vector<DplStlLogicCore*> cores;
	vector<DplStlLogicDialog*> dialogs;

    DplStlDataEntity* createEntity(DustEntity primaryType);

    DustEntity optGetMetaEntity(DustEntity parent,  const char* name);

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

    DplStlDataEntity* resolveEntity(DustEntity entity);

    virtual long getMemberCount(DustEntity entity, DustEntity token);
    virtual DustEntity getMemberKey(DustEntity entity, DustEntity token, long idx);

   	virtual bool access(DustAccessData &access);

// Entity native content access
    virtual void* getNative(DustEntity entity, DustEntity type, bool createIfMissing);

    virtual DustResultType DustResourceInit();
    virtual DustResultType DustResourceRelease();
    virtual DustResultType DustActionExecute();

   	static DplStlRuntime* getRuntime();
   	static DplStlLogicCore* getCurrentCore();

   	friend class DplStlLogicState;
   	friend class DplStlLogicCore;
};

#endif /* DPLSTLRUNTIME_H_INCLUDED */
