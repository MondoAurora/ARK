#include "DplStl.h"

#include <iostream>

using namespace std;


DplStlDataVariant::DplStlDataVariant(DplStlDataTokenInfo &tokenInfo)
:valType(tokenInfo.valType), collType(tokenInfo.collType), collection(0)
{
    value.valRef = 0;
}

DplStlDataVariant::~DplStlDataVariant()
{
};

void DplStlDataVariant::changeRef(DustChange change, DustEntity token, DustEntity source, DustEntity target, DustEntity key)
{
    if ( value.valRef )
    {
        delete value.valRef;
    }

    value.valRef = new DplStlDataRef(this, token, source, target);
}

DplStlDataRef::DplStlDataRef(DplStlDataVariant *pVariant_, DustEntity eToken_, DustEntity eSource_, DustEntity eTarget_)
    :pVariant(pVariant_), eToken(eToken_), eSource(eSource_), eTarget(eTarget_)
{}

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

DplStlDataVariant *DplStlDataEntity::getVariant(DustChange change, DustEntity token)
{
    DplStlDataVariant *pVar = mapOptGet(model, token);

    if ( !pVar )
    {
        switch( change )
        {
        case DUST_CHANGE_REF_SET:
            pVar = new DplStlDataVariant(pStore->tokenInfo[token]);
            model[token] = pVar;
            break;
        default:
            break;
        }
    }

    return pVar;
}


void DplStlDataEntity::changeRef(DustChange change, DustEntity token, DustEntity target, DustEntity key)
{
    DplStlDataVariant *pVar = getVariant(change, token);

    switch( change )
    {
    case DUST_CHANGE_REF_SET:
        pVar->changeRef(change, token, id, target, key);
        break;
    default:
        break;
    }

}


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

