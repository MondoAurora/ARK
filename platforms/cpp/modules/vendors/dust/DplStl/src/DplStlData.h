#ifndef DPLSTLDATA_H_INCLUDED
#define DPLSTLDATA_H_INCLUDED

#include <DustApi.h>

#include <vector>
#include <map>

using namespace std;

class DplStlDataRef;
class DplStlDataStore;

union DplStlDataValue {
    long valLong;
    double valDouble;
    DplStlDataRef *valRef;
};

class DplStlDataVariant {
    DustValType valType;
    DustCollType collType;

    DplStlDataValue value;
    vector<DplStlDataValue*>* collection;

public:
    DplStlDataVariant();
    ~DplStlDataVariant();
};

class DplStlDataRef {
    DustEntity eSource;
    DustEntity eTarget;
    DustEntity eToken;

    DplStlDataVariant *pVariant;

public:
    DplStlDataRef();
    ~DplStlDataRef();
};

class DplStlDataEntity {
    const DplStlDataStore *pStore;
    const long id;
    const DustEntity primaryType;

    map<DustEntity, DplStlDataVariant*> model;
    map<DustEntity, void*> native;

public:
    DplStlDataEntity(DplStlDataStore *pStore_, long id_, DustEntity primaryType_);
    ~DplStlDataEntity();

    friend class DplStlRuntime;
};

class DplStlDataStore {
    DplStlDataStore *pParent;

    long nextId;
    map<DustEntity, DplStlDataEntity*> entities;

public:
    DplStlDataStore(long nextId_);
    ~DplStlDataStore();

    DplStlDataEntity* getEntity(long id = DUST_ENTITY_APPEND, DustEntity primaryType = DUST_ENTITY_INVALID);
};

#endif // DPLSTLDATA_H_INCLUDED
