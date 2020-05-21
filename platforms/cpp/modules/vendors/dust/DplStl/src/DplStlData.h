#ifndef DPLSTLDATA_H_INCLUDED
#define DPLSTLDATA_H_INCLUDED

#include <DustRuntime.h>

#include <vector>
#include <map>

using namespace std;

class DplStlDataRef;
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
        DplStlDataRef *valRef;
    };

public:
    DplStlDataValue();
    DplStlDataValue(DustValType vT, const DplStlDataValue &src);

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
    DplStlDataValue * add(DustValType vt, DustAccessData &ad);

public:
    DplStlDataVariant(DplStlTokenInfo *pTI);
    ~DplStlDataVariant();

    bool access(DustAccessData &ad);

    friend class DplStlRuntime;
    friend class DplStlDataEntity;
};

class DplStlDataRef
{
    DplStlDataVariant *pVariant;

    DustEntity eToken;
    DustEntity eSource;
    DustEntity eTarget;

public:
    DplStlDataRef(DplStlDataVariant *pVariant_, DustEntity eToken_, DustEntity eSource_, DustEntity eTarget_);
    ~DplStlDataRef();

    friend class DplStlRuntime;
    friend class DplStlDataEntity;
    friend class DplStlDataVariant;
    friend class DplStlDataValue;
};

class DplStlDataEntity
{
    DplStlDataStore *pStore;
    const long id;
    const DustEntity primaryType;

    map<DustEntity, DplStlDataVariant*> model;
    map<DustEntity, void*> native;

    DplStlDataVariant *getVariant(DustEntity token, bool createIfMissing);

    void deleteVariant(DustEntity token, DplStlDataVariant *var);

public:
    DplStlDataEntity(DplStlDataStore *pStore_, long id_, DustEntity primaryType_);
    ~DplStlDataEntity();

    bool access(DustAccessData &ad);

    friend class DplStlRuntime;
};

class DplStlDataStore
{
    DplStlDataStore *pParent;

    long nextId;
    map<DustEntity, DplStlDataEntity*> entities;
    map<DustEntity, DplStlTokenInfo*> tokenInfo;

public:
    DplStlDataStore(long nextId_);
    ~DplStlDataStore();

    DplStlTokenInfo* getTokenInfo(DustEntity token);

    DplStlDataEntity* getEntity(long id = DUST_ENTITY_APPEND, DustEntity primaryType = DUST_ENTITY_INVALID);

    friend class DplStlDataEntity;
    friend class DplStlRuntime;
};

#endif // DPLSTLDATA_H_INCLUDED
