#include <iostream>
#include <string>

#include <DustModule.h>

#include "DustgenModDplStl.h"
#include "DplStl.h"

using namespace std;

DustModDplStl::~DustModDplStl()
{
}

DustProcessResult DustModDplStl::DustResourceInit()
{
    cout << "DustModDplStl::DustResourceInit" << endl;
        DustData::setInt(0,0,333);

    return DUST_PROCESS_ACCEPT;
}

DustProcessResult DustModDplStl::DustResourceRelease()
{
    cout << "DustModDplStl::DustResourceRelease" << endl;
    return DUST_PROCESS_ACCEPT;
}

void* DustModDplStl::createNative(int typeId) const
{
    if ( DUST_BOOT_AGENT_RUNTIME == typeId )
    {
        return new DplStlRuntime();
    }
    return 0;
}

DustProcessResult DustModDplStl::dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param) const
{
    return DUST_PROCESS_NOTIMPLEMENTED;
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
