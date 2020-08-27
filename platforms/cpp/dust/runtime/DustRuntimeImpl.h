#ifndef DUSTRUNTIMEIMPL_H_
#define DUSTRUNTIMEIMPL_H_

#include <DustKernel.h>

using namespace std;

class DustRuntimeImpl;

extern "C" class DustModuleLoader
{
public:
    virtual ~DustModuleLoader();

    virtual DustModule* loadModule(const char* name) = 0;
    virtual void releaseModule(DustModule* pModule) = 0;
};

typedef map<DustEntity, DustModule*>::iterator ModuleIterator;

extern "C" class DustAppImpl : public DustModuleApi, public DustNativeLogic
{
    DustRuntimeImpl *pRuntime;
    DustModuleLoader *pModuleLoader;

    map<DustEntity, DustModule*> modulesByToken;
    map<DustEntity, DustModule*> modulesByType;

    DustModule* getModule(DustEntity typeId);
    DustModule* handleMissingModuleForType(DustEntity typeId);

public:
    virtual ~DustAppImpl();

    virtual void initApp(DustRuntimeImpl *pRuntime, DustModuleLoader *pModuleLoader_);

    virtual void addModule(DustEntity token, DustModule* pModule);

    virtual bool isNativeProvided(DustEntity typeId);
    virtual void* createNative(DustEntity typeId);
    virtual DustResultType dispatchCommand(DustEntity typeId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID);
    virtual void releaseNative(DustEntity typeId, void* pNativeObject);
} ;

extern "C" class DustRuntimeImpl: public DustRuntime
{
protected:
//    void setBootToken(DustToken &token, DustEntity entity);
    DustTextDictionary *pTokenDicionary;

public:
    virtual ~DustRuntimeImpl() { }

    virtual void initRuntime(DustAppImpl* pApp, DustTextDictionary *pTokenDicionary_) = 0;
};

#endif /* DUSTRUNTIMEIMPL_H_ */
