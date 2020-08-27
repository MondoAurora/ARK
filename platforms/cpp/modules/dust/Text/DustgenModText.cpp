#include <iostream>
#include <string>

#include "DustgenModText.h"
#include "Text.h"

using namespace std;

using namespace DustUnitMindText;
using namespace DustUnitMindBinary;

DECLARE_FACTORY(TextDictionary, DUST_BOOT_AGENT_DICTIONARY)
DECLARE_FACTORY(string, DUST_BOOT_TYPE_PLAINTEXT)
DECLARE_FACTORY(TextLogicStreamReader, DustAgentStreamReader)
DECLARE_FACTORY(TextLogicStreamWriter, DustAgentStreamWriter)

DustModText DustModText::module;

DustModText::DustModText()
{
    DustModText::module.registerFactory(&FactTextDictionary);
    DustModText::module.registerFactory(&Factstring);
}

DustModText::~DustModText()
{
}

DustResultType DustModText::DustResourceInit()
{
    DustUtils::log() << "DustModText::DustResourceInit" << endl;

    return DUST_RESULT_ACCEPT;
}

DustResultType DustModText::DustResourceRelease()
{
    cout << "DustModText::DustResourceRelease" << endl;
    return DUST_RESULT_ACCEPT;
}

extern "C" DustModule* getModule()
{
    return &DustModText::module;
}
