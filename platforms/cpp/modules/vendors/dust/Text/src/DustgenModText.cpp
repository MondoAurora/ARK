#include <iostream>
#include <string>

#include <DustRuntime.h>

#include "Text.h"

using namespace std;

class DustModText : public DustModule {
public:
	virtual ~DustModText() {
	}

	virtual DustProcessResult DustResourceInit() {
		cout << "DustModText::DustResourceInit" << endl;
		return DUST_PROCESS_ACCEPT;
	}

	virtual DustProcessResult DustResourceRelease() {
		cout << "DustModText::DustResourceRelease" << endl;
		return DUST_PROCESS_ACCEPT;
	}

	virtual void* createNative(int typeId) const {
		if ( DUST_BOOT_DICTIONARY == typeId ) {
			return new TextDictionary();
		}
		return 0;
	}

	virtual DustProcessResult dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) const {
		return DUST_PROCESS_NOTIMPLEMENTED;
	}

	virtual void releaseNative(int typeId, void* pNativeObject) const {
		if ( DUST_BOOT_DICTIONARY == typeId ) {
			delete (TextDictionary*) pNativeObject;
		}
	}
};

DustModText module;

extern "C" DustModule* getModule() {
	return &module;
}


extern "C" void initModule(DustRuntime *pRuntime);
