#ifndef DPLSTLDATA_H_INCLUDED
#define DPLSTLDATA_H_INCLUDED

#include <DustApi.h>

#include <vector>
#include <map>

using namespace std;

class DplStlDataRef;

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
    map<DustEntity, DplStlDataVariant*> model;
    map<DustEntity, void*> native;

public:
    DplStlDataEntity();
    ~DplStlDataEntity();
};

class DplStlDataStore {
    DplStlDataStore *pParent;

    long nextId;
    map<DustEntity, DplStlDataEntity*> entities;

public:
    DplStlDataStore(long nextId_);
    ~DplStlDataStore();

    DplStlDataEntity* createEntity(DustEntity primaryType, DustEntity eGlobalId, DustEntity requiredId = DUST_ENTITY_INVALID);
};

#endif // DPLSTLDATA_H_INCLUDED
