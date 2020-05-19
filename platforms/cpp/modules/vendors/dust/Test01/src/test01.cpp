#include <iostream>
#include <string>

#include <DustModule.h>

#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustgenUnitMindCore.h>

using namespace std;

class T01 : public DustNativeLogic
{
    virtual DustResultType DustActionExecute()
    {
        cout << "T01 sees int value " << DustData::getInteger(0,0,0) << endl;

        DustEntity e = DustData::getRef(DustUnitMindText::DustTypePlainText, DustUnitMindModel::DustRefGlobalId);

        string *pStr = (string*) DustData::getNative(e, DustUnitMindText::DustTypePlainText);

        cout << "T01 read plain text type id " << pStr->c_str() << endl;

        pStr = (string*) DustData::getNative(e, DustUnitMindText::DustTypePlainText);

        cout << "T01 read plain text type id SECOND TIME " << pStr->c_str() << endl;

        return DUST_RESULT_ACCEPT;
    }
};

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
        if ( 99 == typeId )
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
        if ( 99 == typeId )
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
