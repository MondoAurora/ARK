#ifndef SRC_MODGEN_WINGUI_H_
#define SRC_MODGEN_WINGUI_H_


#include <DustRuntime.h>

class WinGuiModule : public DustModule {
public:
	virtual ~WinGuiModule();

	virtual DustResultType DustResourceInit() ;
	virtual DustResultType DustResourceRelease();
};

#endif // SRC_MODGEN_WINGUI_H_
