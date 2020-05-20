#include "DplStl.h"

#include <iostream>

using namespace std;


DplStlDataVariant::DplStlDataVariant(DustTokenInfo *pTI)
    :pTokenInfo(pTI), collection(0)
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
        switch ( pTokenInfo->valType )
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

        switch ( pTokenInfo->valType )
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

DplStlDataRef::DplStlDataRef(DplStlDataVariant *pVariant_, DustEntity eToken_, DustEntity eSource_, DustEntity eTarget_, DustEntity eKey_)
    :pVariant(pVariant_), eToken(eToken_), eSource(eSource_), eTarget(eTarget_), eKey(eKey_)
{}

DplStlDataRef::~DplStlDataRef()
{
};

DplStlDataEntity::DplStlDataEntity(DplStlDataStore *pStore_, long id_, DustEntity primaryType_)
    :pStore(pStore_), id(id_), primaryType(primaryType_)
{
    DustAccessData ad(id_, DUST_BOOT_INT_ID, id_);
    access(ad);
    ad.token = DUST_BOOT_REF_PRIMARYTYPE;
    ad.valLong = primaryType_;
    access(ad);
}

DplStlDataEntity::~DplStlDataEntity()
{
};

DplStlDataVariant *DplStlDataEntity::getVariant(DustEntity token, bool createIfMissing)
{
    DplStlDataVariant *pVar = mapOptGet(model, token);

    if ( !pVar && createIfMissing)
    {
        pVar = new DplStlDataVariant(pStore->getTokenInfo(token));
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
            ret = pVar->access(ad);
        }
    }

    return ret;
}

DplStlDataStore::DplStlDataStore(long nextId_)
    :nextId(nextId_)
{
}

DplStlDataStore::~DplStlDataStore()
{

}

DustTokenInfo* DplStlDataStore::getTokenInfo(DustEntity token)
{
    DustTokenInfo* pTI = tokenInfo[token];

    if ( !pTI )
    {
        DplStlDataEntity *pTokenEntity = getEntity(token);
        cout << "Now I should load pTI info from " << token << " : " << pTokenEntity << endl;

        DustValType vT = DUST_VAL_INTEGER;
        DustCollType cT = DUST_COLL_SINGLE;

        pTI = new DustTokenInfo(vT, cT);
    }

    return pTI;
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

