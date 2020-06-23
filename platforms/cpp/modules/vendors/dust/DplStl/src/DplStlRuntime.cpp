#include "DplStl.h"

#include <DustUtilsDev.h>
#include <iostream>

using namespace std;

vector<long> bootOrder;
map<long, DustToken*> bootEntites;
DplStlRuntimeApp *pBootApp;
DplStlRuntimeThread *pBootThread;


DplStlRuntime* DplStlRuntime::pRuntime = NULL;

DplStlRuntime::DplStlRuntime()
    :accCount(0), accUSec(0)
{
    pRuntime = this;
}

DplStlRuntime::~DplStlRuntime()
{
}

void DplStlRuntime::setBootInfo(DustToken &token, long id)
{
    pBootApp->initBootMember(id, &token);
    setBootToken( &token, id);
//    bootEntites[id] = &token;
//    bootOrder.push_back(id);
}

void DplStlRuntime::initRuntime(DustAppImpl* pApp, DustTextDictionary *pTokenDicionary_)
{
    pBootApp = (DplStlRuntimeApp *) pApp;
    pBootApp->pTokenDictionary = pTokenDicionary_;

    pBootThread = launch(pBootApp, DUST_ENTITY_INVALID);

    cout << "Booting runtime" << endl;

    pBootApp->initBootMember(DUST_BOOT_INT_ID, &DustUnitMindModel::DustIntId);
    pBootApp->initBootMember(DUST_BOOT_REF_GLOBALID, &DustUnitMindModel::DustRefGlobalId);
    pBootApp->initBootMember(DUST_BOOT_REF_PRIMARYTYPE, &DustUnitMindModel::DustRefPrimaryType);
    pBootApp->initBootMember(DUST_BOOT_REF_TAGS, &DustUnitMindModel::DustRefTags);
    pBootApp->initBootMember(DUST_BOOT_REF_OWNER, &DustUnitMindModel::DustRefOwner);
    pBootApp->initBootMember(DUST_BOOT_REF_UNIT, &DustUnitMindModel::DustRefUnit);

    setBootInfo(DustUnitMindText::DustUnitText, DUST_BOOT_UNIT_TEXT);
    setBootInfo(DustUnitMindText::DustTypePlainText, DUST_BOOT_TYPE_PLAINTEXT);
    setBootInfo(DustUnitMindText::DustAgentDictionary, DUST_BOOT_AGENT_DICTIONARY);

    setBootInfo(DustUnitMindDialog::DustUnitDialog, DUST_BOOT_UNIT_DIALOG);
    setBootInfo(DustUnitMindDialog::DustAgentApp, DUST_BOOT_AGENT_APP);

    setBootInfo(DustUnitMindDust::DustUnitDust, DUST_BOOT_UNIT_DUST);
    setBootInfo(DustUnitMindDust::DustAgentRuntime, DUST_BOOT_AGENT_RUNTIME);

    setBootInfo(DustUnitMindModel::DustUnitModel, DUST_BOOT_UNIT_MODEL);
    setBootInfo(DustUnitMindModel::DustTypeEntity, DUST_BOOT_TYPE_ENTITY);
    setBootInfo(DustUnitMindModel::DustRefUnit, DUST_BOOT_REF_UNIT);
    setBootInfo(DustUnitMindModel::DustIntId, DUST_BOOT_INT_ID);
    setBootInfo(DustUnitMindModel::DustRefPrimaryType, DUST_BOOT_REF_PRIMARYTYPE);
    setBootInfo(DustUnitMindModel::DustRefGlobalId, DUST_BOOT_REF_GLOBALID);
    setBootInfo(DustUnitMindModel::DustRefOwner, DUST_BOOT_REF_OWNER);
    setBootInfo(DustUnitMindModel::DustRefTags, DUST_BOOT_REF_TAGS);

    setBootInfo(DustUnitMindIdea::DustUnitIdea, DUST_IDEA_TYPE);
    setBootInfo(DustUnitMindIdea::DustTypeType, DUST_IDEA_TYPE);
    setBootInfo(DustUnitMindIdea::DustTypeMember, DUST_IDEA_MEMBER);
    setBootInfo(DustUnitMindIdea::DustTypeAgent, DUST_IDEA_AGENT);
    setBootInfo(DustUnitMindIdea::DustTypeTag, DUST_IDEA_TAG);
    setBootInfo(DustUnitMindIdea::DustTypeConstant, DUST_IDEA_CONSTANT);

    setBootInfo(DustUnitMindIdea::DustTagValInteger, DUST_VAL_INTEGER);
    setBootInfo(DustUnitMindIdea::DustTagValReal, DUST_VAL_REAL);
    setBootInfo(DustUnitMindIdea::DustTagValRef, DUST_VAL_REF);

    setBootInfo(DustUnitMindIdea::DustTagCollSingle, DUST_COLL_SINGLE);
    setBootInfo(DustUnitMindIdea::DustTagCollSet, DUST_COLL_SET);
    setBootInfo(DustUnitMindIdea::DustTagCollArr, DUST_COLL_ARR);
    setBootInfo(DustUnitMindIdea::DustTagCollMap, DUST_COLL_MAP);

    setBootInfo(DustUnitMindNarrative::DustTagResultReject, DUST_RESULT_REJECT);
    setBootInfo(DustUnitMindNarrative::DustTagResultRead, DUST_RESULT_READ);
    setBootInfo(DustUnitMindNarrative::DustTagResultAccept, DUST_RESULT_ACCEPT);
    setBootInfo(DustUnitMindNarrative::DustTagResultAcceptPass, DUST_RESULT_ACCEPT_PASS);
    setBootInfo(DustUnitMindNarrative::DustTagResultAcceptRead, DUST_RESULT_ACCEPT_READ);

    setBootInfo(DustUnitMindDialog::DustTagCtxSelf, DUST_CTX_SELF);
    setBootInfo(DustUnitMindDialog::DustTagCtxDialog, DUST_CTX_DIALOG);
    setBootInfo(DustUnitMindDialog::DustTagCtxApp, DUST_CTX_APP);
    setBootInfo(DustUnitMindDialog::DustTagCtxSystem, DUST_CTX_SYSTEM);

    setBootInfo(DustUnitMindDialog::DustTagAccessGet, DUST_ACCESS_GET);
    setBootInfo(DustUnitMindDialog::DustTagAccessSet, DUST_ACCESS_SET);
    setBootInfo(DustUnitMindDialog::DustTagAccessMove, DUST_ACCESS_MOVE);
    setBootInfo(DustUnitMindDialog::DustTagAccessRemove, DUST_ACCESS_REMOVE);
    setBootInfo(DustUnitMindDialog::DustTagAccessClear, DUST_ACCESS_CLEAR);
    setBootInfo(DustUnitMindDialog::DustTagAccessCreate, DUST_ACCESS_CREATE);
    setBootInfo(DustUnitMindDialog::DustTagAccessDelete, DUST_ACCESS_DELETE);
    setBootInfo(DustUnitMindDialog::DustTagAccessSetType, DUST_ACCESS_SETTYPE);

    setBootInfo(DustUnitMindNative::DustTypeService, DUST_NATIVE_SERVICE);
    setBootInfo(DustUnitMindNative::DustTypeCommand, DUST_NATIVE_COMMAND);

    setBootInfo(DustUnitMindTime::DustTagEventLevelCritical, DUST_EVENT_CRITICAL);
    setBootInfo(DustUnitMindTime::DustTagEventLevelError, DUST_EVENT_ERROR);
    setBootInfo(DustUnitMindTime::DustTagEventLevelWarning, DUST_EVENT_WARNING);
    setBootInfo(DustUnitMindTime::DustTagEventLevelnfo, DUST_EVENT_INFO);
    setBootInfo(DustUnitMindTime::DustTagEventLevelTrace, DUST_EVENT_TRACE);
    setBootInfo(DustUnitMindTime::DustTagEventLevelDebug, DUST_EVENT_DEBUG);

//    pBootApp->initBootMembers(bootEntites);

    DplStlDataEntity *pE = createEntity(DUST_BOOT_AGENT_APP);
    pE->setNative(DUST_BOOT_AGENT_APP, pBootApp);

    pBootThread->getDialog()->store.entities[DUST_CTX_APP] = pE;

//    for (int i = 0; i < bootOrder.size(); ++i)
//    {
//        long id = bootOrder[i];
//        setBootToken( bootEntites[id], id);
//    }
//    for (BootIterator it = bootEntites.begin(); it != bootEntites.end(); ++it)
//    {
//        setBootToken( it->second, it->first);
//    }

    bootEntites.clear();
}

DustResultType DplStlRuntime::DustResourceInit()
{
    return DUST_RESULT_ACCEPT;
}

DustResultType DplStlRuntime::DustResourceRelease()
{
    cout << "Runtime access called " << accCount << ", time " << ((double) accUSec) / 1000000 << " seconds." << endl;
    return DUST_RESULT_ACCEPT;
}



DustEntity DplStlRuntime::getUnit(const char* name, DustEntity constId)
{
    return getCurrentThread()->getApp()->getUnit(name, constId);
}

DustEntity DplStlRuntime::getTokenEntity(DustEntity parent, const char* name, DustEntity primaryType, DustEntity constId)
{
    return getCurrentThread()->getApp()->getTokenEntity(parent, name, primaryType, constId);
}

DustEntity DplStlRuntime::getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType, DustEntity constId)
{
    return getCurrentThread()->getApp()->getMemberEntity(type, name, valType, collType, constId);
}


DplStlDataEntity* DplStlRuntime::resolveEntity(DustEntity entity)
{
    return getCurrentThread()->getDialog()->getEntity(entity);
}


DplStlDataEntity* DplStlRuntime::createEntity(DustEntity primaryType)
{
    return getCurrentThread()->getDialog()->getEntity(DUST_ENTITY_APPEND, primaryType);
}

long DplStlRuntime::getMemberCount(DustEntity entity, DustEntity token)
{
    long c = 0;

    DplStlDataEntity *pEntity = resolveEntity(entity);
    if ( pEntity )
    {
        DplStlDataVariant *pVar = pEntity->getVariant(token);
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
            DplStlDataVariant *pVar = pEntity->getVariant(token);
            if ( pVar && pVar->pColl && ( (unsigned) idx < pVar->pColl->size()))
            {
                key = (DUST_COLL_MAP == pVar->pTokenInfo->collType) ? pVar->pColl->at(idx)->key : idx;
            }
        }
    }

    return key;
}

bool DplStlRuntime::access(DustAccessData &ad)
{
    bool ret = false;

    struct timeval b;
    DustUtilsDev::timeBegin(b);

    DplStlDataEntity *pEntity = ( DUST_ACCESS_CREATE == ad.access ) ? createEntity(ad.token) : resolveEntity(ad.entity);

    if ( pEntity )
    {
        switch ( ad.access )
        {
        case DUST_ACCESS_CREATE:
            ad.entity = pEntity->id;
            ret = true;
            break;
        case DUST_ACCESS_SETTYPE:
        {
            DplStlDataEntity *pSrc = ( DUST_ENTITY_APPEND == ad.valLong ) ? 0 : resolveEntity(ad.valLong);
            pEntity->setType(ad, pSrc);
        }
        ret = true;
        break;
        default:
            ret = pEntity->access(ad);
        }
    }

    ++accCount;
    accUSec += DustUtilsDev::timeElapseUSec(b);

    return ret;
}



void* DplStlRuntime::getNative(DustEntity entity, DustEntity type, bool createIfMissing)
{
    DplStlDataEntity *pEntity = resolveEntity(entity);
    if ( DUST_ENTITY_APPEND == type )
    {
        type = pEntity->primaryType;
    }
    void* ret = pEntity->getNative(type);

    if ( !ret && createIfMissing)
    {
        ret = getCurrentThread()->getApp()->createNative(type);
        if ( ret )
        {
            pEntity->setNative(type, ret);
        }
    }

    return ret;
}

void DplStlRuntime::deleteNative(DustEntity type, void* pNative)
{
    getCurrentThread()->getApp()->releaseNative(type, pNative);
}

DustResultType DplStlRuntime::DustActionExecute()
{
    pBootThread->getDialog()->commit();

    DustEntity eMain = DustData::getRef(DUST_CTX_APP, DustUnitMindDialog::DustRefAppMain);

    delete pBootThread;
    threads.clear();

    DplStlRuntimeThread *pMainThread = launch(pBootApp, eMain);

    return pMainThread->run();
}

DplStlRuntime* DplStlRuntime::getRuntime() {
    return pRuntime;
}

DplStlRuntimeThread* DplStlRuntime::getCurrentThread()
{
    return pRuntime->threads[0];
}

DplStlRuntimeThread *DplStlRuntime::launch(DplStlRuntimeApp *pApp, DustEntity agent)
{
    DplStlRuntimeThread *pThread = new DplStlRuntimeThread();

    pThread->pRuntime = this;
    threads.push_back(pThread);
    DplStlRuntimeDialog *pDialog = new DplStlRuntimeDialog();
    pThread->pDialog = pDialog;
    pDialog->init(pApp, agent);

    return pThread;
}

void DplStlRuntime::rescheduleThread(DplStlRuntimeThread* pThread)
{
}
