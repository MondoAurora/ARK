//============================================================================
// Name        : api.cpp
// Author      : Lorand Kedves
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

#include <DustModule.h>

using namespace std;

class TestModule : public DustModule {
public:
	virtual ~TestModule() {
	}

	virtual void* createNative(int typeId) const {
		return 0;
	}
	virtual DustProcessResult dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) const {
		return DUST_PROCESS_NOTIMPLEMENTED;
	}
	virtual void releaseNative(int typeId, void* pNativeObject) const {
	}
};

TestModule module;

extern "C" DustModule* getModule() {
	return &module;
}
