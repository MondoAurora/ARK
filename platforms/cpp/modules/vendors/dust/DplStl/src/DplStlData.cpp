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
        if ( valRef ) {
            return ad.valLong == valRef->eTarget;
        } else {
            return false;
        }
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
        DustUtils::log(DUST_EVENT_ERROR) << "Improper valType ";
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
        ad.valLong = valRef ? valRef->eTarget : DUST_ENTITY_INVALID;
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
                if ((0 <= ad.key) && (ad.key < s)) {
                    return pColl->at(ad.key);
                }
                // no break
            case DUST_COLL_MAP:
                for ( int i = 0; i < s; ++i )
                {
                    pv = pColl->at(i);
                    if ( matchValue(vt, ct, ad, pv))
                    {
                        return pv;
                    }
                }
                ret = NULL;
                break;
            default:
                break;
            }
        }
        else
        {
            if ( (0 == ad.key) && ((DUST_COLL_ARR == ct) || (DUST_COLL_SET == ct)) ) {
                return ret;
            }

            if ( !matchValue(vt, ct, ad, ret))
            {
                ret = NULL;
            }
        }
    }

    return ret;
}

bool DplStlDataVariant::setValue(DustValType vt, DustAccessData &ad, DplStlDataValue * pVal)
{
    return ( DUST_VAL_REF == vt )
                      ? pVal->setRef(ad.key, new DplStlDataRef(this, ad.entity, ad.valLong))
                      : pVal->loadFrom(vt, ad);
}

DplStlDataValue * DplStlDataVariant::add(DustValType vt, DustAccessData &ad)
{
    if ( !pColl )
    {
        pColl = new vector<DplStlDataValue*>();
        pColl->push_back(new DplStlDataValue(vt, value));
    }

    DplStlDataValue *pv = new DplStlDataValue();
    setValue(vt, ad, pv);
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
                ret = setValue(vt, ad, pVal);
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

DplStlDataRef::DplStlDataRef(DplStlDataVariant *pVariant_, DustEntity eSource_, DustEntity eTarget_)
    :pVariant(pVariant_), eSource(eSource_), eTarget(eTarget_)
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

DplStlDataVariant *DplStlDataEntity::getVariant(DustEntity token)
{
    DplStlDataVariant *pVar = mapOptGet(model, token);
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

    DplStlDataVariant *pVar = getVariant(ad.token);

    if ( pVar )
    {
        bool single = ( DUST_COLL_SINGLE == pVar->pTokenInfo->collType );
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
    else if ( DUST_ACCESS_SET == ad.access )
    {
        DplStlTokenInfo *pTI = pStore->getTokenInfo(ad.token);
        pVar = new DplStlDataVariant(pTI);
        model[ad.token] = pVar;
        ret = pVar->setValue(pTI->valType, ad, &pVar->value);
    }
    return ret;
}

void DplStlDataEntity::setType(DustAccessData &ad, DplStlDataEntity *pSrc) {
    // copy type content
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
//        DplStlDataEntity *pTokenEntity = getEntity(token);

        DustValType vT = (DustValType) DustUtils::getSingleTag(token, DustUnitMindIdea::DustTagVal, DUST_VAL_INTEGER);
        DustCollType cT = (DustCollType) DustUtils::getSingleTag(token, DustUnitMindIdea::DustTagColl, DUST_COLL_SINGLE);

        cout << "Dynamic token def " << token << ", vT " << vT << ", cT " << cT << endl;

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

