#include "DustMain.h"

#include <DustRuntimeImpl.h>
#include <DustModuleLoaderLib.h>

#include <iostream>

DustModuleLoaderLib *pLibLoader = NULL;
DustTextDictionary *pDict = NULL;
DustRuntimeImpl *pRuntime = NULL;
DustAppImpl *pApp = NULL;

void DustMonolith::init(DustModule *pModKernel, DustModule *pModText)
{
    if ( pRuntime || pDict || pApp )
    {
        DustUtils::log(DUST_EVENT_CRITICAL) << "Multiple DustMonolith::dustInit call, exiting." << endl;
        exit(-1);
    }

    pRuntime = (DustRuntimeImpl*) pModKernel->createNative(DUST_BOOT_AGENT_RUNTIME);
    ::initModule(pRuntime);

    if ( pLibLoader ) {
        pLibLoader->initModule(pModKernel, pRuntime);
        if ( pModText )
        {
            pLibLoader->initModule(pModText, pRuntime);
        }
    }

    pApp = (DustAppImpl*) pModKernel->createNative(DUST_BOOT_AGENT_APP);
    pDict = (DustTextDictionary*) (pModText
                                   ? pModText->createNative(DUST_BOOT_AGENT_DICTIONARY)
                                   : pModKernel->createNative(DUST_BOOT_AGENT_DICTIONARY));

    pApp->initApp(pRuntime, pLibLoader);

    if ( pModText )
    {
        DustMonolith::addModule(DUST_BOOT_MODNAME_TEXT, pModText);
    }
    pRuntime->initRuntime(pApp, pDict);
    DustMonolith::addModule(DUST_BOOT_MODNAME_KERNEL, pModKernel);

//    pRuntime->DustResourceInit();
}

void DustMonolith::addModule(DustEntity token, DustModule *pMod)
{
    pApp->addModule(token, pMod);
}

DustResultType DustMonolith::launch()
{
    DustRuntimeImpl *pR = pRuntime;

    pRuntime = NULL;
    pLibLoader = NULL;
    pApp = NULL;
    pDict = NULL;

    DustResultType ret = pR->DustActionExecute();

    pR->DustResourceRelease();

    return ret;
}

void DustModular::init(const char *nameKernel, const char *nameText)
{
    if ( pLibLoader )
    {
        DustUtils::log(DUST_EVENT_CRITICAL) << "Multiple DustModular::dustInit call, exiting." << endl;
        exit(-1);
    }

    pLibLoader = new DustModuleLoaderLib();

    DustModule *pModKernel = pLibLoader->loadModule(nameKernel);
    DustModule *pModText = nameText ? pLibLoader->loadModule(nameText) : NULL;

    DustMonolith::init(pModKernel, pModText);
}

void DustModular::addModule(const char *name)
{
    DustModule *pMod = pLibLoader->loadModule(name);
    pLibLoader->initModule(pMod, pRuntime);
    DustMonolith::addModule(pDict->getTextToken(name), pMod);
}

DustResultType DustModular::launch()
{
    return DustMonolith::launch();
}
