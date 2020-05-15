#ifndef SRC_TEXT_H_
#define SRC_TEXT_H_

#include <DustRuntime.h>
#include <MiND/DustgenUnitMindTools.h>

#include <map>
#include <string>

using namespace std;

extern "C" class TextDictionary : public DustTextDictionary {
    map<string, DustEntity> words;

public:
	virtual ~TextDictionary();

	virtual DustEntity getTextToken(DustEntity txtParent, const char* name);
	virtual DustProcessResult DustResourceInit();
	virtual DustProcessResult DustResourceRelease();
};

#endif /* SRC_TEXT_H_ */
