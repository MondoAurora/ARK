#ifndef DUSTMODULELOADERLIB_H_
#define DUSTMODULELOADERLIB_H_

#include "DustRuntimeImpl.h"

#ifdef _WIN32
#include <windows.h>
typedef HMODULE my_lib_t;
#define MODULE_EXT ".dll"
#else
#include <dlfcn.h>
typedef void* my_lib_t;
#define MODULE_EXT ".o"
#endif
#include <map>

using namespace std;

class DustLibModule
{
    string name;
    my_lib_t hLib;
    DustModule *pModule;

public:
    DustLibModule(const char* n);
    void initModule(DustRuntime* pRuntime);
    ~DustLibModule();

    friend class DustModuleLoaderLib;
};

extern "C" class DustModuleLoaderLib : public DustModuleLoader
{
    map<DustModule*, DustLibModule*> moduleLibs;

public:
    virtual ~DustModuleLoaderLib();

    virtual DustModule* loadModule(const char* name);
    void initModule(DustModule* pModule, DustRuntime* pRuntime);
    virtual void releaseModule(DustModule* pModule);
};

#endif /* DUSTMODULELOADERLIB_H_ */
