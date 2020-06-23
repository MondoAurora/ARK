#ifndef DPLSTLRUNTIME_H_INCLUDED
#define DPLSTLRUNTIME_H_INCLUDED

#include <DustRuntimeImpl.h>

#include "DplStlData.h"
#include "DplStlAgentsRuntime.h"

typedef map<long, DustToken*>::iterator BootIterator;

extern "C" class DplStlRuntime: public DustRuntimeImpl
{
    long accCount;
    long accUSec;

    static DplStlRuntime* pRuntime;

    vector<DplStlRuntimeThread*> threads;

    vector<DplStlRuntimeApp*> arrPtrApps;

    DplStlDataEntity* createEntity(DustEntity primaryType);

    void reschedule(DplStlRuntimeThread *pThread);
    DplStlRuntimeThread *launch(DplStlRuntimeApp *pApp, DustEntity agent);

    void setBootInfo(DustToken &token, long id);

public:
    DplStlRuntime();
    virtual ~DplStlRuntime();

    virtual void initRuntime(DustAppImpl* pApp, DustTextDictionary *pTokenDicionary_);

    virtual DustEntity getUnit(const char* name, DustEntity constId = DUST_ENTITY_APPEND);
    virtual DustEntity getTokenEntity(DustEntity unit, const char* name, DustEntity primaryType, DustEntity constId = DUST_ENTITY_APPEND);
    virtual DustEntity getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType = DUST_COLL_SINGLE, DustEntity constId = DUST_ENTITY_APPEND);

    virtual DplStlDataEntity* resolveEntity(DustEntity entity);

    virtual long getMemberCount(DustEntity entity, DustEntity token);
    virtual DustEntity getMemberKey(DustEntity entity, DustEntity token, long idx);
    virtual bool access(DustAccessData &access);

// Entity native content access
    virtual void* getNative(DustEntity entity, DustEntity type = DUST_ENTITY_APPEND, bool createIfMissing = true);
    void deleteNative(DustEntity type, void* pNative);

    virtual DustResultType DustResourceInit();
    virtual DustResultType DustResourceRelease();
    virtual DustResultType DustActionExecute();

    static DplStlRuntime* getRuntime();
    static DplStlRuntimeThread* getCurrentThread();

    void rescheduleThread(DplStlRuntimeThread* pThread);
};

#endif /* DPLSTLRUNTIME_H_INCLUDED */
