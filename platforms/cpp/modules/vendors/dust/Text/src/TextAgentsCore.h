#ifndef TEXTAGENTSCORE_H
#define TEXTAGENTSCORE_H

#include <DustApi.h>


using namespace std;

class TextDictionary : public DustTextDictionary {
    map<string, DustEntity> words;

public:
	virtual ~TextDictionary();

	virtual DustEntity getTextToken(DustEntity txtParent, const char* name);
	virtual DustResultType DustResourceInit();
	virtual DustResultType DustResourceRelease();
};

class TextLogicCore: public DustNativeLogic {
private:

public:
	TextLogicCore();
	virtual ~TextLogicCore();

	virtual DustResultType DustResourceInit();
	virtual DustResultType DustActionExecute();
};

#endif // TEXTAGENTSCORE_H
