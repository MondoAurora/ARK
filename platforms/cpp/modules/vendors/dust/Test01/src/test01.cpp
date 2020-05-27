#include <iostream>
#include <string>

#include <DustModule.h>

#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustgenUnitMindCore.h>
#include <vendors/dust/DustgenUnitTest01.h>

using namespace std;
using namespace DustUnitDustTest01;


void test01()
{
    cout << "T01 sees int value " << DustData::getInteger(0,0,0) << endl;

    DustEntity e = DustData::getRef(DustUnitMindText::DustTypePlainText, DustUnitMindModel::DustRefGlobalId);

    string *pStr = (string*) DustData::getNative(e, DustUnitMindText::DustTypePlainText);

    cout << "T01 read plain text type id " << pStr->c_str() << endl;

    pStr = (string*) DustData::getNative(e, DustUnitMindText::DustTypePlainText);

    cout << "T01 read plain text type id SECOND TIME " << pStr->c_str() << endl;
}

void test02()
{
    DustEntity e = DustData::createEntity(DustTypePoint);

    DustData::setReal(e, DustRealX, 3.14);
    DustData::setReal(e, DustRealY, 8.88);

    DustData::setInteger(e, DustIntCode, 13);

    cout << "Point color: " << DustData::getInteger(e, DustIntCode)
        << ", X: " << DustData::getReal(e, DustRealX)
        << ", Y: " << DustData::getReal(e, DustRealY)
        << endl;
}

class T01 : public DustNativeLogic
{
    virtual DustResultType DustActionExecute()
    {
//        test01();
        test02();

        return DUST_RESULT_ACCEPT;
    }
};


class FactTest01_ : public DustFactoryLogic
{
    virtual DustToken& DustFactoryGetToken() { return DustAgentTest01; };

    virtual void* DustFactoryCreate() { return new T01(); };
    virtual void DustFactoryDestroy(void* pObj ) { delete (T01*) pObj; }
} FactTest01 ;

class TestModule : public DustModule
{
public:
    virtual ~TestModule()
    {
    }

    virtual DustResultType DustResourceInit()
    {
        cout << "TestModule::DustResourceInit" << endl;
        return DUST_RESULT_ACCEPT;
    }
    virtual DustResultType DustResourceRelease()
    {
        cout << "TestModule::DustResourceRelease" << endl;
        return DUST_RESULT_ACCEPT;
    }

    virtual void* createNative(int typeId) const
    {
        if ( DustAgentTest01 == typeId )
        {
            return new T01();
        }
        return 0;
    }
    virtual DustResultType dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) const
    {
        return DUST_RESULT_NOTIMPLEMENTED;
    }
    virtual void releaseNative(int typeId, void* pNativeObject) const
    {
        if ( DustAgentTest01 == typeId )
        {
            delete (T01*) pNativeObject;
        }
    }
};

TestModule module;

extern "C" DustModule* getModule()
{
    return &module;
}
