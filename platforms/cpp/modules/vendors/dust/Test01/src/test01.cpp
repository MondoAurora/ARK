#include <iostream>
#include <string>

#include <DustModule.h>

using namespace std;

class T01 : public DustNativeLogic
{
    virtual DustProcessResult DustActionExecute()
    {
        cout << "T01 sees int value " << DustData::getInt(0,0,0) << endl;
        return DUST_PROCESS_ACCEPT;
    }
};

class TestModule : public DustModule
{
public:
    virtual ~TestModule()
    {
    }

    virtual DustProcessResult DustResourceInit()
    {
        cout << "TestModule::DustResourceInit" << endl;
        return DUST_PROCESS_ACCEPT;
    }
    virtual DustProcessResult DustResourceRelease()
    {
        cout << "TestModule::DustResourceRelease" << endl;
        return DUST_PROCESS_ACCEPT;
    }

    virtual void* createNative(int typeId) const
    {
        if ( 99 == typeId )
        {
            return new T01();
        }
        return 0;
    }
    virtual DustProcessResult dispatchCommand(int logicId, DustNativeLogic* pLogic, DustEntity cmd, DustEntity param = DUST_ENTITY_INVALID) const
    {
        return DUST_PROCESS_NOTIMPLEMENTED;
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
