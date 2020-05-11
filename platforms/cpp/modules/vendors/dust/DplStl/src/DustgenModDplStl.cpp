#include <iostream>
#include <string>

#include <DustModule.h>

#include "DplStl.h"

using namespace std;

class DustModDplStl : public DustModule {
public:
	virtual ~DustModDplStl() {
	}

	virtual DustProcessResult DustResourceInit() {
		cout << "DustModDplStl::DustResourceInit" << endl;
		return DUST_PROCESS_ACCEPT;
	}
	virtual DustProcessResult DustResourceRelease() {
		cout << "DustModDplStl::DustResourceRelease" << endl;
		return DUST_PROCESS_ACCEPT;
	}

	virtual void* createNative(int typeId) const {
		if ( DUST_BOOT_RUNTIME == typeId ) {
			return new DplStlRuntime();
		}
		return 0;
	}
	virtual DustProcessResult dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) const {
		return DUST_PROCESS_NOTIMPLEMENTED;
	}
	virtual void releaseNative(int typeId, void* pNativeObject) const {
		if ( DUST_BOOT_RUNTIME == typeId ) {
			delete (DplStlRuntime*) pNativeObject;
		}
	}
};

DustModDplStl module;

extern "C" DustModule* getModule() {
	return &module;
}

extern "C" void initModule(DustRuntime *pRuntime);
