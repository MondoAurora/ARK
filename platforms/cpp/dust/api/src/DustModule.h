#ifndef DUSTMODULE_H_
#define DUSTMODULE_H_

#include "DustApi.h"

#define DUST_LAST_CONST_MODULE DUST_LAST_CONST_API

extern "C" class DustModuleConnector: public DustNativeLogic {

public:
	virtual ~DustModuleConnector() {
	}
	;

	virtual DustEntity getUnit(const char* name) = 0;
	virtual DustEntity getIdeaEntity(DustEntity unit, const char* name, DustIdeaType ideaType, DustEntity constId = DUST_ENTITY_INVALID) = 0;
	virtual DustEntity getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType = DUST_COLL_SINGLE, DustEntity constId = DUST_ENTITY_INVALID) = 0;
};

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
