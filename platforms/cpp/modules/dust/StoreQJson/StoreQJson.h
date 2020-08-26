#ifndef STORE_QJSON_H_
#define STORE_QJSON_H_

#include <DustKernel.h>

#include <dust/DustgenUnitStore.h>

class AgentStoreReader : public DustNativeLogic
{
    virtual DustResultType DustResourceInit();
    virtual DustResultType DustActionExecute();
};

class AgentStoreWriter : public DustNativeLogic
{
    virtual DustResultType DustActionExecute();
};

#endif /* STORE_QJSON_H_*/
