#ifndef DUSTRUNTIME_H_
#define DUSTRUNTIME_H_

#include "DustModule.h"

#define DUST_FNAME_GET_MODULE "getModule"
#define DUST_FNAME_INIT_MODULE "initModule"


extern "C" class DustRuntimeConnector : public DustModuleConnector {
public:
	virtual ~DustRuntimeConnector() {
	}

	virtual DustEntity getTextToken(const char* name) = 0;
	virtual void loadModule(const char* name) = 0;
	virtual DustModule* getModuleForType(DustEntity type) = 0;
};

class DustRuntime : public DustModule {
public:
	virtual ~DustRuntime() {
	}

	virtual void setConnector(DustRuntimeConnector* pConn) = 0;

	virtual DustEntity getMetaUnit(const char* name);
	virtual DustEntity getMetaEntity(DustEntity primaryType, const char* name, DustEntity parent, DustEntity constId = DUST_ENTITY_INVALID);

	virtual DustEntity getEntityByPath(DustEntity ctx, ...);
	virtual DustEntity createEntity(DustEntity primaryType);

// Entity value access
	virtual int getInt(DustEntity entity, DustEntity token, int defValue);
	virtual double getDouble(DustEntity entity, DustEntity token, double defValue);

	virtual void setInt(DustEntity entity, DustEntity token, int val);
	virtual void setDouble(DustEntity entity, DustEntity token, double val);

// Entity reference access
	virtual unsigned int getRefCount(DustEntity entity, DustEntity token);
	virtual DustEntity getRefKey(DustEntity entity, DustEntity token, int idx);
	virtual DustEntity getRef(DustEntity entity, DustEntity token, int key =
			DUST_REFKEY_ARR_APPEND);

	virtual bool setRef(DustEntity entity, DustEntity token, DustEntity target,
			int key = DUST_REFKEY_ARR_APPEND);

// Entity native content access
		virtual void* getNative(DustEntity entity, DustEntity type);
};

typedef DustModule* (*getModule_t)();
typedef void (*initModule_t)(DustRuntime*);

#endif /* DUSTRUNTIME_H_ */
