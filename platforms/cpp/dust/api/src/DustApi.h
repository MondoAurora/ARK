#ifndef DUSTAPI_H_
#define DUSTAPI_H_

typedef int DustEntity;

#define DUST_REFKEY_ARR_APPEND -1

enum DustTokenType {
	DUST_ENTITY_INVALID = 0,
	DUST_ENTITY_TRUE,
	DUST_ENTITY_FALSE,

	DUST_TOKEN_UNIT,
	DUST_TOKEN_TYPE,
	DUST_TOKEN_AGENT,
	DUST_TOKEN_CONST,
	DUST_TOKEN_TAG,

	DUST_TOKEN_VAL_INT,
	DUST_TOKEN_VAL_DOUBLE,
	DUST_TOKEN_VAL_REF,

	DUST_TOKEN_COLL_SET,
	DUST_TOKEN_COLL_ARR,
	DUST_TOKEN_COLL_MAP,

	DUST_TOKEN_
};

enum DustProcessResult {
	DUST_PROCESS_NOTIMPLEMENTED = DUST_ENTITY_INVALID,
	DUST_PROCESS_REJECT = DUST_TOKEN_,
	DUST_PROCESS_ACCEPT_PASS,
	DUST_PROCESS_ACCEPT,
	DUST_PROCESS_ACCEPT_READ,
	DUST_PROCESS_READ,
	DUST_PROCESS_
};

enum DustChange {
	DUST_CHG_REF_SET = DUST_PROCESS_,
	DUST_CHG_REF_REMOVE,
	DUST_CHG_REF_CLEAR,
	DUST_CHG_
};

enum DustBoot {
	DUST_BOOT_DICTIONARY = DUST_CHG_,
	DUST_BOOT_RUNTIME,
	DUST_BOOT_
};

#define DUST_LAST_CONST DUST_BOOT_

extern "C" class DustNativeResource {
public:
	virtual ~DustNativeResource() {
	}

	virtual DustProcessResult DustResourceInit() {
		return DUST_PROCESS_ACCEPT;
	}
	virtual DustProcessResult DustResourceRelease() {
		return DUST_PROCESS_ACCEPT;
	}
};

extern "C" class DustNativeAction {
public:
	virtual ~DustNativeAction() {
	}
	virtual DustProcessResult DustActionExecute() {
		return DUST_PROCESS_NOTIMPLEMENTED;
	}
};

extern "C" class DustNativeLogic: public DustNativeResource, public DustNativeAction {
public:
	virtual ~DustNativeLogic() {
	}
};

class DustData {
public:
// Entity creation and access
	static DustEntity getEntityByPath(DustEntity ctx, ...);
	static DustEntity createEntity(DustEntity primaryType);

// Entity value access
	static int getInt(DustEntity entity, DustEntity token, int defValue);
	static double getDouble(DustEntity entity, DustEntity token, double defValue);

	static void setInt(DustEntity entity, DustEntity token, int val);
	static void setDouble(DustEntity entity, DustEntity token, double val);

// Entity reference access
	static unsigned int getRefCount(DustEntity entity, DustEntity token);
	static DustEntity getRefKey(DustEntity entity, DustEntity token, int idx);
	static DustEntity getRef(DustEntity entity, DustEntity token, int key =
			DUST_REFKEY_ARR_APPEND);

	static bool setRef(DustEntity entity, DustEntity token, DustEntity target,
			int key = DUST_REFKEY_ARR_APPEND);

// Entity native content access
		static void* getNative(DustEntity entity, DustEntity type);
};

#endif /* DUSTAPI_H_ */
