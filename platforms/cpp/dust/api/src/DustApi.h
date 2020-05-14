#ifndef DUSTAPI_H_
#define DUSTAPI_H_

typedef long DustEntity;

#define DUST_ENTITY_APPEND -1
#define DUST_ENTITY_INVALID 0

#define DUST_SEP_ID "."
#define DUST_SEP_UNIT ":"

#define mapContains(m, k) (m.find( k ) != m.end())
#define mapOptGet(m, k) (((m).find( k ) != (m).end()) ? (m)[k] : NULL)
#define findEntity(m, k) (((m).find( k ) != (m).end()) ? (m)[k] : DUST_ENTITY_INVALID)

enum DustProcessResult
{
    DUST_PROCESS_NOTIMPLEMENTED = DUST_ENTITY_INVALID,
    DUST_PROCESS_REJECT,
    DUST_PROCESS_ACCEPT_PASS,
    DUST_PROCESS_ACCEPT,
    DUST_PROCESS_ACCEPT_READ,
    DUST_PROCESS_READ,
    DUST_PROCESS_
};

enum DustChange
{
    DUST_CHG_REF_SET = DUST_PROCESS_,
    DUST_CHG_REF_REMOVE,
    DUST_CHG_REF_CLEAR,
    DUST_CHG_
};

enum DustIdeaType
{
    DUST_IDEA_UNIT = DUST_CHG_,
    DUST_IDEA_TYPE,
    DUST_IDEA_MEMBER,
    DUST_IDEA_AGENT,
    DUST_IDEA_CONST,
    DUST_IDEA_TAG,

    DUST_IDEA_
};

enum DustValType
{
    DUST_VAL_INT = DUST_IDEA_,
    DUST_VAL_DOUBLE,
    DUST_VAL_REF,

    DUST_VAL_
};

enum DustCollType
{
    DUST_COLL_SINGLE = DUST_ENTITY_INVALID,
    DUST_COLL_SET = DUST_VAL_,
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

    virtual DustProcessResult DustResourceInit()
    {
        return DUST_PROCESS_ACCEPT;
    }
    virtual DustProcessResult DustResourceRelease()
    {
        return DUST_PROCESS_ACCEPT;
    }
};

extern "C" class DustNativeAction
{
public:
    virtual ~DustNativeAction()
    {
    }
    virtual DustProcessResult DustActionExecute()
    {
        return DUST_PROCESS_NOTIMPLEMENTED;
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

class DustMeta
{
public:
    static DustEntity getTokenEntity(DustToken* pToken);
    static DustEntity getUnit(const char* name);
    static DustEntity getIdeaEntity(DustEntity unit, const char* name, DustIdeaType ideaType, DustEntity constId = DUST_ENTITY_INVALID);
    static DustEntity getMemberEntity(DustEntity type, const char* name, DustValType valType, DustCollType collType = DUST_COLL_SINGLE, DustEntity constId = DUST_ENTITY_INVALID);
};

extern "C" class DustToken {
    DustIdeaType ideaType;
    const char* name;
    const DustEntity parent;

    DustValType valType;
    DustCollType collType;

   DustEntity entity;

public:
    DustToken(const char* unitName)
    : ideaType(DUST_IDEA_UNIT), name(unitName), parent(DUST_ENTITY_INVALID),
        valType(DUST_VAL_), collType(DUST_COLL_),
        entity(DUST_ENTITY_APPEND) {}

    DustToken(DustEntity unit, const char* ideaName, DustIdeaType ideaType, DustEntity constId = DUST_ENTITY_APPEND)
    : ideaType(ideaType), name(ideaName), parent(unit),
        valType(DUST_VAL_), collType(DUST_COLL_),
        entity(constId) {}

    DustToken(DustEntity parent_, const char* memberName, DustValType valType_, DustCollType collType_ = DUST_COLL_SINGLE, DustEntity constId = DUST_ENTITY_APPEND)
    : ideaType(DUST_IDEA_MEMBER), name(memberName), parent(parent_),
        valType(valType_), collType(collType_),
        entity(constId) {}

    operator DustEntity();

    friend class DustMeta;
};

class DustData
{
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
    static DustEntity getRef(DustEntity entity, DustEntity token, int key = DUST_ENTITY_APPEND);

    static bool setRef(DustEntity entity, DustEntity token, DustEntity target, int key = DUST_ENTITY_APPEND);

// Entity native content access
    static void* getNative(DustEntity entity, DustEntity type);
};

#endif /* DUSTAPI_H_ */
