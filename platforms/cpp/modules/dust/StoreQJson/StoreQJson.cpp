#include <iostream>
#include <string>

#include "StoreQJson.h"

#include "qjson.h"

using namespace std;


DustResultType AgentStoreReader::DustResourceInit()
{
    qjson::value val("{ \"hello\" : \"world\" } ");

    cout << endl << val << endl << endl;

    return DUST_RESULT_ACCEPT_PASS;
}


DustResultType AgentStoreReader::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}


DustResultType AgentStoreWriter::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}
