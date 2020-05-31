#ifndef DUSTAPI_H_
#define DUSTAPI_H_

typedef long DustEntity;

#define DUST_ENTITY_NOCHANGE -2
#define DUST_ENTITY_APPEND -1
#define DUST_ENTITY_INVALID 0

#define DUST_SEP_ID "."
#define DUST_SEP_UNIT ":"

#define mapContains(m, k) (m.find( k ) != m.end())
#define mapOptGet(m, k) (((m).find( k ) != (m).end()) ? (m)[k] : NULL)
#define findEntity(m, k) (((m).find( k ) != (m).end()) ? (m)[k] : DUST_ENTITY_INVALID)

enum DustResultType
{
    DUST_RESULT_NOTIMPLEMENTED = DUST_ENTITY_INVALID,
    DUST_RESULT_REJECT,
    DUST_RESULT_ACCEPT_PASS,
    DUST_RESULT_ACCEPT,
    DUST_RESULT_ACCEPT_READ,
    DUST_RESULT_READ,
    DUST_RESULT_
};

enum DustEventType
{
    DUST_EVENT_CRITICAL = DUST_RESULT_,
    DUST_EVENT_ERROR,
    DUST_EVENT_WARNING,
    DUST_EVENT_INFO,
    DUST_EVENT_TRACE,
    DUST_EVENT_DEBUG,
    DUST_EVENT_
};

enum DustCtxType
{
    DUST_CTX_SELF = DUST_EVENT_,
    DUST_CTX_DIALOG,
    DUST_CTX_APP,
    DUST_CTX_SYSTEM,
    DUST_CTX_,
};

enum DustAccessType
{
    DUST_ACCESS_GET = DUST_CTX_,
    DUST_ACCESS_SET,
    DUST_ACCESS_MOVE,
    DUST_ACCESS_REMOVE,
    DUST_ACCESS_CLEAR,
    DUST_ACCESS_CREATE,
    DUST_ACCESS_DELETE,
    DUST_ACCESS_
};

enum DustIdeaType
{
    DUST_IDEA_UNIT = DUST_ACCESS_,
    DUST_IDEA_TYPE,
    DUST_IDEA_MEMBER,
    DUST_IDEA_AGENT,
    DUST_IDEA_TAG,

    DUST_NATIVE_CONSTANT,
    DUST_NATIVE_SERVICE,
    DUST_NATIVE_COMMAND,

    DUST_IDEA_
};

enum DustValType
{
    DUST_VAL_INTEGER = DUST_IDEA_,
    DUST_VAL_REAL,
    DUST_VAL_REF,

    DUST_VAL_
};

enum DustCollType
{
    DUST_COLL_SINGLE = DUST_VAL_,
    DUST_COLL_SET,
    DUST_COLL_ARR,
    DUST_COLL_MAP,

    DUST_COLL_
};

#define DUST_LAST_CONST_API DUST_COLL_

extern "C" class DustNativeResource
{
public:
    virtual ~DustNativeResource()
    {
    }

    virtual DustResultType DustResourceInit()
    {
        return DUST_RESULT_ACCEPT;
    }
    virtual DustResultType DustResourceRelease()
    {
        return DUST_RESULT_ACCEPT;
    }
};

extern "C" class DustNativeAction
{
public:
    virtual ~DustNativeAction()
    {
    }
    virtual DustResultType DustActionExecute()
    {
        return DUST_RESULT_NOTIMPLEMENTED;
    }
};

extern "C" class DustNativeLogic: public DustNativeResource, public DustNativeAction
{
public:
    virtual ~DustNativeLogic()
    {
    }
};

class DustToken;

extern "C" class DustToken
{
    DustEntity primaryType;
    const char* name;
    DustToken* parent;

    DustValType valType;
    DustCollType collType;

    DustEntity entity;

public:
    DustToken(const char* unitName)
        : primaryType(DUST_IDEA_UNIT), name(unitName), parent(0),
          valType(DUST_VAL_), collType(DUST_COLL_),
          entity(DUST_ENTITY_APPEND) {}

    DustToken(DustToken &unit, const char* ideaName, DustEntity primaryType_)
        : primaryType(primaryType_), name(ideaName), parent(&unit),
          valType(DUST_VAL_), collType(DUST_COLL_),
          entity(DUST_ENTITY_APPEND) {}

    DustToken(DustToken &parent_, const char* memberName, DustValType valType_, DustCollType collType_ = DUST_COLL_SINGLE)
        : primaryType(DUST_IDEA_MEMBER), name(memberName), parent(&parent_),
          valType(valType_), collType(collType_),
          entity(DUST_ENTITY_APPEND) {}

    DustEntity getPrimaryType() const
    {
        return primaryType;
    }
    DustValType getValType() const
    {
        return valType;
    }
    DustCollType getCollType() const
    {
        return collType;
    }

    operator DustEntity();

    friend class DustData;
    friend class DustRuntime;
};

class DustRef
{
private:
    DustEntity entity;
    DustToken *pToken;

public:
    DustRef(DustCtxType ctx = DUST_CTX_SELF);
    operator DustEntity();
    DustRef& operator >> (long key);
    DustRef& operator >> (DustToken &token);
};

class DustData
{
private:
    static DustEntity getTokenEntity(DustToken* pToken, DustEntity constId = DUST_ENTITY_APPEND);

public:
// Entity creation and access
//    static DustEntity getEntityByPath(DustEntity ctx, ...);
    static DustEntity createEntity(DustEntity primaryType);
    static bool deleteEntity(DustEntity entity);

    static long getMemberCount(DustEntity entity, DustEntity token);
    static DustEntity getMemberKey(DustEntity entity, DustEntity token, long idx);
    static bool clearMember(DustEntity entity, DustEntity token);
    static bool moveMember(DustEntity entity, DustEntity token, long keyFrom, long keyTo);

    static long getInteger(DustEntity entity, DustEntity token, long defValue = 0, long key = DUST_ENTITY_APPEND);
    static double getReal(DustEntity entity, DustEntity token, double defValue = 0.0, long key = DUST_ENTITY_APPEND);
    static DustEntity getRef(DustEntity entity, DustEntity token, DustEntity defValue = DUST_ENTITY_INVALID, long key = DUST_ENTITY_APPEND);

    static bool setInteger(DustEntity entity, DustEntity token, long val, long key = DUST_ENTITY_APPEND);
    static bool setReal(DustEntity entity, DustEntity token, double val, long key = DUST_ENTITY_APPEND);
    static bool setRef(DustEntity entity, DustEntity token, DustEntity target, long key = DUST_ENTITY_APPEND);

    static bool removeInteger(DustEntity entity, DustEntity token, long val, long key = DUST_ENTITY_APPEND);
    static bool removeReal(DustEntity entity, DustEntity token, double val, long key = DUST_ENTITY_APPEND);
    static bool removeRef(DustEntity entity, DustEntity token, DustEntity target, long key = DUST_ENTITY_APPEND);

// Entity native content access
    static void* getNative(DustEntity entity, DustEntity type = DUST_ENTITY_APPEND, bool createIfMissing = true);

    friend class DustToken;
    friend class DustRuntime;
};

#endif /* DUSTAPI_H_ */
