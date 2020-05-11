/*
 * DplStrl.h
 *
 *  Created on: May 8, 2020
 *      Author: loran
 */

#ifndef SRC_DPLSTL_H_
#define SRC_DPLSTL_H_

#include <DustRuntime.h>

extern "C" class DplStlRuntime: public DustRuntime {
public:
	virtual ~DplStlRuntime();

	virtual void setConnector(DustRuntimeConnector* pConn);

	virtual DustEntity getMetaUnit(const char* name);
	virtual DustEntity getMetaEntity(DustEntity primaryType, const char* name, DustEntity parent, DustEntity constId = DUST_ENTITY_INVALID);

	virtual DustEntity createEntity(DustEntity primaryType);

// Entity value access
	virtual int getInt(DustEntity entity, DustEntity token, int defValue);
	virtual double getDouble(DustEntity entity, DustEntity token, double defValue);

	virtual void setInt(DustEntity entity, DustEntity token, int val);
	virtual void setDouble(DustEntity entity, DustEntity token, double val);

// Entity reference access
	virtual unsigned int getRefCount(DustEntity entity, DustEntity token);
	virtual DustEntity getRefKey(DustEntity entity, DustEntity token, int idx);
	virtual DustEntity getRef(DustEntity entity, DustEntity token, int key = DUST_REFKEY_ARR_APPEND);

	virtual bool setRef(DustEntity entity, DustEntity token, DustEntity target, int key = DUST_REFKEY_ARR_APPEND);

// Entity native content access
	virtual void* getNative(DustEntity entity, DustEntity type);

	virtual DustProcessResult DustResourceInit();
	virtual DustProcessResult DustResourceRelease();
	virtual DustProcessResult DustActionExecute();
};

#endif /* SRC_DPLSTL_H_ */
