#ifndef DPLSTLAGENTSRUNTIME_H
#define DPLSTLAGENTSRUNTIME_H

#include "DplStlData.h"

#include <stack>
#include <map>
#include <vector>

using namespace std;

typedef map<DustEntity, DplStlDataEntity*>::iterator EntityIterator;

class DplStlLogicPDA;
class DplStlRuntime;


class DplStlLogicState: public DustNativeLogic {
private:
	map<DustEntity, DplStlDataEntity*> emapRef;
	DplStlDataStore *pStore;

	DustNativeLogic* pLogic;

public:
	DplStlLogicState();
	~DplStlLogicState();

	DplStlDataEntity* getEntity(DustEntity e) ;

	DustResultType init(DplStlDataEntity *pSelf, DplStlLogicState *pParent);

	virtual DustResultType DustActionExecute();
	virtual DustResultType DustResourceRelease();
};

typedef map<DustEntity, DplStlLogicState*>::const_iterator StateIterator;

class DplStlLogicPDA: public DustNativeLogic {
	map<int, DplStlLogicState*> stack;
	int stackPos;

public:
	DplStlLogicPDA();
	virtual ~DplStlLogicPDA();

	virtual DustResultType DustActionExecute();
	virtual DustResultType DustResourceRelease();

	DplStlLogicState* getCurrentState() {
		return stack[stackPos];
	}

	void relayEntry(DplStlLogicState *pStateRelay);
	void relayExit();

	DplStlDataEntity* resolveEntity(DustEntity entity) {
		DplStlLogicState* pS = stack[stackPos];
		return pS ? pS->getEntity(entity) : NULL;
	}

	friend class DplStRuntime;
	friend class DplStlLogicControl;
	friend class DplStlLogicDialog;
};

class DplStlLogicDialog : public DustNativeLogic {
	vector<DplStlLogicPDA> pdas;
	unsigned int currPDAIdx;
	DplStlDataEntity *pData;

public:
	DplStlLogicDialog();
	~DplStlLogicDialog();

	DplStlLogicPDA* getCurrentPda() {
		return &pdas[currPDAIdx];
	}

	DplStlLogicPDA* getPda(unsigned int idx) {
		if ( idx >= pdas.size() ) {
			pdas.resize(idx+1);
		}

		return &pdas[idx];
	}

	void getData(DplStlDataEntity* pData_) {
		pData = pData_;
	}

	DplStlDataEntity* getData() {
		return pData;
	}

	virtual DustResultType DustActionExecute();
	virtual DustResultType DustResourceRelease();

	friend class DplStRuntime;
};


class DplStlLogicCore : public DustNativeLogic {
    DplStlRuntime *pRuntime;
	DplStlLogicDialog *pDialog = NULL;
	DustResultType lastResult;

public:
    DplStlLogicCore(DplStlRuntime *pRuntime);

	DustResultType getLastResult () {
		return lastResult;
	}
	DplStlLogicDialog* getDialog() {
		return pDialog;
	}

	DplStlDataEntity* resolveEntity(DustEntity entity);

	virtual DustResultType DustActionExecute();

	DustResultType run(int dlgIdx, DplStlLogicState *pState, int agentCount = 1);

	friend class DplStlLogicState;
	friend class DplStlLogicPDA;
	friend class DplStlRuntime;
	friend class DplStlLogicControl;
};

#endif // DPLSTLAGENTSRUNTIME_H
