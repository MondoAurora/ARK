#include <iostream>
#include <string>

#include <DustModule.h>

#include "DustgenModDplStl.h"
#include "DplStl.h"

using namespace std;

DECLARE_FACTORY(DplStlRuntime, DUST_BOOT_AGENT_RUNTIME)


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

DustModDplStl module;

extern "C" DustModule* getModule()
{
    module.registerFactory(&FactDplStlRuntime);

    return &module;
}
