#ifndef TEST00_H
#define TEST00_H

#include <map>
#include <string>

class DustLibModule;
class DustModule;

using namespace std;

class DustModuleLoader
{
public:
    virtual ~DustModuleLoader();

    virtual DustModule* loadModule(const char* name) = 0;
    virtual void releaseModule(DustModule* pModule) = 0;
};

//
//class DustModuleLoaderLib : public DustModuleLoader
//{
//    map<DustModule*, DustLibModule*> moduleLibs;
//
//public:
//    virtual DustModule* loadModule(const char* name);
//    virtual void releaseModule(DustModule* pModule);
//};


#endif // TEST00_H
