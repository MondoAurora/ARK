#include "DplStl.h"

using namespace DustUnitMindDialog;
using namespace DustUnitMindGeneric;


/****************************
 *
 *      App
 *
 ****************************/

void DplStlRuntimeApp::initBootMembers(map<long, DustToken*> &bootEntites)
{
    for (BootIterator it = bootEntites.begin(); it != bootEntites.end(); ++it)
    {
        DustToken* pT = it->second;
        if ( DUST_IDEA_MEMBER == pT->getPrimaryType() )
        {
            tokenInfo[it->first] = new DplStlTokenInfo(pT->getValType(), pT->getCollType());
        }
    }
}

DplStlTokenInfo* DplStlRuntimeApp::getTokenInfo(DustEntity token)
{
    DplStlTokenInfo* pTI = tokenInfo[token];

    if ( !pTI )
    {
        DustValType vT = (DustValType) DustUtils::getSingleTag(token, DustUnitMindIdea::DustTagVal, DUST_VAL_INTEGER);
        DustCollType cT = (DustCollType) DustUtils::getSingleTag(token, DustUnitMindIdea::DustTagColl, DUST_COLL_SINGLE);

        cout << "Dynamic token def " << token << ", vT " << vT << ", cT " << cT << endl;

        tokenInfo[token] = pTI = new DplStlTokenInfo(vT, cT);
    }

    return pTI;
}

DustEntity DplStlRuntimeApp::getTextToken(const char* name, DustEntity parent)
{
    DustEntity txtParent = parent ? DustData::getRef(parent, DUST_BOOT_REF_GLOBALID) : DUST_ENTITY_INVALID;
    return pTokenDictionary->getTextToken(name, txtParent);
}

void DplStlRuntimeApp::optSetParent(DustAccessData &ad, DplStlDataEntity* pEntity, DustEntity parent)
{
    if ( parent )
    {
        ad.updateLong(parent, DUST_BOOT_REF_OWNER);
        pEntity->access(ad);

        for ( DustEntity p = parent; p; p = DustData::getRef(p, DUST_BOOT_REF_OWNER) )
        {
            DustEntity unit = DustData::getRef(p, DUST_BOOT_REF_UNIT);
            if ( unit )
            {
                ad.updateLong(unit, DUST_BOOT_REF_UNIT);
                pEntity->access(ad);
                break;
            }
        }
    }
}

DplStlDataEntity* DplStlRuntimeApp::registerGlobalEntity(DustEntity txtToken, DustEntity primaryType, DustEntity parent, DustEntity constId)
{
    DplStlDataEntity* pEntity = store.getEntity(constId, primaryType);
    DustEntity entity = pEntity->id;

    globalEntites[txtToken] = entity;
    DustAccessData ad(entity, DUST_BOOT_REF_GLOBALID, txtToken);
    pEntity->access(ad);

    optSetParent(ad, pEntity, parent);

    return pEntity;
}

DustEntity DplStlRuntimeApp::getUnit(const char* name, DustEntity constId)
{
    DustEntity txtToken = getTextToken(name);
    DustEntity unit = findEntity(globalEntites, txtToken);

    if ( !unit )
    {
        DplStlDataEntity* pEntity = registerGlobalEntity(txtToken, DUST_MODEL_UNIT, DUST_ENTITY_INVALID, constId);
        unit = pEntity->id;
        DustAccessData ad(unit, DUST_BOOT_REF_UNIT, unit);
        pEntity->access(ad);
    }

    return unit;
}

DustEntity DplStlRuntimeApp::getTokenEntity(DustEntity parent, const char* name, DustEntity primaryType, DustEntity constId)
{
    DustEntity txtToken = getTextToken(name, parent);
    DustEntity idea = findEntity(globalEntites, txtToken);

    if ( !idea )
    {
        DplStlDataEntity* pEntity = registerGlobalEntity(txtToken, primaryType, parent, constId);
        idea = pEntity->id;
    }

    return idea;
}

DustEntity DplStlRuntimeApp::getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType, DustEntity constId)
{
    DustEntity txtToken = getTextToken(name, type);
    DustEntity member = findEntity(globalEntites, txtToken);

    if ( !member )
    {
        DplStlDataEntity* pEntity = registerGlobalEntity(txtToken, DUST_IDEA_MEMBER, type, constId);
        member = pEntity->id;

        DustAccessData ad(member, DUST_BOOT_REF_TAGS, (long) valType);
        pEntity->access(ad);

        ad.updateLong(collType);
        pEntity->access(ad);

        cout << "Token def " << name << ", vT " << valType << ", cT " << collType << endl;

    }

    return member;
}

DplStlRuntimeDialog* DplStlRuntimeApp::openDialog(DustEntity eRoot)
{
    DplStlRuntimeDialog* ret = new DplStlRuntimeDialog();

    ret->init(this, eRoot);
    dialogs.insert(ret);

    return ret;
}

bool DplStlRuntimeApp::closeDialog(DplStlRuntimeDialog* pDialog, DustResultType result)
{
    bool found = dialogs.erase(pDialog);
    if ( found )
    {
        delete pDialog;
    }
    return found;
}

/****************************
 *
 *      Thread
 *
 ****************************/

DplStlRuntimeThread::DplStlRuntimeThread()
    : pRuntime(NULL), pDialog(NULL) {}

DplStlRuntimeThread::~DplStlRuntimeThread() {}

DustResultType DplStlRuntimeThread::run(DplStlRuntimeDialog*pDialog_)
{
    if ( pDialog_ ) {
        pDialog = pDialog_;
    }

    DustResultType ret;

    while (pDialog)
    {
        ret = pDialog->step(this);

        if (!DustUtils::isReading(ret) )
        {
            pDialog = NULL;
        }

        pRuntime->rescheduleThread(this);
    }

    return ret;
}


/****************************
 *
 * State
 *
 ****************************/
DplStlRuntimeState::DplStlRuntimeState()
    :    DplStlRuntimeState(DUST_ENTITY_INVALID, NULL)
{
}

DplStlRuntimeState::DplStlRuntimeState(DustEntity agent, DplStlRuntimeDialog *pDialog_)
    :    pDialog(NULL), pSelf(NULL), pLogic(NULL), logic(true), stackPos(-1), pStack(NULL), pChildren(NULL)
{
    init(agent, pDialog_);
}

void DplStlRuntimeState::init(DustEntity agent, DplStlRuntimeDialog *pDialog_)
{
    pDialog = pDialog_;
    pSelf = agent ? new DplStlDataEntity(*(pDialog_->getEntity(agent))) : NULL;
}

DplStlRuntimeState::~DplStlRuntimeState()
{
    if ( pSelf ) {
        delete pSelf;
    }
}

DustResultType DplStlRuntimeState::step(DplStlRuntimeThread *pThread)
{
    DplStlRuntimeStateSwitcher(pThread, this);

    if ( !pLogic )
    {
        pLogic = pThread->getRuntime()->getNative(pSelf->id);
    }

    DustResultType ret = ((DustNativeLogic*)pLogic)->DustActionExecute();

    /** Just keeping the code, should check later */
    if ( pStack && !DustUtils::isReading(ret) && (0 < stackPos) )
    {
        --stackPos;
        ret = DUST_RESULT_READ;
    }

    return ret;
}

/****************************
 *
 * Dialog
 *
 ****************************/

DplStlRuntimeDialog::DplStlRuntimeDialog()
    : pApp(NULL), pState(NULL), lastResult(DUST_RESULT_NOTIMPLEMENTED), currChildIdx(0)
{
}

DplStlRuntimeDialog::~DplStlRuntimeDialog()
{
    if (DustUtils::isSuccess(lastResult)) {
        commit();
    }
}

void DplStlRuntimeDialog::init(DplStlRuntimeApp *pApp_, DustEntity eRoot)
{
    pApp = pApp_;
    store.init(&pApp->store);

    if (eRoot) {
        childCount = DustData::getMemberCount(eRoot, DustRefCollectionMembers);
    }
    pState = new DplStlRuntimeState(eRoot, this);
}

DustResultType DplStlRuntimeDialog::step(DplStlRuntimeThread *pThread)
{
    DustResultType ret = pState->step(pThread);

    if ( childCount ) {
    switch (ret)
    {
    case DUST_RESULT_ACCEPT:
        if (currChildIdx)
        {
            currChildIdx = 0;
            ret = DUST_RESULT_READ;
        }
        break;
    case DUST_RESULT_ACCEPT_PASS:
        if (++currChildIdx == childCount)
        {
            currChildIdx = 0;
        }
        ret = DUST_RESULT_READ;
        break;
    default:
        // do nothing
        break;
    }
    }
    return ret;
}

void DplStlRuntimeDialog::commit() {
    store.commit();
}

DplStlRuntimeStateSwitcher::DplStlRuntimeStateSwitcher(DplStlRuntimeThread *pThread, DplStlRuntimeState *pState)
{
    pDialog = pThread->getDialog();
    pOldState = pDialog->pState;
    pDialog->pState = pState;
}



DplStlRuntimeStateSwitcher::~DplStlRuntimeStateSwitcher()
{
    pDialog->pState = pOldState;
};
