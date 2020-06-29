#include <iostream>
#include <string>

#include <DustModule.h>

#include "DustgenModWinGui.h"

using namespace std;
using namespace DustUnitMindDrawing;

DECLARE_FACTORY(WinGuiWindow, DustAgentOSWindow)

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
