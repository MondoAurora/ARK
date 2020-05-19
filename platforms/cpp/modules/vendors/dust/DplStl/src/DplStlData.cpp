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

bool DplStlDataVariant::access(DustAccessData &ad)
{
    bool ret = false;
    DplStlDataValue *pVal = &value;

    switch ( ad.access )
    {
       case DUST_ACCESS_GET:
            ret = true;
            switch ( valType )
            {
            case DUST_VAL_INTEGER:
                ad.valLong = pVal->valLong;
                break;
            case DUST_VAL_REAL:
                ad.valDouble = pVal->valDouble;
                break;
            case DUST_VAL_REF:
                ad.valLong = pVal->valRef->eTarget;
                break;
            case DUST_VAL_:
                ret = false;
                break;
            }
        break;
    case DUST_ACCESS_SET:
        ret = true;

        switch ( valType )
        {
        case DUST_VAL_INTEGER:
            pVal->valLong = ad.valLong;
            break;
        case DUST_VAL_REAL:
            pVal->valDouble = ad.valDouble;
            break;
        case DUST_VAL_REF:
            pVal->valRef = new DplStlDataRef(this, ad.token, ad.entity, ad.valLong, ad.key);
            break;
        case DUST_VAL_:
            ret = false;
            break;
        }
        break;
    default:
        break;
    }

    return ret;
}

//void DplStlDataVariant::changeRef(DustAccessType change, DustEntity token, DustEntity source, DustEntity target, DustEntity key)
//{
//    if ( value.valRef )
//    {
//        delete value.valRef;
//    }
//
//    value.valRef = new DplStlDataRef(this, token, source, target, key);
//}

DplStlDataRef::DplStlDataRef(DplStlDataVariant *pVariant_, DustEntity eToken_, DustEntity eSource_, DustEntity eTarget_, DustEntity eKey_)
    :pVariant(pVariant_), eToken(eToken_), eSource(eSource_), eTarget(eTarget_), eKey(eKey_)
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

DplStlDataVariant *DplStlDataEntity::getVariant(DustEntity token, bool createIfMissing)
{
    DplStlDataVariant *pVar = mapOptGet(model, token);

    if ( !pVar && createIfMissing)
    {
        pVar = new DplStlDataVariant(pStore->tokenInfo[token]);
        model[token] = pVar;
    }

    return pVar;
}

bool DplStlDataEntity::access(DustAccessData &ad)
{
    bool ret = false;

    DplStlDataVariant *pVar = getVariant(ad.token, DUST_ACCESS_SET == ad.access);

    if ( pVar )
    {
        switch ( ad.access )
        {
        case DUST_ACCESS_CLEAR:
            delete pVar;
            model.erase(ad.token);
            ret = true;
            break;
        default:
            pVar->access(ad);
        }
    }

    return ret;
}


//void DplStlDataEntity::changeRef(DustAccessType change, DustEntity token, DustEntity target, DustEntity key)
//{
//    DplStlDataVariant *pVar = getVariant(token, DUST_ACCESS_SET == change);
//
//    switch( change )
//    {
//    case DUST_ACCESS_SET:
//        pVar->changeRef(change, token, id, target, key);
//        break;
//    default:
//        break;
//    }
//
//}


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

