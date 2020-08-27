
#include "DustRuntimeImpl.h"

using namespace std;

DustModuleLoader::~DustModuleLoader()
{
};

DustAppImpl::~DustAppImpl()
{
    modulesByType.clear();
    for (ModuleIterator it = modulesByToken.begin(); it != modulesByToken.end(); ++it)
    {
        DustModule* pMod = it->second;

        if ( pModuleLoader )
        {
            pModuleLoader->releaseModule(pMod);
        }
        else
        {
            pMod->DustResourceRelease();
            delete pMod;
        }
    }
    modulesByToken.clear();
}

void DustAppImpl::initApp(DustRuntimeImpl *pRuntime_, DustModuleLoader *pModuleLoader_)
{
    pRuntime = pRuntime_;
    pModuleLoader = pModuleLoader_;
}

void DustAppImpl::addModule(DustEntity token, DustModule* pModule)
{
    pModule->initModule(pRuntime);
    pModule->DustResourceInit();
    modulesByToken[token] = pModule;
}

DustModule* DustAppImpl::getModule(DustEntity typeId)
{
    DustModule *pMod = mapOptGet(modulesByType, typeId);

    if ( !pMod )
    {
        for (ModuleIterator it = modulesByToken.begin(); !pMod && it != modulesByToken.end(); ++it)
        {
            DustModule* pM = it->second;
            if ( pM->isNativeProvided(typeId))
            {
                pMod = pM;
            }
        }
    }

    if ( !pMod )
    {
        pMod = handleMissingModuleForType(typeId);
    }

    return pMod;
}

DustModule *DustAppImpl::handleMissingModuleForType(DustEntity typeId)
{
    DustModule *ret = NULL;

    if ( pModuleLoader)
    {
        DustUtils::log(DUST_EVENT_TRACE) << "Placeholder for loading module for type " << typeId << endl;
    }

    if ( !ret )
    {
        DustUtils::log(DUST_EVENT_WARNING) << "Missing module for type " << typeId << endl;
    }

    return ret;
}


bool DustAppImpl::isNativeProvided(DustEntity typeId)
{
    return getModule(typeId) ? true : false;
}

void* DustAppImpl::createNative(DustEntity typeId)
{
    DustModule *pMod = getModule(typeId);
    return pMod ? pMod->createNative(typeId) : NULL;
}

DustResultType DustAppImpl::dispatchCommand(DustEntity typeId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param)
{
    DustModule *pMod = getModule(typeId);
    return pMod ? pMod->dispatchCommand(typeId, pLogic, cmd, param) : DUST_RESULT_NOTIMPLEMENTED;
}

void DustAppImpl::releaseNative(DustEntity typeId, void* pNativeObject)
{
    DustModule *pMod = getModule(typeId);
    if (pMod)
    {
        pMod->releaseNative(typeId, pNativeObject);
    }
}

