#ifndef DPLSTLAGENTSNARRATIVE_H
#define DPLSTLAGENTSNARRATIVE_H

#include <DustApi.h>

#include <map>

class DplStlRuntimeState;

class DplStlLogicControl: public DustNativeLogic {
private:
	std::map<DustEntity, DplStlRuntimeState*> mapChildBlocks;
	bool firstCall;

protected:
	unsigned int pos;
	bool inSep;

	void requestRelay(DustEntity relay);
	DustResultType optGetChildResult(DustResultType defRet = DUST_RESULT_ACCEPT_PASS);
	DustResultType optRelayChild();

	virtual bool isColl() {
		return true;
	}

public:
	DplStlLogicControl();
	virtual ~DplStlLogicControl();

	virtual DustResultType DustResourceInit() {
		firstCall = true;
		return DustNativeLogic::DustResourceInit();
	}
};

class DplStlLogicRepeat: public DplStlLogicControl {
protected:
	virtual bool isColl() {
		return false;
	}

public:
	virtual ~DplStlLogicRepeat() {
	}
	virtual DustResultType DustActionExecute();
};

class DplStlLogicSequence: public DplStlLogicControl {
public:
	virtual ~DplStlLogicSequence() {
	}
	virtual DustResultType DustActionExecute();
};

class DplStlLogicSelect: public DplStlLogicControl {
public:
	virtual ~DplStlLogicSelect() {
	}
	virtual DustResultType DustActionExecute();
};


#endif // DPLSTLAGENTSNARRATIVE_H
