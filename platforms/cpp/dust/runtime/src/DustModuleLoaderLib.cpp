#include <iostream>
#include <string>

#include "DustModuleLoaderLib.h"

using namespace std;

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



DustLibModule::DustLibModule(const char* n)
    : name(n)
{
//		name.append(MODULE_EXT).insert(0, "lib");
    name.append(MODULE_EXT);
    hLib = MyLoadLib(name.c_str());
    getModule_t gm = (getModule_t) MyLoadProc(hLib, DUST_FNAME_GET_MODULE);

    cout << "Loading module " << name << " with fn " << gm << endl;

    pModule = gm();
}


void DustLibModule::initModule(DustRuntime* pRuntime)
{
    initModule_t im = (initModule_t) MyLoadProc(hLib, DUST_FNAME_INIT_MODULE);

    if ( im )
    {
        im(pRuntime);
        cout << DUST_FNAME_INIT_MODULE << " called in module " << name << endl;
    }
    else
    {
        cout << "ERROR missing " << DUST_FNAME_INIT_MODULE << " in module " << name << endl;
    }
};

DustLibModule::~DustLibModule()
{
    MyUnloadLib(hLib);
}


DustModuleLoaderLib::~DustModuleLoaderLib()
{
    DustUtils::log(DUST_EVENT_TRACE) << "DustModuleLoader destructor" << endl;
}

DustModule* DustModuleLoaderLib::loadModule(const char* name)
{
    DustLibModule *pLM = new DustLibModule(name);
    DustModule* ret = pLM->pModule;

    moduleLibs[ret] = pLM;

    return ret;
};

void DustModuleLoaderLib::initModule(DustModule* pModule, DustRuntime* pRuntime)
{
    moduleLibs[pModule]->initModule(pRuntime);
};

void DustModuleLoaderLib::releaseModule(DustModule* pModule)
{
    delete moduleLibs[pModule];
    moduleLibs.erase(pModule);
};
