#include "DplStl.h"

#include <iostream>

using namespace std;

DplStlDataValue::DplStlDataValue()
    :key(DUST_ENTITY_APPEND), valPtrRef(NULL) {}

DplStlDataValue::DplStlDataValue(const DplStlDataValue &src, DplStlDataVariant *pVar)
{
    key = src.key;

    switch ( pVar->pTokenInfo->valType )
    {
    case DUST_VAL_INTEGER:
        valLong = src.valLong;
        break;
    case DUST_VAL_REAL:
        valDouble = src.valDouble;
        break;
    case DUST_VAL_REF:
        valPtrRef = (src.valPtrRef->pVariant == pVar)
                    ? src.valPtrRef
                    : new DplStlDataRef(pVar, src.valPtrRef->eSource, src.valPtrRef->eTarget);
        break;
    default:
        valPtrRef = NULL;
        break;
    }
}

DplStlDataValue::~DplStlDataValue()
{
    if ( valPtrRef )
    {
        delete valPtrRef;
        valPtrRef = NULL;
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
        if ( valPtrRef )
        {
            return ad.valLong == valPtrRef->eTarget;
        }
        else
        {
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
        ad.valLong = valPtrRef ? valPtrRef->eTarget : DUST_ENTITY_INVALID;
        return true;
    default:
        return false;
    }
}

bool DplStlDataValue::setRef(DustEntity k, DplStlDataRef *pR)
{
    if ( valPtrRef )
    {
        delete valPtrRef;
    }
    key = k;
    valPtrRef = pR;

    return true;
}

DplStlDataVariant::DplStlDataVariant(DplStlTokenInfo *pTI)
    :pTokenInfo(pTI), pColl(0)
{
    value.valPtrRef = 0;
}

DplStlDataVariant::DplStlDataVariant(const DplStlDataVariant &src)
    : pTokenInfo(src.pTokenInfo), value(src.value, this), pColl(0)
{
    int s = src.pColl ? src.pColl->size() : 0;

    if ( s )
    {
        pColl = new vector<DplStlDataValue*>();
        pColl->resize(s);
        for ( int i = 0; i < s; ++i )
        {
            pColl->push_back(new DplStlDataValue((*src.pColl->at(i)), this));
        }
    }
}

DplStlDataVariant::~DplStlDataVariant()
{
    if ( pColl )
    {
        value.valPtrRef = NULL;

        for ( int i = pColl->size(); i-->0; )
        {
            delete pColl->at(i);
        }
        pColl->clear();
        delete pColl;
    }
    else
    {
        if (DUST_VAL_REF != pTokenInfo->valType )
        {
            value.valPtrRef = NULL;
        }
    }
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
                if ((0 <= ad.key) && (ad.key < s))
                {
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
            if ( (0 == ad.key) && ((DUST_COLL_ARR == ct) || (DUST_COLL_SET == ct)) )
            {
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
        pColl->push_back(new DplStlDataValue(value, this));
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

DplStlDataEntity::DplStlDataEntity(long id_, DustEntity primaryType_)
    :id(id_), primaryType(primaryType_), pNative(NULL)
{
    DustAccessData ad(id_, DUST_BOOT_INT_ID, id_);
    access(ad);
    ad.token = DUST_BOOT_REF_PRIMARYTYPE;
    ad.valLong = primaryType_;
    access(ad);
}

DplStlDataEntity::DplStlDataEntity(DplStlDataEntity &src)
    :id(src.id), primaryType(src.primaryType), pNative(NULL)
{
    for (VarPtrIterator it = src.model.begin(); it != src.model.end(); ++it)
    {
        model[it->first] = new DplStlDataVariant(*(it->second));
    }
}

DplStlDataEntity::~DplStlDataEntity()
{
    for (VarPtrIterator it = model.begin(); it != model.end(); ++it)
    {
        delete it->second;
    }

    if ( pNative )
    {
        DplStlRuntime* pRT = DplStlRuntime::getRuntime();
        for (PtrIterator it = pNative->begin(); it != pNative->end(); ++it)
        {
            pRT->deleteNative(it->first, it->second);
        }
        delete pNative;
    }
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

void *DplStlDataEntity::getNative(DustEntity token)
{
    return pNative ? mapOptGet((*pNative), token) : NULL;
}

void* DplStlDataEntity::setNative(DustEntity token, void *ptr)
{
    void *pOrig = NULL;

    if (!pNative)
    {
        pNative = new map<DustEntity, void*>();
    }
    else
    {
        pOrig = mapOptGet((*pNative), token);
    }

    (*pNative)[token] = ptr;

    return pOrig;
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
        DplStlTokenInfo *pTI = DplStlRuntime::getCurrentThread()->getApp()->getTokenInfo(ad.token);
        pVar = new DplStlDataVariant(pTI);
        model[ad.token] = pVar;
        ret = pVar->setValue(pTI->valType, ad, &pVar->value);
    }
    return ret;
}

void DplStlDataEntity::setType(DustAccessData &ad, DplStlDataEntity *pSrc)
{
    // copy type content
}


DplStlDataStore::DplStlDataStore(DplStlDataStore *pParent_)
    :pParent(pParent_), nextId(pParent_ ? pParent_->nextId + 1 : DUST_LAST_CONST_RUNTIME)
{
}

DplStlDataStore::~DplStlDataStore()
{
    for ( EntityPtrIterator it = entities.begin(); it != entities.end(); ++it)
    {
        delete it->second;
    }
    entities.clear();
}

void DplStlDataStore::overwrite(DustEntity id, DplStlDataEntity *pE)
{
    DplStlDataEntity *pOrig = mapOptGet(entities, id);

    if ( pOrig )
    {
        delete pOrig;
    }

    entities[id] = pE;
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
        if ( pParent && !pEntity )
        {
            pEntity = pParent->getEntity(id, primaryType);
        }
    }

    if ( !pEntity )
    {
        pEntity = new DplStlDataEntity(id, primaryType);
        entities[id] = pEntity;
    }

    return pEntity;
}

void DplStlDataStore::init(DplStlDataStore *pParent_)
{
    entities.clear();
    pParent = pParent_;
}

void DplStlDataStore::commit()
{
    if ( pParent )
    {
        for ( EntityPtrIterator it = entities.begin(); it != entities.end(); ++it )
        {
            pParent->overwrite(it->first, it->second);
        }
        entities.clear();
    }
}
void DplStlDataStore::rollback()
{
    if ( pParent )
    {

    }
};
