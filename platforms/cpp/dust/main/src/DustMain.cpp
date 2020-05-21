#include <DustRuntime.h>
#include "DustMain.h"

#include <iostream>

#include <map>
#include <set>
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

    void initModule0(DustRuntime* pR)
    {
        initModule_t im = (initModule_t) MyLoadProc(hLib, DUST_FNAME_INIT_MODULE);

        if ( im )
        {
            im(pR);
            cout << DUST_FNAME_INIT_MODULE << " called in module " << name << endl;
        }
        else
        {
            cout << "ERROR missing " << DUST_FNAME_INIT_MODULE << " in module " << name << endl;
        }
    }

    void initModule(DustRuntime* pR)
    {
        initModule0(pR);
        pModule->DustResourceInit();
    }

    friend class DustMainApp;
};

typedef map<string, DustMainModule*>::iterator ModuleIterator;
typedef set<DustMainModule*>::iterator ActiveModuleIterator;


extern "C" class DustMainApp : public DustRuntimeConnector
{
    map<DustEntity, DustModule*> modByType;

    map<string, DustMainModule*> modByName;
    set<DustMainModule*> activeModules;

    DustTextDictionary *pMainDict;
    DustRuntime *pRuntime;

    DustMainModule* pRuntimeModule;
    DustMainModule* pTextModule;

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

    virtual DustMainModule* loadModule(const char* name, bool boot)
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

        return pmm;
    }

    virtual DustEntity getTextToken(DustEntity parent, const char* name)
    {
        return pMainDict->getTextToken(parent, name);
    }

    virtual DustModule* getModuleForType(DustEntity type)
    {
        DustModule *pm = mapOptGet(modByType, type);

        if ( !pm )
        {
            for (ActiveModuleIterator it = activeModules.begin(); it != activeModules.end(); ++it)
            {
                DustModule *pTmpMod = (*it)->pModule;
                void *pTest = pTmpMod->createNative(type);
                if ( pTest )
                {
                    pm = pTmpMod;
                    pm->releaseNative(type, pTest);
                    break;
                }
            }

            if ( pm )
            {
                modByType[type] = pm;
            }
        }

        return pm;
    }

public:
    static DustMainApp theApp;

    void boot(int argc, char **argv)
    {
        for ( int i = 1; i < argc; ++i )
        {
            DustMainModule *pmm = loadModule(argv[i], true);
            DustModule *pMod = pmm->pModule;

            if ( !pRuntime )
            {
                pRuntime = (DustRuntime*) pMod->createNative(DUST_BOOT_AGENT_RUNTIME);
                if ( pRuntime )
                {
                    modByType[DUST_BOOT_AGENT_RUNTIME] = pMod;
                    pRuntime->setConnector(this);
                    pRuntimeModule = pmm;
                    activeModules.insert(pmm);
                }
            }
            if ( !pMainDict)
            {
                pMainDict = (DustTextDictionary*) pMod->createNative(DUST_BOOT_AGENT_DICTIONARY);
                if ( pMainDict )
                {
                    modByType[DUST_BOOT_AGENT_DICTIONARY] = pMod;
                    pTextModule = pmm;
                    activeModules.insert(pmm);
                }
            }
        }

        ::initModule(pRuntime);

        pTextModule->initModule0(pRuntime);
        pRuntimeModule->initModule(pRuntime);

        pRuntime->DustResourceInit();

        for (ModuleIterator it = modByName.begin(); it != modByName.end(); ++it)
        {
            DustMainModule *pmm = it->second;
            activeModules.insert(pmm);

            if ( pmm != pRuntimeModule )
            {
                if ( pmm != pTextModule )
                {
                    pmm->initModule(pRuntime);
                }
                else
                {
                    pmm->pModule->DustResourceInit();
                }
            }
        }
    }
};

DustMainApp DustMainApp::theApp;

extern "C" void bootDust(int moduleCount, char **moduleNames)
{
    DustMainApp::theApp.boot(moduleCount, moduleNames);
}

