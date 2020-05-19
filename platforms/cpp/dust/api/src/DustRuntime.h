#ifndef DUSTRUNTIME_H_
#define DUSTRUNTIME_H_

#include "DustModule.h"

#define DUST_FNAME_GET_MODULE "getModule"
#define DUST_FNAME_INIT_MODULE "initModule"

enum DustBoot
{
    DUST_BOOT_AGENT_RUNTIME = DUST_LAST_CONST_MODULE,
    DUST_BOOT_AGENT_DICTIONARY,

    DUST_BOOT_UNIT_TEXT,
    DUST_BOOT_TYPE_PLAINTEXT,

    DUST_BOOT_UNIT_MODEL,
    DUST_BOOT_TYPE_ENTITY,
    DUST_BOOT_REF_GLOBALID,
    DUST_BOOT_REF_OWNER,
    DUST_BOOT_
};

#define DUST_LAST_CONST_RUNTIME DUST_BOOT_


extern "C" class DustTextDictionary: public DustNativeLogic
{
public:
    virtual ~DustTextDictionary()
    {
    }

    virtual DustEntity getTextToken(DustEntity txtParent, const char* name) = 0;
};

extern "C" class DustRuntimeConnector: public DustTextDictionary
{
public:
    virtual ~DustRuntimeConnector()
    {
    }

    virtual DustEntity getTextToken(DustEntity txtParent, const char* name) = 0;
    virtual void loadModule(const char* name) = 0;
    virtual DustModule* getModuleForType(DustEntity type) = 0;
};

extern "C" class DustAccessData
{
public:
    DustAccessType access;
    DustEntity entity;
    DustEntity token;
    DustValType valType;
    long key;

    union
    {
        long valLong;
        double valDouble;
    };

    DustAccessData(DustAccessType a, DustEntity e, DustEntity t, long k = DUST_ENTITY_APPEND, long k2 = DUST_ENTITY_APPEND)
        : access(a), entity(e), token(t), valType(DUST_VAL_), key(k), valLong(k2) {}

    DustAccessData(DustEntity e, DustEntity t, DustValType vt, long v, long k = DUST_ENTITY_APPEND)
        : access(DUST_ACCESS_SET), entity(e), token(t), valType(vt), key(k), valLong(v) {}

    DustAccessData(DustEntity e, DustEntity t, double v, long k = DUST_ENTITY_APPEND)
        : access(DUST_ACCESS_SET), entity(e), token(t), valType(DUST_VAL_REAL), key(k), valDouble(v) { }

};

extern "C" class DustRuntime: public DustNativeLogic
{
protected:
    void setBootToken(DustToken &token, DustEntity entity);

public:
    virtual ~DustRuntime()
    {
    }

    virtual DustEntity getUnit(const char* name, DustEntity constId = DUST_ENTITY_APPEND) = 0;
    virtual DustEntity getIdeaEntity(DustEntity unit, const char* name, DustIdeaType ideaType, DustEntity constId = DUST_ENTITY_APPEND) = 0;
    virtual DustEntity getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType = DUST_COLL_SINGLE, DustEntity constId = DUST_ENTITY_APPEND) = 0;

    virtual void setConnector(DustRuntimeConnector* pConn) = 0;

    virtual DustEntity createEntity(DustEntity primaryType) = 0;

    virtual long getMemberCount(DustEntity entity, DustEntity token) = 0;
    virtual DustEntity getMemberKey(DustEntity entity, DustEntity token, long idx) = 0;

    virtual bool accessMember(DustAccessData &access) = 0;

// Entity native content access
    virtual void* getNative(DustEntity entity, DustEntity type) = 0;
};

typedef DustModule* (*getModule_t)();
typedef void (*initModule_t)(DustRuntime*);

extern "C" void initModule(DustRuntime *pRuntime);

#endif /* DUSTRUNTIME_H_ */
