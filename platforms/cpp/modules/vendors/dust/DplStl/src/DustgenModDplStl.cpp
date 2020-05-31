#include <iostream>
#include <string>

#include <DustModule.h>

#include "DustgenModDplStl.h"
#include "DplStl.h"

using namespace std;

using namespace DustUnitMindDust;
using namespace DustUnitMindNarrative;

DECLARE_FACTORY(DplStlRuntime, DUST_BOOT_AGENT_RUNTIME)

DECLARE_FACTORY(DplStlLogicCore, DustAgentCore)
DECLARE_FACTORY(DplStlLogicPDA, DustAgentPda)
DECLARE_FACTORY(DplStlLogicState, DustAgentState)

DECLARE_FACTORY(DplStlLogicDialog, DustAgentDialog)
DECLARE_FACTORY(DplStlLogicSequence, DustAgentSequence)
DECLARE_FACTORY(DplStlLogicSelect, DustAgentSelect)
DECLARE_FACTORY(DplStlLogicRepeat, DustAgentRepeat)

DustModDplStl module;

extern "C" DustModule* getModule()
{
    module.registerFactory(&FactDplStlRuntime);

    return &module;
}

DustModDplStl::~DustModDplStl()
{
}

DustResultType DustModDplStl::DustResourceInit()
{
    DustUtils::log() << "DustModDplStl::DustResourceInit" << endl;

    module.registerFactory(&FactDplStlLogicCore);
    module.registerFactory(&FactDplStlLogicPDA);
    module.registerFactory(&FactDplStlLogicState);

    module.registerFactory(&FactDplStlLogicDialog);
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
