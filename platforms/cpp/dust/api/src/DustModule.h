#ifndef DUSTMODULE_H_
#define DUSTMODULE_H_

#include "DustUtils.h"

#include <map>

#define DUST_LAST_CONST_MODULE DUST_LAST_CONST_API

class DustRuntime;

extern "C" class DustFactoryLogic
{
public:
    virtual DustEntity DustFactoryGetType() = 0;
    virtual void* DustFactoryCreate() = 0;
    virtual void DustFactoryDestroy(void*) = 0;

    virtual DustResultType DustFactoryDispatch(DustNativeLogic* pLogic, DustEntity cmd, DustEntity param) {
		return DUST_RESULT_NOTIMPLEMENTED;
	}
} ;

#ifndef DECLARE_FACTORY
#define DECLARE_FACTORY(className, typeKey) class Fact_##className : public DustFactoryLogic \
{\
    virtual DustEntity DustFactoryGetType() { return typeKey ; };\
    virtual void* DustFactoryCreate() { return new className (); };\
    virtual void DustFactoryDestroy(void* pObj ) { delete ( className * ) pObj; }\
} Fact##className ;
#endif // DECLARE_FACTORY

extern "C" class DustModule: public DustNativeLogic {
private:
	static DustRuntime* apiRuntime;
    std::map<DustEntity, DustFactoryLogic*> logicFactories;
    std::map<DustEntity, DustEntity> algorithms;

public:
	virtual ~DustModule() {
	}

    void registerFactory(DustFactoryLogic *pFactory);
    void registerAlgorithm(DustEntity agent, DustEntity implRoot);

	bool isNativeProvided(DustEntity typeId);
	void* createNative(DustEntity typeId) ;
	DustResultType dispatchCommand(DustEntity typeId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID);
	void releaseNative(DustEntity typeId, void* pNativeObject);

    friend class DustData;
};

#endif /* DUSTMODULE_H_ */
