#include "Text.h"

#include <iostream>

using namespace std;

TextDictionary::~TextDictionary() {};

DustEntity TextDictionary::getTextToken(const char* name, DustEntity txtParent)
{
    string key(name);

    string* pStr = txtParent ? (string*) DustData::getNative(txtParent, DUST_BOOT_TYPE_PLAINTEXT) : NULL;

    if (pStr) {
        key.insert(0, (0 <= pStr->find(DUST_SEP_UNIT, 0) ? DUST_SEP_ID : DUST_SEP_UNIT) );
        key.insert(0, *pStr);
    }

    DustEntity ret = findEntity(words, key);
//    cout << "Search for " << key.c_str() << " in " << this << " map size " << words.size() << endl;

    if ( !ret ) {
        ret = DustData::createEntity(DUST_BOOT_TYPE_PLAINTEXT);
        pStr = (string*) DustData::getNative(ret, DUST_BOOT_TYPE_PLAINTEXT);
        (*pStr) = key;
        words[key] = ret;

        cout << "New key created " << ((string*) DustData::getNative(ret, DUST_BOOT_TYPE_PLAINTEXT))->c_str() << endl;
    } else {
        cout << "Old key access key: " << key << " -> " << (string*) DustData::getNative(ret, DUST_BOOT_TYPE_PLAINTEXT) << endl;
    }

    return ret;
}

DustResultType TextDictionary::DustResourceInit()
{
    return DUST_RESULT_ACCEPT;
}

DustResultType TextDictionary::DustResourceRelease()
{
    return DUST_RESULT_ACCEPT;
}
