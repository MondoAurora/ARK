#include "DustRuntime.h"

DustRuntime *apiRuntime = 0;

extern "C" void initModule(DustRuntime *pRuntime)
{
    if (!apiRuntime)
    {
        apiRuntime = pRuntime;
    }
}


DustToken::operator DustEntity()
{
    if ( DUST_ENTITY_APPEND == entity )
    {
        entity = DustData::getTokenEntity(this);
    }
    return entity;
}

void DustRuntime::setBootToken(DustToken &token, DustEntity entity) {
    DustEntity e = DustData::getTokenEntity(&token, entity);
    token.entity = e;
}

DustEntity DustData::getTokenEntity(DustToken* pToken, DustEntity constId)
{
    switch ( pToken->ideaType )
    {
    case DUST_IDEA_UNIT:
        return apiRuntime->getUnit(pToken->name, constId);
    case DUST_IDEA_MEMBER:
        return apiRuntime->getMemberEntity(*(pToken->parent), pToken->name, pToken->valType, pToken->collType, constId);
    default:
        return apiRuntime->getIdeaEntity(*(pToken->parent), pToken->name, pToken->ideaType, constId);
    }
}

DustEntity DustData::getEntityByPath(DustEntity ctx, ...)
{
    DustEntity e = ctx;
//
//	DustProdLightRef *pR = NULL;
//
//	va_list args;
//	va_start(args, ctx);
//
//	while (e) {
//		int p = va_arg(args, int);
//
//		if (!p) {
//			break;
//		}
//
//		pR = DustProdLightRuntime::pRuntime->getRef(e, p);
//
//		if (pR && pR->getCount()) {
//			switch (pR->tokenType) {
//			case DUST_TOKEN_REF_SINGLE:
//				e = pR->getRef(0);
//				break;
//			case DUST_TOKEN_REF_SET:
//			case DUST_TOKEN_REF_ARR:
//				p = va_arg(args, int);
//				e = pR->getRef(p);
//				break;
//			case DUST_TOKEN_REF_MAP:
//				p = va_arg(args, int);
//				p = pR->getTokenByIndex(p);
//				e = pR->getRef(p);
//				break;
//			default:
//				e = 0;
//				break;
//			}
//		} else {
//			e = 0;
//		}
//	}
//
//	va_end(args);

    return e;
}
DustEntity DustData::createEntity(DustEntity primaryType)
{
    return apiRuntime->createEntity(primaryType);
}

int DustData::getInteger(DustEntity entity, DustEntity token, int defValue)
{
    return apiRuntime->getInteger(entity, token, defValue);
}
double DustData::getReal(DustEntity entity, DustEntity token, double defValue)
{
    return apiRuntime->getReal(entity, token, defValue);
}
void DustData::setInteger(DustEntity entity, DustEntity token, int val)
{
    apiRuntime->setInteger(entity, token, val);
}
void DustData::setReal(DustEntity entity, DustEntity token, double val)
{
    apiRuntime->setReal(entity, token, val);
}

long DustData::getRefCount(DustEntity entity, DustEntity token)
{
    return apiRuntime->getRefCount(entity, token);
}
DustEntity DustData::getRefKey(DustEntity entity, DustEntity token, long idx)
{
    return apiRuntime->getRefKey(entity, token, idx);
}
DustEntity DustData::getRef(DustEntity entity, DustEntity token, long key)
{
    return apiRuntime->getRef(entity, token, key);
}

bool DustData::setRef(DustEntity entity, DustEntity token, DustEntity target, long key)
{
    return apiRuntime->setRef(entity, token, target, key);
}

void* DustData::getNative(DustEntity entity, DustEntity type)
{
    return apiRuntime->getNative(entity, type);
}
