
#include <DustRuntime.h>

class DustModDplStl : public DustModule {
public:
	virtual ~DustModDplStl();

	virtual DustResultType DustResourceInit() ;
	virtual DustResultType DustResourceRelease();
};

