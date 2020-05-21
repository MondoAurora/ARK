#include <iostream>
#include <string>

#include <DustRuntime.h>

#include "DustgenModText.h"
#include "Text.h"

using namespace std;

DustModText module;

extern "C" DustModule* getModule()
{
    return &module;
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

void* DustModText::createNative(int typeId) const
{
    if ( DUST_BOOT_AGENT_DICTIONARY == typeId )
    {
        return new TextDictionary();
    }
    else if ( DUST_BOOT_TYPE_PLAINTEXT == typeId )
    {
        return new string();
    }
    return 0;
}

DustResultType DustModText::dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param) const
{
    return DUST_RESULT_NOTIMPLEMENTED;
}

void DustModText::releaseNative(int typeId, void* pNativeObject) const
{
    if ( DUST_BOOT_AGENT_DICTIONARY == typeId )
    {
        delete (TextDictionary*) pNativeObject;
    }
    else if ( DUST_BOOT_TYPE_PLAINTEXT == typeId )
    {
        delete (string*) pNativeObject;
    }
}
