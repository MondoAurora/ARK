#ifndef DUSTMODULE_H_
#define DUSTMODULE_H_

#include "DustApi.h"

extern "C" class DustModuleConnector : public DustNativeLogic {

public:
	virtual ~DustModuleConnector() {};

	virtual DustEntity getMetaUnit(const char* name) = 0;
	virtual DustEntity getMetaEntity(DustEntity primaryType, const char* name, DustEntity parent, DustEntity constId = DUST_ENTITY_INVALID) = 0;
};


class DustModule : public DustNativeLogic {
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
