#ifndef DUSTKERNEL_H_
#define DUSTKERNEL_H_

#include "DustModule.h"

enum DustBoot
{
    DUST_BOOT_MODNAME_KERNEL = DUST_LAST_CONST_MODULE,
    DUST_BOOT_MODNAME_TEXT,

    DUST_BOOT_UNIT_TEXT,
    DUST_BOOT_TYPE_PLAINTEXT,

    DUST_BOOT_UNIT_DIALOG,
    DUST_BOOT_AGENT_APP,

    DUST_BOOT_UNIT_DUST,
    DUST_BOOT_AGENT_RUNTIME,
    DUST_BOOT_AGENT_DICTIONARY,

    DUST_BOOT_UNIT_MODEL,
    DUST_BOOT_TYPE_ENTITY,
    DUST_BOOT_REF_UNIT,
    DUST_BOOT_INT_ID,
    DUST_BOOT_REF_PRIMARYTYPE,
    DUST_BOOT_REF_GLOBALID,
    DUST_BOOT_REF_OWNER,
    DUST_BOOT_REF_TAGS,
    DUST_BOOT_
};

enum DustVisitState
{
    DUST_VISIT_OPEN = DUST_BOOT_,
    DUST_VISIT_BEGIN,
    DUST_VISIT_VALUE,
    DUST_VISIT_END,
    DUST_VISIT_CLOSE,
    DUST_VISIT_
};

#define DUST_LAST_CONST_RUNTIME DUST_VISIT_

extern "C" class DustTextDictionary: public DustNativeLogic
{
public:
    virtual ~DustTextDictionary(){};

    virtual DustEntity getTextToken(const char* name, DustEntity txtParent = DUST_ENTITY_INVALID) = 0;
};

extern "C" class DustAccessData
{
public:
    DustAccessType access;
    DustEntity entity;
    DustEntity token;
    long key;

    union
    {
        long valLong;
        double valDouble;
    };

    DustAccessData(DustAccessType a, DustEntity e, DustEntity t, long k = DUST_ENTITY_APPEND, long k2 = DUST_ENTITY_APPEND)
        : access(a), entity(e), token(t), key(k), valLong(k2) {}

    DustAccessData(DustEntity e, DustEntity t, long v, long k = DUST_ENTITY_APPEND)
        : access(DUST_ACCESS_SET), entity(e), token(t), key(k), valLong(v) {}

    DustAccessData(DustEntity e, DustEntity t, double v, long k = DUST_ENTITY_APPEND)
        : access(DUST_ACCESS_SET), entity(e), token(t), key(k), valDouble(v) { }

    void updateLong(long v, DustEntity t = DUST_ENTITY_NOCHANGE, long k = DUST_ENTITY_NOCHANGE)
    {
        valLong = v;
        if ( DUST_ENTITY_NOCHANGE != t )
        {
            token = t;
        }
        if ( DUST_ENTITY_NOCHANGE != k )
        {
            key = k;
        }
    }
};


typedef DustResultType (*DustDiscoveryVisitor)(DustVisitState state, DustAccessData &data, void* pHint);

class DustDiscovery
{
public:
    static DustEntity getTextToken(const char* name, DustEntity txtParent = DUST_ENTITY_INVALID);
    static DustResultType visit(DustAccessData &start, DustDiscoveryVisitor visitor, void* pHint = 0);
};

extern "C" class DustRuntime: public DustNativeLogic
{
protected:
    void setBootToken(DustToken *pToken, DustEntity entity);

public:
    virtual ~DustRuntime()
    {
    }

    virtual DustEntity getUnit(const char* name, DustEntity constId = DUST_ENTITY_APPEND) = 0;
    virtual DustEntity getTokenEntity(DustEntity unit, const char* name, DustEntity primaryType, DustEntity constId = DUST_ENTITY_APPEND) = 0;
    virtual DustEntity getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType = DUST_COLL_SINGLE, DustEntity constId = DUST_ENTITY_APPEND) = 0;

    virtual long getMemberCount(DustEntity entity, DustEntity token) = 0;
    virtual DustEntity getMemberKey(DustEntity entity, DustEntity token, long idx) = 0;

    virtual bool access(DustAccessData &access) = 0;

// Entity native content access
    virtual void* getNative(DustEntity entity, DustEntity type = DUST_ENTITY_APPEND, bool createIfMissing = true) = 0;

    virtual DustEntity getTextToken(const char* name, DustEntity txtParent) = 0;
    virtual DustResultType visit(DustAccessData &start, DustDiscoveryVisitor visitor, void* pHint) = 0;
};

#define DUST_FNAME_GET_MODULE "getModule"
#define DUST_FNAME_INIT_MODULE "initModule"

typedef DustModule* (*getModule_t)();
typedef void (*initModule_t)(DustRuntime*);

extern "C" void initModule(DustRuntime *pRuntime);

#endif /* DUSTKERNEL_H_ */
