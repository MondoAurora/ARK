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

DplStlDataEntity::DplStlDataEntity(DplStlDataStore *pStore_, long id_, DustEntity primaryType_)
    :pStore(pStore_), id(id_), primaryType(primaryType_)
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

DplStlDataEntity* DplStlDataStore::getEntity(long id, DustEntity primaryType)
{
    DplStlDataEntity *pEntity = 0;

    if ( DUST_ENTITY_APPEND == id )
    {
        id = ++nextId;
    }
    else
    {
        pEntity = findEntity(entities, id);
    }

    if ( !pEntity )
    {
        pEntity = new DplStlDataEntity(this, id, primaryType);
        entities[id] = pEntity;
    }

    return pEntity;
}

