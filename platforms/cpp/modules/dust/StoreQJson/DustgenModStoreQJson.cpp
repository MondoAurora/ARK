#include <iostream>
#include <string>

#include <DustModule.h>

#include "DustgenModStoreQJson.h"
#include "StoreQJson.h"

using namespace std;
using namespace DustUnitDustStore;

DECLARE_FACTORY(AgentStoreReader, DustAgentStoreReader)
DECLARE_FACTORY(AgentStoreWriter, DustAgentStoreWriter)

StoreQJsonModule::~StoreQJsonModule()
{
}

DustResultType StoreQJsonModule::DustResourceInit()
{
    cout << "StoreQJsonModule::DustResourceInit" << endl;
    registerFactory(&FactAgentStoreReader);
    registerFactory(&FactAgentStoreWriter);
    return DUST_RESULT_ACCEPT;
}
DustResultType StoreQJsonModule::DustResourceRelease()
{
    cout << "StoreQJsonModule::DustResourceRelease" << endl;
    return DUST_RESULT_ACCEPT;
}

StoreQJsonModule module;

extern "C" DustModule* getModule()
{
    return &module;
}
