#include "DustRuntime.h"

DustRuntime *apiRuntime = 0;

extern "C" void initModule(DustRuntime *pRuntime) {
	if (!apiRuntime) {
		apiRuntime = pRuntime;
	}
}


DustEntity DustData::getEntityByPath(DustEntity ctx, ...) {
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
DustEntity DustData::createEntity(DustEntity primaryType) {
	return apiRuntime->createEntity(primaryType);
}

int DustData::getInt(DustEntity entity, DustEntity token, int defValue) {
	return apiRuntime->getInt(entity, token, defValue);
}
double DustData::getDouble(DustEntity entity, DustEntity token, double defValue) {
	return apiRuntime->getDouble(entity, token, defValue);
}
void DustData::setInt(DustEntity entity, DustEntity token, int val) {
	apiRuntime->setInt(entity, token, val);
}
void DustData::setDouble(DustEntity entity, DustEntity token, double val) {
	apiRuntime->setDouble(entity, token, val);
}

unsigned int DustData::getRefCount(DustEntity entity, DustEntity token)  {
	return apiRuntime->getRefCount(entity, token);
}
DustEntity DustData::getRefKey(DustEntity entity, DustEntity token, int idx) {
	return apiRuntime->getRefKey(entity, token, idx);
}
DustEntity DustData::getRef(DustEntity entity, DustEntity token, int key) {
	return apiRuntime->getRef(entity, token, key);
}

bool DustData::setRef(DustEntity entity, DustEntity token, DustEntity target,
		int key) {
	return apiRuntime->setRef(entity, token, target, key);
}

void* DustData::getNative(DustEntity entity, DustEntity type) {
	return apiRuntime->getNative(entity, type);
}
