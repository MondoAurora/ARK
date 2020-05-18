#ifndef DPLSTLDATA_H_INCLUDED
#define DPLSTLDATA_H_INCLUDED

#include <DustApi.h>

#include <vector>
#include <map>

using namespace std;

class DplStlDataRef;
class DplStlDataStore;

union DplStlDataValue
{
    long valLong;
    double valDouble;
    DplStlDataRef *valRef;
};

class DplStlDataTokenInfo
{
public:
    DustValType valType;
    DustCollType collType;
};

class DplStlDataVariant
{
    DustValType valType;
    DustCollType collType;

    DplStlDataValue value;
    vector<DplStlDataValue*>* collection;

public:
    DplStlDataVariant(DplStlDataTokenInfo &tokenInfo);
    ~DplStlDataVariant();

    void changeRef(DustChange change, DustEntity token, DustEntity source, DustEntity target, DustEntity key);

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

};

class DplStlDataEntity
{
    DplStlDataStore *pStore;
    const long id;
    const DustEntity primaryType;

    map<DustEntity, DplStlDataVariant*> model;
    map<DustEntity, void*> native;

    DplStlDataVariant *getVariant(DustChange change, DustEntity token);

public:
    DplStlDataEntity(DplStlDataStore *pStore_, long id_, DustEntity primaryType_);
    ~DplStlDataEntity();

    void changeRef(DustChange change, DustEntity token, DustEntity target, DustEntity key = DUST_ENTITY_APPEND);

    friend class DplStlRuntime;
};

class DplStlDataStore
{
    DplStlDataStore *pParent;

    long nextId;
    map<DustEntity, DplStlDataEntity*> entities;
    map<DustEntity, DplStlDataTokenInfo> tokenInfo;

public:
    DplStlDataStore(long nextId_);
    ~DplStlDataStore();

    DplStlDataEntity* getEntity(long id = DUST_ENTITY_APPEND, DustEntity primaryType = DUST_ENTITY_INVALID);

    friend class DplStlDataEntity;
};

#endif // DPLSTLDATA_H_INCLUDED
