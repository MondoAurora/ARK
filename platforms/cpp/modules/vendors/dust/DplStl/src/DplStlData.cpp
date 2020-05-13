#include "DplStl.h"

#include <iostream>

using namespace std;


DplStlDataVariant::DplStlDataVariant()
    : collection(0)
{}

DplStlDataVariant::~DplStlDataVariant()
{
};

DplStlDataRef::DplStlDataRef() {}

DplStlDataRef::~DplStlDataRef()
{
};

DplStlDataEntity::DplStlDataEntity()
{
}

DplStlDataEntity::~DplStlDataEntity()
{
};

DplStlDataStore::DplStlDataStore(long nextId_)
:nextId(nextId_)
{
}

DplStlDataStore::~DplStlDataStore()
{

}

DplStlDataEntity* DplStlDataStore::createEntity(DustEntity primaryType, DustEntity eGlobalId, DustEntity requiredId) {
    return NULL;
}
