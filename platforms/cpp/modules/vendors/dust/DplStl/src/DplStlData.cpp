#include "DplStl.h"

#include <iostream>

using namespace std;

DplStlDataValue::DplStlDataValue()
    :key(DUST_ENTITY_APPEND), valLong(0) {}

DplStlDataValue::DplStlDataValue(DustValType vT, const DplStlDataValue &src)
{
    key = src.key;

    switch ( vT )
    {
    case DUST_VAL_INTEGER:
        valLong = src.valLong;
        break;
    case DUST_VAL_REAL:
        valDouble = src.valDouble;
        break;
    case DUST_VAL_REF:
        valRef = src.valRef;
        break;
    default:
        break;
    }
}

bool DplStlDataValue::match(DustValType vT, DustAccessData &ad)
{
    if ( key != ad.key )
    {
        return false;
    }

    switch ( vT )
    {
    case DUST_VAL_INTEGER:
        return ad.valLong == valLong;
    case DUST_VAL_REAL:
        return ad.valDouble == valDouble;
    case DUST_VAL_REF:
        return valRef ? ad.valLong == valRef->eTarget : false;
    default:
        return false;
    }
}

bool DplStlDataValue::loadFrom(DustValType vT, DustAccessData &ad)
{
    key = ad.key;

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
    ad.key = key;

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

bool DplStlDataValue::setRef(DustEntity k, DplStlDataRef *pR)
{
    if ( valRef )
    {
        delete valRef;
    }
    key = k;
    valRef = pR;

    return true;
}

DplStlDataVariant::DplStlDataVariant(DplStlTokenInfo *pTI)
    :pTokenInfo(pTI), pColl(0)
{
    value.valRef = 0;
}

DplStlDataVariant::~DplStlDataVariant()
{
};

bool DplStlDataVariant::matchValue(DustValType vt, DustCollType ct, DustAccessData &ad, DplStlDataValue* pVal)
{
    switch (  ct )
    {
    case DUST_COLL_SET:
        return pVal->match(vt, ad);
    case DUST_COLL_MAP:
        return pVal->key == ad.key;
    default:
        return false;
    }
}

DplStlDataValue* DplStlDataVariant::locateForOverride(DustAccessData &ad)
{
    DplStlDataValue* ret = &value;
    DustCollType ct = pTokenInfo->collType;

    if ( DUST_COLL_SINGLE != ct )
    {
        DustValType vt = pTokenInfo->valType;
        if ( pColl )
        {
            int s = pColl->size();
            DplStlDataValue* pv;

            switch (  ct )
            {
            case DUST_COLL_ARR:
                return ((0 <= ad.key) && (ad.key < s)) ? pColl->at(ad.key) : NULL;
            case DUST_COLL_SET:
            case DUST_COLL_MAP:
                for ( int i = 0; i < s; ++i )
                {
                    pv = pColl->at(i);
                    if ( matchValue(vt, ct, ad, pv))
                    {
                        return pv;
                    }
                }
                break;
            default:
                break;
            }
        }
        else
        {
            if ( !matchValue(vt, ct, ad, ret))
            {
                ret = NULL;
            }
        }
    }

    return ret;
}

DplStlDataValue * DplStlDataVariant::add(DustValType vt, DustAccessData &ad)
{
    if ( !pColl )
    {
        pColl = new vector<DplStlDataValue*>();
        pColl->push_back(new DplStlDataValue(vt, value));
    }

    DplStlDataValue *pv = new DplStlDataValue();
    pv->loadFrom(vt, ad);
    pColl->push_back(pv);

    return pv;
}

bool DplStlDataVariant::access(DustAccessData &ad)
{
    bool ret = false;
    DustValType vt = pTokenInfo->valType;
    DplStlDataValue *pVal = locateForOverride(ad);

    switch ( ad.access )
    {
    case DUST_ACCESS_GET:
        ret = pVal ? pVal->writeTo(vt, ad) : false;
        break;
    case DUST_ACCESS_SET:
        if ( pVal )
        {
            if ( !pVal->match(vt, ad))
            {
                ret = ( DUST_VAL_REF == vt )
                      ? pVal->setRef(ad.key, new DplStlDataRef(this, ad.token, ad.entity, ad.valLong))
                      : pVal->loadFrom(vt, ad);
            }
        }
        else
        {
            add(vt, ad);
            ret = true;
        }
        break;
    case DUST_ACCESS_REMOVE:
        break;
    default:
        break;
    }

    return ret;
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
                if ( ret && pVar->pColl && pVar->pColl->empty() )
                {
                    deleteVariant(ad.token, pVar);
                }
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

DplStlTokenInfo* DplStlDataStore::getTokenInfo(DustEntity token)
{
    DplStlTokenInfo* pTI = tokenInfo[token];

    if ( !pTI )
    {
        DplStlDataEntity *pTokenEntity = getEntity(token);
        cout << "Now I should load pTI info from " << token << " : " << pTokenEntity << endl;

        DustValType vT = DUST_VAL_INTEGER;
        DustCollType cT = DUST_COLL_SINGLE;

        pTI = new DplStlTokenInfo(vT, cT);
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

