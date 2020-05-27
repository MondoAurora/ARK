#ifndef DUSTMODULE_H_
#define DUSTMODULE_H_

#include "DustUtils.h"

#define DUST_LAST_CONST_MODULE DUST_LAST_CONST_API

class DustRuntime;

extern "C" class DustFactoryLogic
{
    virtual DustToken& DustFactoryGetToken() = 0;
    virtual void* DustFactoryCreate() = 0;
    virtual void DustFactoryDestroy(void*) = 0;

    virtual DustResultType DustFactoryCommand(DustNativeLogic* pLogic, DustEntity cmd, DustEntity param) {
		return DUST_RESULT_NOTIMPLEMENTED;
	}
} ;

extern "C" class DustModule: public DustNativeLogic {
	static DustRuntime* apiRuntime;

	friend class DustData;

public:
	virtual ~DustModule() {
	}

	virtual void* createNative(int typeId) const {
		return 0;
	}
	virtual DustResultType dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) const {
		return DUST_RESULT_NOTIMPLEMENTED;
	}
	virtual void releaseNative(int typeId, void* pNativeObject) const {
	}
};

#endif /* DUSTMODULE_H_ */
