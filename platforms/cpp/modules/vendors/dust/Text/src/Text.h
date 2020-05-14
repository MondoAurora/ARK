#ifndef SRC_TEXT_H_
#define SRC_TEXT_H_

#include <DustRuntime.h>
#include <MiND/DustgenUnitMindText.h>

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

extern DustUnitMindText *pUnitText;

#endif /* SRC_TEXT_H_ */
