#include "Text.h"

#include <iostream>

using namespace std;

TextDictionary::~TextDictionary() {};

DustEntity TextDictionary::getTextToken(const char* name) {
	int i = DustData::getInt(0, 0, 0);

	cout << i << endl;

	return 1;
}

DustProcessResult TextDictionary::DustResourceInit() {
	return DUST_PROCESS_ACCEPT;
}

DustProcessResult TextDictionary::DustResourceRelease() {
	return DUST_PROCESS_ACCEPT;
}
