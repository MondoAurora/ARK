#include <iostream>
#include <string>

#include <DustRuntime.h>

#include "DustgenModText.h"
#include "Text.h"

using namespace std;

DustModText module;

using namespace DustUnitMindText;
using namespace DustUnitMindStream;

DECLARE_FACTORY(TextDictionary, DUST_BOOT_AGENT_DICTIONARY)
DECLARE_FACTORY(string, DUST_BOOT_TYPE_PLAINTEXT)
DECLARE_FACTORY(TextLogicStreamReader, DustAgentReader)
DECLARE_FACTORY(TextLogicStreamWriter, DustAgentWriter)

extern "C" DustModule* getModule()
{
    module.registerFactory(&FactTextDictionary);
    module.registerFactory(&Factstring);

    return &module;
}

DustModText::~DustModText()
{
}

DustResultType DustModText::DustResourceInit()
{
    DustUtils::log() << "DustModText::DustResourceInit" << endl;
    registerFactory(&FactTextLogicStreamReader);
    registerFactory(&FactTextLogicStreamWriter);

    return DUST_RESULT_ACCEPT;
}

DustResultType DustModText::DustResourceRelease()
{
    cout << "DustModText::DustResourceRelease" << endl;
    return DUST_RESULT_ACCEPT;
}

