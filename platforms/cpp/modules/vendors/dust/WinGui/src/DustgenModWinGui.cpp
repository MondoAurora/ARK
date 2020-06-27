#include <iostream>
#include <string>

#include <DustModule.h>

#include "DustgenModWinGui.h"
#include "WinGui.h"

using namespace std;
using namespace DustUnitDustTest01;

DECLARE_FACTORY(WinGuiWindow, DustAgentTestWindow)
//DECLARE_FACTORY(AgentWindow, DustAgentTestWindow)

WinGuiModule::~WinGuiModule()
{
}

DustResultType WinGuiModule::DustResourceInit()
{
    cout << "WinGuiModule::DustResourceInit" << endl;
    registerFactory(&FactWinGuiWindow);
    return DUST_RESULT_ACCEPT;
}
DustResultType WinGuiModule::DustResourceRelease()
{
    cout << "WinGuiModule::DustResourceRelease" << endl;
    return DUST_RESULT_ACCEPT;
}

WinGuiModule module;

extern "C" DustModule* getModule()
{
    return &module;
}
