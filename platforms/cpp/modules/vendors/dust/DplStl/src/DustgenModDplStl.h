
#include <DustRuntime.h>

class DustModDplStl : public DustModule {
public:
	virtual ~DustModDplStl();

	virtual DustResultType DustResourceInit() ;

	virtual DustResultType DustResourceRelease();

	virtual void* createNative(int typeId) const;

	virtual DustResultType dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) const;

	virtual void releaseNative(int typeId, void* pNativeObject) const ;
};

