#include "DplStl.h"


DplStlLogicState::DplStlLogicState() :
		pStore(NULL), pLogic(NULL) {
}

DplStlLogicState::~DplStlLogicState() {
}

DplStlDataEntity* DplStlLogicState::getEntity(DustEntity e) {
	EntityIterator i = pStore->entities.find(e);
	DplStlDataEntity* ret;

	if (i == pStore->entities.end()) {
		EntityIterator pi = emapRef.find(e);
		ret = (pi == emapRef.end()) ? NULL : pi->second;
	} else {
		ret = i->second;
	}

	return ret;
}

DustResultType DplStlLogicState::init(DplStlDataEntity *pTask, DplStlLogicState *pParent) {
//	DplStlDataRef *pRef;
	DplStlDataEntity *pSelf;

//	if (AgentCall == pTask->primaryType) {
//	} else {
		pSelf = pTask; // maybe shallow copy?
//	}

	emapRef[DPL_CTX_SELF] = pSelf;

    DplStlRuntime *pR = DplStlRuntime::getRuntime();

	pStore = pParent ? pParent->pStore : &pR->store;

	/*
	DustEntity eRes = findEntity(pR->agentResolution, pSelf->primaryType);
	if ( eRes ) {
		pSelf->primaryType = pR->resolveEntity(eRes)->primaryType;
	}

	pLogic =  DplStlRuntime::createNative(pSelf->primaryType);
*/

	return DUST_RESULT_ACCEPT;
}

DustResultType DplStlLogicState::DustActionExecute() {
	DustResultType ret = pLogic->DustActionExecute();
	DplStlRuntime::getCurrentCore()->lastResult = ret;
	return ret;
}

DustResultType DplStlLogicState::DustResourceRelease() {
    /*
	DplStlDataEntity *pSelf = emapRef[DPL_CTX_SELF];

    pSelf->releaseActions();
*/
	emapRef.clear();
	return DUST_RESULT_ACCEPT;
}

/****************************
 *
 * Agent
 *
 ****************************/

DplStlLogicPDA::DplStlLogicPDA()
:stackPos(-1)
{

}

DplStlLogicPDA::~DplStlLogicPDA() {
	DustResourceRelease();
}

DustResultType DplStlLogicPDA::DustActionExecute() {
	DustResultType ret = stack[stackPos]->DustActionExecute();

	if (!DustUtils::isReading(ret)) {
		if (0 < stackPos) {
			--stackPos;
			ret = DUST_RESULT_READ;
		}
	}

	return ret;
}

DustResultType DplStlLogicPDA::DustResourceRelease() {
	stack.clear();
	stackPos = -1;
	return DUST_RESULT_ACCEPT;
}

void DplStlLogicPDA::relayEntry(DplStlLogicState *pStateRelay) {
	stack[++stackPos] = pStateRelay;
}

void DplStlLogicPDA::relayExit() {
	stack[stackPos--] = NULL;
}

/****************************
 *
 * Dialog
 *
 ****************************/

DplStlLogicDialog::DplStlLogicDialog()
:currPDAIdx(0),pData(NULL)
{
	pdas.resize(1);
}

DplStlLogicDialog::~DplStlLogicDialog() {
	DustResourceRelease();
}

DustResultType DplStlLogicDialog::DustActionExecute() {
	DustResultType ret = pdas[currPDAIdx].DustActionExecute();

	switch (ret) {
	case DUST_RESULT_ACCEPT:
		if (currPDAIdx) {
			currPDAIdx = 0;
			ret = DUST_RESULT_READ;
		}
		break;
	case DUST_RESULT_ACCEPT_PASS:
		if (++currPDAIdx == pdas.size()) {
			currPDAIdx = 0;
		}
		ret = DUST_RESULT_READ;
		break;
	default:
		// do nothing
		break;
	}

	return ret;
}

DustResultType DplStlLogicDialog::DustResourceRelease() {
	pdas.clear();
	currPDAIdx = 0;
	return DUST_RESULT_ACCEPT;
}

/****************************
 *
 * Core
 *
 ****************************/

DplStlLogicCore::DplStlLogicCore(DplStlRuntime *pR)
: pRuntime(pR), pDialog(NULL), lastResult(DUST_RESULT_READ) {}


DustResultType DplStlLogicCore::DustActionExecute() {
	while (pDialog) {
		DustResultType dlgRet = pDialog->DustActionExecute();
		if (!DustUtils::isReading(dlgRet) ) {
			pDialog = NULL;
		}

		pRuntime->pScheduler->DustActionExecute();
	}

	return lastResult;
}

DplStlDataEntity* DplStlLogicCore::resolveEntity(DustEntity entity) {
	return pDialog ? pDialog->getCurrentPda()->resolveEntity(entity) : NULL;
}

DustResultType DplStlLogicCore::run(int dlgIdx, DplStlLogicState *pState, int agentCount) {
	pDialog = pRuntime->dialogs[dlgIdx];

	for ( int i = 0; i < agentCount; ++i) {
		pDialog->getPda(i)->relayEntry(&pState[i]);
	}

	return DustActionExecute();
}
