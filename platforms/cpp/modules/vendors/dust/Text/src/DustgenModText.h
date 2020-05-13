
#include <DustRuntime.h>

#include "Text.h"

class DustModText : public DustModule {
public:
	virtual ~DustModText();

	virtual DustProcessResult DustResourceInit() ;

	virtual DustProcessResult DustResourceRelease();

	virtual void* createNative(int typeId) const;

	virtual DustProcessResult dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) const;

	virtual void releaseNative(int typeId, void* pNativeObject) const ;
};
