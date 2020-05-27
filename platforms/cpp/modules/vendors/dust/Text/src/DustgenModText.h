
#include <DustRuntime.h>

class DustModText : public DustModule {
public:
	virtual ~DustModText();

	virtual DustResultType DustResourceInit() ;

	virtual DustResultType DustResourceRelease();

	virtual void* createNative(int typeId) const;

	virtual DustResultType dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) const;

	virtual void releaseNative(int typeId, void* pNativeObject) const ;
};
