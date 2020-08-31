#ifndef DPLSTLDATA_H_INCLUDED
#define DPLSTLDATA_H_INCLUDED

#include <DustKernel.h>

#include <vector>
#include <map>
#include <set>

using namespace std;

//class DplStlDataRef;
class DplStlDataVariant;
class DplStlDataStore;
class DplStlDataVisit;
class DplStlRuntime;

class DplStlTokenInfo
{
public:
    DustValType valType;
    DustCollType collType;

    DplStlTokenInfo(DustValType valType, DustCollType collType)
        : valType(valType), collType(collType)
    {};
};

class DplStlDataValue
{
    DustEntity key;

    union
    {
        long valLong;
        double valDouble;
        DustEntity valTarget;
//        DplStlDataRef *valPtrRef;
    };


public:
    DplStlDataValue();
    DplStlDataValue(const DplStlDataValue &src, DplStlDataVariant *pVariant);
    ~DplStlDataValue();

    bool match(DustValType vT, DustAccessData &ad);
    bool loadFrom(DustValType vT, DustAccessData &ad);
    bool writeTo(DustValType vT, DustAccessData &ad);

    void visit(DustValType vT, DplStlDataVisit *pVisit);


//    bool setRef(DustEntity key, DplStlDataRef *pRef);

    friend class DplStlDataVariant;
    friend class DplStlRuntime;
};

class DplStlDataVariant
{
    DplStlTokenInfo *pTokenInfo;

    DplStlDataValue value;
    vector<DplStlDataValue*>* pColl;

    bool matchValue(DustValType vt, DustCollType ct, DustAccessData &ad, DplStlDataValue* pVal);
    DplStlDataValue* locateForOverride(DustAccessData &ad);

    bool setValue(DustValType vt, DustAccessData &ad, DplStlDataValue * pVal);
    DplStlDataValue * add(DustValType vt, DustAccessData &ad);

public:
    DplStlDataVariant(DplStlTokenInfo *pTI);
    DplStlDataVariant(const DplStlDataVariant &src);
    ~DplStlDataVariant();

    bool access(DustAccessData &ad);
    void visit(DplStlDataVisit *pVisit);

    friend class DplStlRuntime;
    friend class DplStlDataEntity;
    friend class DplStlDataValue;
};

typedef map<DustEntity, DplStlDataVariant*>::iterator VarPtrIterator;
typedef map<DustEntity, void*>::iterator PtrIterator;

class DplStlDataEntity
{
public:
    const long id;
    const DustEntity primaryType;

private:
    map<DustEntity, DplStlDataVariant*> model;
    map<DustEntity, void*> *pNative;

    void deleteVariant(DustEntity token, DplStlDataVariant *var);

public:
    DplStlDataEntity(DplStlDataEntity &src);
    DplStlDataEntity(long id_, DustEntity primaryType_);
    ~DplStlDataEntity();

    DplStlDataVariant *getVariant(DustEntity token);

    void *getNative(DustEntity token);
    void *setNative(DustEntity token, void *ptr);

    void setType(DustAccessData &ad, DplStlDataEntity *pSrc);

    bool access(DustAccessData &ad);
    void visit(DplStlDataVisit *pVisit);

    friend class DplStlRuntime;
};

typedef map<DustEntity, DplStlDataEntity*>::iterator EntityPtrIterator;

/**
class DplStlContext {
public:
    virtual ~DplStlContext();
    virtual DplStlDataEntity* getEntity(long id = DUST_ENTITY_APPEND, DustEntity primaryType = DUST_ENTITY_INVALID) = 0;
};
*/

class DplStlDataStore // : public DplStlContext
{
    DplStlDataStore *pParent;

    long nextId;
    map<DustEntity, DplStlDataEntity*> entities;

     void overwrite(DustEntity, DplStlDataEntity*);

public:
    DplStlDataStore(DplStlDataStore *pParent_ = NULL);
    virtual ~DplStlDataStore();

    virtual DplStlDataEntity* getEntity(long id = DUST_ENTITY_APPEND, DustEntity primaryType = DUST_ENTITY_INVALID);

    void init(DplStlDataStore *pParent);
    void loadAll(DplStlDataVisit *pVisit);

    void commit();
    void rollback();

    friend class DplStlDataEntity;
    friend class DplStlRuntimeState;
    friend class DplStlRuntime;
};

typedef  set<DustEntity>::iterator VisitIterator;

class DplStlDataVisit
{
private:
    DplStlRuntime *pRuntime;
    DustAccessData *pAd;
    DustDiscoveryVisitor visitor;
    void* pHint;

    DustResultType ret;

    set<DustEntity> visited;
    set<DustEntity> toVisit;

public:

    DplStlDataVisit(DplStlRuntime *pRuntime, DustAccessData &da, DustDiscoveryVisitor visitor, void* pHint);
    ~DplStlDataVisit();

    DustResultType execute();
    DustResultType send(DustVisitState vs);
    void optAdd(DustEntity entity);

    DustResultType getRet() {
        return ret;
    }

    DustAccessData * getAccData() {
        return pAd;
    }
};

#endif // DPLSTLDATA_H_INCLUDED
