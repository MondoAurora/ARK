#ifndef SRC_TEXT_H_
#define SRC_TEXT_H_

#include <DustRuntime.h>

#include <MiND/DustgenUnitMindText.h>

extern "C" class TextDictionary : public DustTextDictionary {
public:
	virtual ~TextDictionary();

	virtual DustEntity getTextToken(DustEntity txtParent, const char* name);
	virtual DustProcessResult DustResourceInit();
	virtual DustProcessResult DustResourceRelease();
};

extern DustUnitMindText *pUnitText;

#endif /* SRC_TEXT_H_ */
