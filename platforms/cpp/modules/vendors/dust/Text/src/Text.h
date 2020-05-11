#ifndef SRC_TEXT_H_
#define SRC_TEXT_H_


#include <DustRuntime.h>

extern "C" class TextDictionary : public DustTextDictionary {
public:
	virtual ~TextDictionary();

	virtual DustEntity getTextToken(const char* name);
	virtual DustProcessResult DustResourceInit();
	virtual DustProcessResult DustResourceRelease();
};

#endif /* SRC_TEXT_H_ */
