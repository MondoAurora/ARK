
#include <DustRuntime.h>

class DustModText : public DustModule {
public:
	virtual ~DustModText();

	virtual DustResultType DustResourceInit() ;
	virtual DustResultType DustResourceRelease();
};
