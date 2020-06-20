
#include <DustKernel.h>

class DustModDplStl : public DustModule {
public:
    static DustModDplStl module;

	DustModDplStl();
	virtual ~DustModDplStl();

	virtual DustResultType DustResourceInit() ;
	virtual DustResultType DustResourceRelease();
};

