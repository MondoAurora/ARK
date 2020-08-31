#include <iostream>
#include <string>

#include <DustModule.h>

#include "DustgenModStoreJsonNlohmann.h"
#include "StoreJsonNlohmann.h"

using namespace std;
using namespace DustUnitDustStore;

DECLARE_FACTORY(AgentStoreReader, DustAgentStoreReader)
DECLARE_FACTORY(AgentStoreWriter, DustAgentStoreWriter)

StoreJsonNlohmannModule::~StoreJsonNlohmannModule()
{
}

DustResultType StoreJsonNlohmannModule::DustResourceInit()
{
    cout << "StoreJsonNlohmannModule::DustResourceInit" << endl;
    registerFactory(&FactAgentStoreReader);
    registerFactory(&FactAgentStoreWriter);
    return DUST_RESULT_ACCEPT;
}
DustResultType StoreJsonNlohmannModule::DustResourceRelease()
{
    cout << "StoreJsonNlohmannModule::DustResourceRelease" << endl;
    return DUST_RESULT_ACCEPT;
}

StoreJsonNlohmannModule module;

extern "C" DustModule* getModule()
{
    return &module;
}
