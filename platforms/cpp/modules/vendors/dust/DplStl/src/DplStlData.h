#ifndef DPLSTLDATA_H_INCLUDED
#define DPLSTLDATA_H_INCLUDED

#include <DustKernel.h>

#include <vector>
#include <map>

using namespace std;

class DplStlDataRef;
class DplStlDataVariant;
class DplStlDataStore;

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
        DplStlDataRef *valPtrRef;
    };


public:
    DplStlDataValue();
    DplStlDataValue(const DplStlDataValue &src, DplStlDataVariant *pVariant);
    ~DplStlDataValue();

    bool match(DustValType vT, DustAccessData &ad);
    bool loadFrom(DustValType vT, DustAccessData &ad);
    bool writeTo(DustValType vT, DustAccessData &ad);

    bool setRef(DustEntity key, DplStlDataRef *pRef);

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

    friend class DplStlRuntime;
    friend class DplStlDataEntity;
    friend class DplStlDataValue;
};

class DplStlDataRef
{
    DplStlDataVariant *pVariant;

    DustEntity eSource;
    DustEntity eTarget;

public:
    DplStlDataRef(DplStlDataVariant *pVariant_, DustEntity eSource_, DustEntity eTarget_);
    ~DplStlDataRef();

    friend class DplStlRuntime;
    friend class DplStlDataEntity;
    friend class DplStlDataVariant;
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

    bool access(DustAccessData &ad);
    void setType(DustAccessData &ad, DplStlDataEntity *pSrc);

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

    void commit();
    void rollback();

    friend class DplStlDataEntity;
    friend class DplStlRuntimeState;
    friend class DplStlRuntime;
};

#endif // DPLSTLDATA_H_INCLUDED
