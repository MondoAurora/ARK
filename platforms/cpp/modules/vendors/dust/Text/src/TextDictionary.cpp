#include "Text.h"

#include <iostream>

using namespace std;

TextDictionary::~TextDictionary() {};

DustEntity TextDictionary::getTextToken(DustEntity txtParent, const char* name)
{
    string key(name);

    string* pStr = txtParent ? (string*) DustData::getNative(txtParent, DUST_BOOT_TYPE_PLAINTEXT) : NULL;

    if (pStr) {
        key.insert(0, (0 <= pStr->find(DUST_SEP_UNIT, 0) ? DUST_SEP_ID : DUST_SEP_UNIT) );
        key.insert(0, *pStr);
    }

    DustEntity ret = findEntity(words, key);

    if ( !ret ) {
        ret = DustData::createEntity(DUST_BOOT_TYPE_PLAINTEXT);
        pStr = (string*) DustData::getNative(ret, DUST_BOOT_TYPE_PLAINTEXT);
        (*pStr) = key;

        cout << "New key created " << ((string*) DustData::getNative(ret, DUST_BOOT_TYPE_PLAINTEXT))->c_str() << endl;
    } else {
        cout << "Old key access key: " << key << " -> " << (string*) DustData::getNative(ret, DUST_BOOT_TYPE_PLAINTEXT) << endl;
    }

    return ret;
}

DustProcessResult TextDictionary::DustResourceInit()
{
    return DUST_PROCESS_ACCEPT;
}

DustProcessResult TextDictionary::DustResourceRelease()
{
    return DUST_PROCESS_ACCEPT;
}
