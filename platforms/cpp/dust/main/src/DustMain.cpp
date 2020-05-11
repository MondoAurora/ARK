#include <DustRuntime.h>
#include "DustMain.h"

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

my_lib_t MyLoadLib(const char* szMyLib)
{
# ifdef _WIN32
    return ::LoadLibraryA(szMyLib);
# else //_WIN32
    return ::dlopen(szMyLib, RTLD_LAZY);
# endif //_WIN32
}

int MyUnloadLib(my_lib_t hMyLib)
{
# ifdef _WIN32
    return ::FreeLibrary(hMyLib);
# else //_WIN32
    return ::dlclose(hMyLib);
# endif //_WIN32
}

void* MyLoadProc(my_lib_t hMyLib, const char* szMyProc)
{
# ifdef _WIN32
    return (void*) GetProcAddress(hMyLib, szMyProc);
# else //_WIN32
    return ::dlsym(hMyLib, szMyProc);
# endif //_WIN32
}


#define mapContains(m, k) (m.find( k ) != m.end())
#define mapOptGet(m, k) (((m).find( k ) != (m).end()) ? (m)[k] : NULL)

class DustMainModule
{
    string name;
    my_lib_t hLib;
    DustModule *pModule;

    DustMainModule(const char* n)
        : name(n)
    {
//		name.append(MODULE_EXT).insert(0, "lib");
        name.append(MODULE_EXT);
        hLib = MyLoadLib(name.c_str());
        getModule_t gm = (getModule_t) MyLoadProc(hLib, DUST_FNAME_GET_MODULE);

        pModule = gm();
    }

    ~DustMainModule()
    {
        pModule->DustResourceRelease();
        MyUnloadLib(hLib);
    }

    void initModule(DustRuntime* pR)
    {
        initModule_t im = (initModule_t) MyLoadProc(hLib, DUST_FNAME_INIT_MODULE);

        if ( im )
        {
            im(pR);
        }
        else
        {
            cout << "ERROR missing " << DUST_FNAME_INIT_MODULE << " in module " << name << endl;
        }

        pModule->DustResourceInit();
    }

    friend class DustMainApp;
};

typedef map<string, DustMainModule*>::iterator ModuleIterator;


extern "C" class DustMainApp : public DustRuntimeConnector
{
    map<DustEntity, DustModule*> modByType;
    map<string, DustMainModule*> modByName;

    DustTextDictionary *pMainDict;
    DustRuntime *pRuntime;

    DustMainApp() : pMainDict(0), pRuntime(0) {}

    ~DustMainApp()
    {
        for (ModuleIterator it = modByName.begin(); it != modByName.end(); ++it)
        {
            delete it->second;
        }
    }

    virtual void loadModule(const char* name)
    {
        loadModule(name, false);
    }

    virtual DustModule* loadModule(const char* name, bool boot)
    {
        string n = name;
        DustMainModule *pmm = mapOptGet(modByName, n);

        if ( !pmm )
        {
            pmm = new DustMainModule(name);
            modByName[n] = pmm;

            if ( !boot )
            {
                pmm->initModule(pRuntime);
            }
        }

        return pmm->pModule;
    }

    virtual void initModule()
    {
    }

    virtual DustEntity getTextToken(const char* name)
    {
        return 0;
    }

    virtual DustModule* getModuleForType(DustEntity type)
    {
        DustModule *pm = mapOptGet(modByType, type);

        if ( !pm )
        {
            for (ModuleIterator it = modByName.begin(); it != modByName.end(); ++it)
            {
                DustModule *pTmpMod = it->second->pModule;
                void *pTest = pTmpMod->createNative(type);
                if ( pTest ) {
                    pm = pTmpMod;
                    pm->releaseNative(type, pTest);
                    break;
                }
            }

            if ( pm ) {
                modByType[type] = pm;
            }
        }

        return pm;
    }

    virtual DustEntity getMetaUnit(const char* name)
    {
        return pRuntime->getMetaUnit(name);
    }

    virtual DustEntity getMetaEntity(DustEntity primaryType, const char* name, DustEntity parent, DustEntity constId = DUST_ENTITY_INVALID)
    {
        return pRuntime->getMetaEntity(primaryType, name, parent, constId);
    }

public:
    static DustMainApp theApp;

    void boot(int argc, char **argv)
    {
        for ( int i = 1; i < argc; ++i )
        {
            DustModule *pMod = loadModule(argv[i], true);

            if ( !pRuntime )
            {
                pRuntime = (DustRuntime*) pMod->createNative(DUST_BOOT_RUNTIME);
                if ( pRuntime )
                {
                    modByType[DUST_BOOT_RUNTIME] = pMod;
                    pRuntime->setConnector(this);
                }
            }
            if ( !pMainDict)
            {
                pMainDict = (DustTextDictionary*) pMod->createNative(DUST_BOOT_DICTIONARY);
                if ( pMainDict )
                {
                    modByType[DUST_BOOT_DICTIONARY] = pMod;
                }
            }
        }

        ::initModule(pRuntime);

        for (ModuleIterator it = modByName.begin(); it != modByName.end(); ++it)
        {
            it->second->initModule(pRuntime);
        }
    }
};

DustMainApp DustMainApp::theApp;

extern "C" void bootDust(int moduleCount, char **moduleNames)
{
    DustMainApp::theApp.boot(moduleCount, moduleNames);
}

//int main(int argc, char **argv) {
//
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//
//	return 0;
//}
