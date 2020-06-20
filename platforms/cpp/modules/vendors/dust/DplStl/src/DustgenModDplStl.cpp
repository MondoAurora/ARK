#include <iostream>
#include <string>

#include <DustModule.h>

#include "DustgenModDplStl.h"
#include "DplStl.h"

using namespace std;

using namespace DustUnitMindDust;
using namespace DustUnitMindNarrative;
using namespace DustUnitMindDialog;

DECLARE_FACTORY(DplStlRuntime, DUST_BOOT_AGENT_RUNTIME)
DECLARE_FACTORY(DplStlRuntimeApp, DUST_BOOT_AGENT_APP)

DECLARE_FACTORY(DplStlRuntimeThread, DustAgentThread)
DECLARE_FACTORY(DplStlRuntimeState, DustAgentState)
DECLARE_FACTORY(DplStlRuntimeDialog, DustAgentDialog)

DECLARE_FACTORY(DplStlLogicSequence, DustAgentSequence)
DECLARE_FACTORY(DplStlLogicSelect, DustAgentSelect)
DECLARE_FACTORY(DplStlLogicRepeat, DustAgentRepeat)

DustModDplStl DustModDplStl::module;

DustModDplStl::DustModDplStl()
{
        module.registerFactory(&FactDplStlRuntime);
        module.registerFactory(&FactDplStlRuntimeApp);
}

DustModDplStl::~DustModDplStl()
{
}

DustResultType DustModDplStl::DustResourceInit()
{
    DustUtils::log() << "DustModDplStl::DustResourceInit" << endl;

    module.registerFactory(&FactDplStlRuntimeDialog);
    module.registerFactory(&FactDplStlRuntimeThread);
    module.registerFactory(&FactDplStlRuntimeState);

    module.registerFactory(&FactDplStlLogicSequence);
    module.registerFactory(&FactDplStlLogicSelect);
    module.registerFactory(&FactDplStlLogicRepeat);

    return DUST_RESULT_ACCEPT;
}

DustResultType DustModDplStl::DustResourceRelease()
{
    cout << "DustModDplStl::DustResourceRelease" << endl;
    return DUST_RESULT_ACCEPT;
}

extern "C" DustModule* getModule()
{
    return &DustModDplStl::module;
}
