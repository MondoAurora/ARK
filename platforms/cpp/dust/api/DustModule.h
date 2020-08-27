#ifndef DUSTMODULE_H_
#define DUSTMODULE_H_

#include "DustUtils.h"

#include <map>

#define DUST_LAST_CONST_MODULE DUST_LAST_CONST_API

class DustRuntime;

extern "C" class DustFactoryLogic
{
public:
    virtual bool isSingleton() { return false; };
    virtual DustEntity DustFactoryGetType() = 0;
    virtual void* DustFactoryCreate() = 0;
    virtual void DustFactoryDestroy(void*) = 0;
} ;

#ifndef DECLARE_FACTORY
#define DECLARE_FACTORY(className, typeKey) class Fact_##className : public DustFactoryLogic \
{\
    virtual DustEntity DustFactoryGetType() { return typeKey ; };\
    virtual void* DustFactoryCreate() { return new className (); };\
    virtual void DustFactoryDestroy(void* pObj ) { delete ( className * ) pObj; }\
} Fact##className ;
#endif // DECLARE_FACTORY

#ifndef DECLARE_SINGLETON
#define DECLARE_SINGLETON(className, typeKey) class Fact_##className : public DustFactoryLogic \
{\
    virtual bool isSingleton() { return true; }; \
    virtual DustEntity DustFactoryGetType() { return typeKey ; };\
    virtual void* DustFactoryCreate() { return new className (); };\
    virtual void DustFactoryDestroy(void* pObj ) { delete ( className * ) pObj; }\
} Fact##className ;
#endif // DECLARE_SINGLETON


extern "C" class DustModuleApi
{
public:
	virtual ~DustModuleApi() {
	}

    virtual bool isNativeProvided(DustEntity typeId) = 0;
    virtual void* createNative(DustEntity typeId) = 0;
    virtual DustResultType dispatchCommand(DustEntity typeId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) = 0;
    virtual void releaseNative(DustEntity typeId, void* pNativeObject) = 0;
} ;

extern "C" class DustModule: public DustNativeLogic, public DustModuleApi {
private:
    static DustRuntime *apiRuntime;

    std::map<DustEntity, DustFactoryLogic*> logicFactories;
    std::map<DustEntity, DustEntity> algorithms;

protected:
    void registerFactory(DustFactoryLogic *pFactory);
    void registerAlgorithm(DustEntity agent, DustEntity implRoot);

public:
	virtual ~DustModule() {
	}

	void initModule(DustRuntime *pRuntime);

	virtual bool isNativeProvided(DustEntity typeId);

    /**
	 alg relay executes inside, allows recursion!!!
	 the final creation clones the last entity into the current context and creates the native object
	 resolution calls out back to DustData::getNative
	 this even allows singleton instances on module level
     */
	virtual void* createNative(DustEntity typeId) ;

	virtual DustResultType dispatchCommand(DustEntity typeId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID);
	virtual void releaseNative(DustEntity typeId, void* pNativeObject);

    friend class DustData;
};

#endif /* DUSTMODULE_H_ */
