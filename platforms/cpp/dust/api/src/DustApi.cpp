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


long DustData::getMemberCount(DustEntity entity, DustEntity token)
{
    return apiRuntime->getMemberCount(entity, token);
}
DustEntity DustData::getMemberKey(DustEntity entity, DustEntity token, long idx)
{
    return apiRuntime->getMemberKey(entity, token, idx);
}
bool DustData::clearMember(DustEntity entity, DustEntity token) {
    DustAccessData ad(DUST_ACCESS_CLEAR, entity, token);
    return apiRuntime->accessMember(ad);
}
bool DustData::moveMember(DustEntity entity, DustEntity token, long keyFrom, long keyTo) {
    DustAccessData ad(DUST_ACCESS_MOVE, entity, token, keyFrom, keyTo);
    return apiRuntime->accessMember(ad);
}

long DustData::getInteger(DustEntity entity, DustEntity token, long defValue, long key)
{
    DustAccessData ad(DUST_ACCESS_GET, entity, token, key);
    return apiRuntime->accessMember(ad) ? ad.valLong : defValue;
}
double DustData::getReal(DustEntity entity, DustEntity token, double defValue, long key)
{
    DustAccessData ad(DUST_ACCESS_GET, entity, token, key);
    return apiRuntime->accessMember(ad) ? ad.valDouble : defValue;
}
DustEntity DustData::getRef(DustEntity entity, DustEntity token, DustEntity defValue, long key)
{
    DustAccessData ad(DUST_ACCESS_GET, entity, token, key);
    return apiRuntime->accessMember(ad) ? ad.valLong : defValue;
}


bool DustData::setInteger(DustEntity entity, DustEntity token, long val, long key)
{
    DustAccessData ad(entity, token, val, key);
    return apiRuntime->accessMember(ad);
}
bool DustData::setReal(DustEntity entity, DustEntity token, double val, long key)
{
    DustAccessData ad(entity, token, val, key);
    return apiRuntime->accessMember(ad);
}
bool DustData::setRef(DustEntity entity, DustEntity token, DustEntity target, long key)
{
    DustAccessData ad(entity, token, target, key);
    return apiRuntime->accessMember(ad);
}

bool DustData::removeInteger(DustEntity entity, DustEntity token, long val, long key)
{
    DustAccessData ad(DUST_ACCESS_REMOVE, entity, token, val, key);
    return apiRuntime->accessMember(ad);
}
bool DustData::removeReal(DustEntity entity, DustEntity token, double val, long key)
{
    DustAccessData ad(DUST_ACCESS_REMOVE, entity, token, val, key);
    return apiRuntime->accessMember(ad);
}
bool DustData::removeRef(DustEntity entity, DustEntity token, DustEntity target, long key)
{
    DustAccessData ad(DUST_ACCESS_REMOVE, entity, token, target, key);
    return apiRuntime->accessMember(ad);
}

void* DustData::getNative(DustEntity entity, DustEntity type)
{
    return apiRuntime->getNative(entity, type);
}
