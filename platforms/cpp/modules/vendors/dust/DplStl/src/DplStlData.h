#ifndef DPLSTLDATA_H_INCLUDED
#define DPLSTLDATA_H_INCLUDED

#include <DustRuntime.h>

#include <vector>
#include <map>

using namespace std;

class DplStlDataRef;
class DplStlDataStore;

class DustTokenInfo
{
public:
    DustValType valType;
    DustCollType collType;

    DustTokenInfo(DustValType valType, DustCollType collType)
        : valType(valType), collType(collType)
    {};
};

union DplStlDataValue
{
    long valLong;
    double valDouble;
    DplStlDataRef *valRef;
};

class DplStlDataVariant
{
    DustTokenInfo *pTokenInfo;

    DplStlDataValue value;
    vector<DplStlDataValue*>* collection;

public:
    DplStlDataVariant(DustTokenInfo *pTI);
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
    DustEntity eKey;

public:
    DplStlDataRef(DplStlDataVariant *pVariant_, DustEntity eToken_, DustEntity eSource_, DustEntity eTarget_, DustEntity eKey_);
    ~DplStlDataRef();

    friend class DplStlRuntime;
    friend class DplStlDataEntity;
    friend class DplStlDataVariant;

};

class DplStlDataEntity
{
    DplStlDataStore *pStore;
    const long id;
    const DustEntity primaryType;

    map<DustEntity, DplStlDataVariant*> model;
    map<DustEntity, void*> native;

    DplStlDataVariant *getVariant(DustEntity token, bool createIfMissing);

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
    map<DustEntity, DustTokenInfo*> tokenInfo;

public:
    DplStlDataStore(long nextId_);
    ~DplStlDataStore();

    DustTokenInfo* getTokenInfo(DustEntity token);

    DplStlDataEntity* getEntity(long id = DUST_ENTITY_APPEND, DustEntity primaryType = DUST_ENTITY_INVALID);

    friend class DplStlDataEntity;
    friend class DplStlRuntime;
};

#endif // DPLSTLDATA_H_INCLUDED
