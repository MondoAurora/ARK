#include <DustRuntime.h>

#include <iostream>

#include <map>
#include <string>

using namespace std;

#ifdef _WIN32
#include <windows.h>
typedef HMODULE my_lib_t;
#define MODULE_EXT ".dll"
#else
#include <dlfcn.h>
typedef void* my_lib_t;
#define MODULE_EXT ".o"
#endif

my_lib_t MyLoadLib(const char* szMyLib) {
# ifdef _WIN32
	return ::LoadLibraryA(szMyLib);
# else //_WIN32
	return ::dlopen(szMyLib, RTLD_LAZY);
# endif //_WIN32
}

int MyUnloadLib(my_lib_t hMyLib) {
# ifdef _WIN32
	return ::FreeLibrary(hMyLib);
# else //_WIN32
	return ::dlclose(hMyLib);
# endif //_WIN32
}

void* MyLoadProc(my_lib_t hMyLib, const char* szMyProc) {
# ifdef _WIN32
	return (void*) GetProcAddress(hMyLib, szMyProc);
# else //_WIN32
	return ::dlsym(hMyLib, szMyProc);
# endif //_WIN32
}


#define mapContains(m, k) (m.find( k ) != m.end())
#define mapOptGet(m, k) (((m).find( k ) != (m).end()) ? (m)[k] : NULL)

class DustMainModule {
	string name;
	my_lib_t hLib;
	DustModule *pModule;

	DustMainModule(const char* n)
	: name(n) {
		name.append(MODULE_EXT);
		hLib = MyLoadLib(name.c_str());
		getModule_t gm = (getModule_t) MyLoadProc(hLib, DUST_FNAME_GET_MODULE);

		pModule = gm();
	}

	~DustMainModule() {
		pModule->DustResourceRelease();
		MyUnloadLib(hLib);
	}

	void initModule(DustRuntime* pR) {
		initModule_t im = (initModule_t) MyLoadProc(hLib, DUST_FNAME_INIT_MODULE);
		im(pR);
	}

	friend class DustMainApp;
};

extern "C" class DustMainApp : public DustRuntimeConnector {
	static DustMainApp theApp;

	map<DustEntity, DustModule*> modByType;
	map<string, DustMainModule*> modByName;

	DustRuntime *pRuntime = 0;

	~DustMainApp() {
	}

	virtual void loadModule(const char* name) {
		string n = name;

		if ( !mapContains(modByName, n) ) {
			DustMainModule *pmm = new DustMainModule(name);
			modByName[n] = pmm;

			if ( pRuntime ) {
				pmm->initModule(pRuntime);
			}
		}
	}

	virtual DustEntity getTextToken(const char* name) {
		return 0;
	}

	virtual DustModule* getModuleForType(DustEntity type) {
		return modByType[type];
	}

	virtual DustEntity getMetaUnit(const char* name) {
		return pRuntime->getMetaUnit(name);
	}

	virtual DustEntity getMetaEntity(DustEntity primaryType, const char* name, DustEntity parent, DustEntity constId = DUST_ENTITY_INVALID) {
		return pRuntime->getMetaEntity(primaryType, name, parent, constId);
	}

public:
	static void loadMod(const char* mod) {
		theApp.loadModule(mod);
	}
};

DustMainApp DustMainApp::theApp;

int main(int argc, char **argv) {
	DustMainApp::loadMod("libDustModTest01");

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	return 0;
}
