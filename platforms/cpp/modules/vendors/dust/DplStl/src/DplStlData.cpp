#include "DplStl.h"

#include <iostream>

using namespace std;

DplStlDataValue::DplStlDataValue()
    :valLong(0) {}

bool DplStlDataValue::match(DustValType vT, DustAccessData &ad)
{
    switch ( vT )
    {
    case DUST_VAL_INTEGER:
        return ad.valLong == valLong;
    case DUST_VAL_REAL:
        return ad.valDouble == valDouble;
    case DUST_VAL_REF:
        return ad.valLong == valRef->eTarget;
    default:
        return false;
    }
}

bool DplStlDataValue::loadFrom(DustValType vT, DustAccessData &ad)
{
    switch ( vT )
    {
    case DUST_VAL_INTEGER:
        valLong = ad.valLong;
        return true;
    case DUST_VAL_REAL:
        valDouble = ad.valDouble;
        return true;
    default:
        DustUtils::log(DUST_EVENT_ERROR) << "Improper valType";
        return false;
    }
}

bool DplStlDataValue::writeTo(DustValType vT, DustAccessData &ad)
{
    switch ( vT )
    {
    case DUST_VAL_INTEGER:
        ad.valLong = valLong;
        return true;
    case DUST_VAL_REAL:
        ad.valDouble = valDouble;
        return true;
    case DUST_VAL_REF:
        ad.valLong = valRef->eTarget;
        return true;
    default:
        return false;
    }
}

DplStlDataVariant::DplStlDataVariant(DustTokenInfo *pTI)
    :pTokenInfo(pTI), pColl(0)
{
    value.valRef = 0;
}

DplStlDataVariant::~DplStlDataVariant()
{
};

DplStlDataValue* DplStlDataVariant::locate(DustAccessData &ad)
{
    DplStlDataValue* ret = &value;

    if ( DUST_COLL_SINGLE != pTokenInfo->collType )
    {
        if ( !pColl )
        {
            if ( DUST_ENTITY_APPEND == ad.key )
            {
                return &value;
            }
            else
            {
                switch (  pTokenInfo->collType )
                {
                case DUST_COLL_SET:
                    break;
                case DUST_COLL_ARR:
                    break;
                case DUST_COLL_MAP:
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
        }
    }

    return ret;
}


bool DplStlDataVariant::access(DustAccessData &ad)
{
    bool ret = false;
    DplStlDataValue *pVal = locate(ad);

    switch ( ad.access )
    {
    case DUST_ACCESS_GET:
        ret = pVal->writeTo(pTokenInfo->valType, ad);
        break;
    case DUST_ACCESS_SET:
        if ( DUST_VAL_REF == pTokenInfo->valType )
        {
            pVal->valRef = new DplStlDataRef(this, ad.token, ad.entity, ad.valLong, ad.key);
            ret = true;
        }
        else
        {
            ret = pVal->loadFrom(pTokenInfo->valType, ad);
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

void DplStlDataEntity::deleteVariant(DustEntity token, DplStlDataVariant *pVar)
{
    delete pVar;
    model.erase(token);

}

bool DplStlDataEntity::access(DustAccessData &ad)
{
    bool ret = false;

    DplStlDataVariant *pVar = getVariant(ad.token, DUST_ACCESS_SET == ad.access);
    bool single = ( DUST_COLL_SINGLE == pVar->pTokenInfo->collType );

    if ( pVar )
    {
        switch ( ad.access )
        {
        case DUST_ACCESS_CLEAR:
            deleteVariant(ad.token, pVar);
            ret = true;
            break;
        case DUST_ACCESS_REMOVE:
            if ( single )
            {
                deleteVariant(ad.token, pVar);
                ret = true;
            }
            else
            {
                ret = pVar->access(ad);
            }
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

