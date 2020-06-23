#ifndef DPLSTLAGENTSRUNTIME_H
#define DPLSTLAGENTSRUNTIME_H

#include <DustRuntimeImpl.h>

#include "DplStlData.h"

#include <stack>
#include <map>
#include <vector>
#include <set>

using namespace std;

class DplStlRuntimeApp;
class DplStlRuntimeDialog;
class DplStlRuntime;
class DplStlRuntimeThread;

class DplStlRuntimeState // : public  DplStlContext
{
private:
    DplStlRuntimeDialog *pDialog;
    DplStlDataEntity *pSelf;

    void* pLogic;
    bool logic;

    int stackPos;
    map<int, DplStlRuntimeState*> *pStack;
    map<DustEntity, DplStlRuntimeState*> *pChildren;

//    DplStlDataEntity* getLocalEntity(long id);

public:
    DplStlRuntimeState();
    DplStlRuntimeState(DustEntity agent, DplStlRuntimeDialog *pDialog);
    virtual ~DplStlRuntimeState();

    void init(DustEntity agent, DplStlRuntimeDialog *pDialog);
    DustResultType step(DplStlRuntimeThread *pThread);

//    virtual DplStlDataEntity* getEntity(long id = DUST_ENTITY_APPEND, DustEntity primaryType = DUST_ENTITY_INVALID);

    friend class DplStlRuntimeThread;
    friend class DplStlLogicControl;
    friend class DplStlRuntimeDialog;
    friend class DplStlRuntimeApp;
};

typedef map<DustEntity, DplStlRuntimeState*>::const_iterator StateIterator;


class DplStlRuntimeDialog // : public  DplStlContext
{
    DplStlRuntimeApp *pApp;

    DplStlDataStore store;

    DplStlRuntimeState *pState;
    DustResultType lastResult;

    unsigned int childCount;
    unsigned int currChildIdx;

public:
    DplStlRuntimeDialog();
    virtual ~DplStlRuntimeDialog();

    inline DustResultType getLastResult ()
    {
        return lastResult;
    }

    virtual DplStlDataEntity* getEntity(long id = DUST_ENTITY_APPEND, DustEntity primaryType = DUST_ENTITY_INVALID)
    {
        return ((DUST_CTX_SELF == id) && pState && pState->pSelf) ? pState->pSelf : store.getEntity(id, primaryType);
    }

    void init(DplStlRuntimeApp *pApp, DustEntity eRoot);
    DustResultType step(DplStlRuntimeThread *pThread);
    void commit();

    friend class DplStlRuntime;
    friend class DplStlRuntimeThread;
    friend class DplStlRuntimeStateSwitcher;
};

class DplStlRuntimeStateSwitcher
{
    DplStlRuntimeDialog *pDialog;
    DplStlRuntimeState *pOldState;

public:
    DplStlRuntimeStateSwitcher(DplStlRuntimeThread *pThread, DplStlRuntimeState *pState);
    ~DplStlRuntimeStateSwitcher();
};



class DplStlRuntimeApp : public DustAppImpl
{
    DustTextDictionary *pTokenDictionary;

    DplStlDataStore store;
    map<DustEntity, DustEntity> globalEntites;
    map<DustEntity, DplStlTokenInfo*> tokenInfo;

    map<DustEntity, DustEntity> agentResolution;

    set<DplStlRuntimeDialog*> dialogs;

    DplStlRuntimeDialog* openDialog(DustEntity eRoot);
    bool closeDialog(DplStlRuntimeDialog* pTask, DustResultType result);

public:
    void initBootMembers(map<long, DustToken*> &bootEntites);
    void initBootMember(long id, DustToken* pT);

    DustEntity getTextToken(const char* name, DustEntity parent = DUST_ENTITY_INVALID);

    void optSetParent(DustAccessData &ad, DplStlDataEntity* pEntity, DustEntity parent);
    DplStlDataEntity* registerGlobalEntity(DustEntity txtToken, DustEntity primaryType, DustEntity parent = DUST_ENTITY_INVALID, DustEntity constId = DUST_ENTITY_APPEND);

    DplStlTokenInfo* getTokenInfo(DustEntity token);

    DustEntity getUnit(const char* name, DustEntity constId = DUST_ENTITY_APPEND);
    DustEntity getTokenEntity(DustEntity unit, const char* name, DustEntity primaryType, DustEntity constId = DUST_ENTITY_APPEND);
    DustEntity getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType = DUST_COLL_SINGLE, DustEntity constId = DUST_ENTITY_APPEND);

    friend class DplStlRuntimeDialog;
    friend class DplStlRuntimeThread;
    friend class DplStlRuntime;
};

class DplStlRuntimeThread
{
    DplStlRuntime* pRuntime;
    DplStlRuntimeDialog*pDialog;

public:
    DplStlRuntimeThread();
    ~DplStlRuntimeThread();

    inline DplStlRuntime *getRuntime()
    {
        return pRuntime;
    };

    inline DplStlRuntimeDialog*getDialog()
    {
        return pDialog;
    };
    inline DplStlRuntimeApp*getApp()
    {
        return pDialog->pApp;
    };

    DustResultType run(DplStlRuntimeDialog*pDialog_ = NULL);

    friend class DplStlRuntime;
};


#endif // DPLSTLAGENTSRUNTIME_H
