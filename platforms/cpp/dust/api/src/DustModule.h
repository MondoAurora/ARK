#ifndef DUSTMODULE_H_
#define DUSTMODULE_H_

#include "DustApi.h"

#define DUST_LAST_CONST_MODULE DUST_LAST_CONST_API

class DustRuntime;

extern "C" class DustModule: public DustNativeLogic {
	static DustRuntime* apiRuntime;

	friend class DustData;

public:
	virtual ~DustModule() {
	}

	virtual void* createNative(int typeId) const {
		return 0;
	}
	virtual DustProcessResult dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) const {
		return DUST_PROCESS_NOTIMPLEMENTED;
	}
	virtual void releaseNative(int typeId, void* pNativeObject) const {
	}
};

#endif /* DUSTMODULE_H_ */
