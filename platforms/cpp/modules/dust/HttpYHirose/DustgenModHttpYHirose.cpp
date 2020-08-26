#include <iostream>
#include <string>

#include <DustModule.h>

#include "DustgenModHttpYHirose.h"
#include "HttpYHirose.h"

using namespace std;
using namespace DustUnitDustHttp;

DECLARE_FACTORY(AgentHttpGetter, DustAgentHttpGetter)

HttpYHiroseModule::~HttpYHiroseModule()
{
}

DustResultType HttpYHiroseModule::DustResourceInit()
{
    cout << "HttpYHiroseModule::DustResourceInit" << endl;
    registerFactory(&FactAgentHttpGetter);
    return DUST_RESULT_ACCEPT;
}
DustResultType HttpYHiroseModule::DustResourceRelease()
{
    cout << "HttpYHiroseModule::DustResourceRelease" << endl;
    return DUST_RESULT_ACCEPT;
}

HttpYHiroseModule module;

extern "C" DustModule* getModule()
{
    return &module;
}
