
#include "Text.h"

class DustModText : public DustModule {
public:
    static DustModText module;

	DustModText();
	virtual ~DustModText();

	virtual DustResultType DustResourceInit() ;
	virtual DustResultType DustResourceRelease();
};
