#include <iostream>
#include <string>

#include <DustModule.h>

#include "DustgenModDplStl.h"
#include "DplStl.h"

using namespace std;

DustModDplStl::~DustModDplStl()
{
}

DustResultType DustModDplStl::DustResourceInit()
{
    DustUtils::log() << "DustModDplStl::DustResourceInit" << endl;

    return DUST_RESULT_ACCEPT;
}

DustResultType DustModDplStl::DustResourceRelease()
{
    cout << "DustModDplStl::DustResourceRelease" << endl;
    return DUST_RESULT_ACCEPT;
}

void* DustModDplStl::createNative(int typeId) const
{
    if ( DUST_BOOT_AGENT_RUNTIME == typeId )
    {
        return new DplStlRuntime();
    }
    return 0;
}

DustResultType DustModDplStl::dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param) const
{
    return DUST_RESULT_NOTIMPLEMENTED;
}

void DustModDplStl::releaseNative(int typeId, void* pNativeObject) const
{
    if ( DUST_BOOT_AGENT_RUNTIME == typeId )
    {
        delete (DplStlRuntime*) pNativeObject;
    }
}

DustModDplStl module;

extern "C" DustModule* getModule()
{
    return &module;
}
