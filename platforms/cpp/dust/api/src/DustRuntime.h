#ifndef DUSTRUNTIME_H_
#define DUSTRUNTIME_H_

#include "DustModule.h"

#define DUST_FNAME_GET_MODULE "getModule"
#define DUST_FNAME_INIT_MODULE "initModule"

extern "C" class DustRuntimeConnector: public DustModuleConnector {
public:
	virtual ~DustRuntimeConnector() {
	}

	virtual DustEntity getTextToken(const char* name) = 0;
	virtual void loadModule(const char* name) = 0;
	virtual DustModule* getModuleForType(DustEntity type) = 0;
};

extern "C" class DustTextDictionary: public DustNativeLogic {
public:
	virtual ~DustTextDictionary() {
	}

	virtual DustEntity getTextToken(const char* name) = 0;
};

extern "C" class DustRuntime: public DustNativeLogic {
public:
	virtual ~DustRuntime() {
	}

	virtual void setConnector(DustRuntimeConnector* pConn) = 0;

	virtual DustEntity getMetaUnit(const char* name) = 0;
	virtual DustEntity getMetaEntity(DustEntity primaryType, const char* name, DustEntity parent, DustEntity constId = DUST_ENTITY_INVALID) = 0;

	virtual DustEntity createEntity(DustEntity primaryType) = 0;

// Entity value access
	virtual int getInt(DustEntity entity, DustEntity token, int defValue) = 0;
	virtual double getDouble(DustEntity entity, DustEntity token, double defValue) = 0;

	virtual void setInt(DustEntity entity, DustEntity token, int val) = 0;
	virtual void setDouble(DustEntity entity, DustEntity token, double val) = 0;

// Entity reference access
	virtual unsigned int getRefCount(DustEntity entity, DustEntity token) = 0;
	virtual DustEntity getRefKey(DustEntity entity, DustEntity token, int idx) = 0;
	virtual DustEntity getRef(DustEntity entity, DustEntity token, int key = DUST_REFKEY_ARR_APPEND) = 0;

	virtual bool setRef(DustEntity entity, DustEntity token, DustEntity target, int key = DUST_REFKEY_ARR_APPEND) = 0;

// Entity native content access
	virtual void* getNative(DustEntity entity, DustEntity type) = 0;
};

typedef DustModule* (*getModule_t)();
typedef void (*initModule_t)(DustRuntime*);

extern "C" void initModule(DustRuntime *pRuntime);

#endif /* DUSTRUNTIME_H_ */
