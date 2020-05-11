#include "Text.h"

#include <iostream>

using namespace std;

TextDictionary::~TextDictionary() {};

DustEntity TextDictionary::getTextToken(const char* name)
{
    DustData::setInt(0, 0, 333);
    return 1;
}

DustProcessResult TextDictionary::DustResourceInit()
{
    return DUST_PROCESS_ACCEPT;
}

DustProcessResult TextDictionary::DustResourceRelease()
{
    return DUST_PROCESS_ACCEPT;
}
