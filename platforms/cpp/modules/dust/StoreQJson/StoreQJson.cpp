#include <iostream>
#include <string>

#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustMindUtils.h>

#include "StoreQJson.h"
#include "qjson.h"

using namespace std;


DustResultType AgentStoreReader::DustResourceInit()
{
    DustRef self;
    string data;
    DustMindUtils::readPlainText(self, DustRefLinkSource, &data);
    qjson::value val(data);

    DustUtils::log() << "StoreReader received string " << data << endl << "   as JSON value: " << val << endl;

    return DUST_RESULT_ACCEPT_PASS;
}


DustResultType AgentStoreReader::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}


DustResultType AgentStoreWriter::DustResourceInit()
{
    qjson::value val("{ \"data\" : { \"id\" : \"test01\" , \"target\" : \"World\" , \"from\" : \"CPP client\" } } ");

    ostringstream oss;
    oss << val;
    string data = oss.str();

    DustUtils::log() << "StoreWriter created " << data << endl;

    DustRef self;
    DustMindUtils::setPlainText(self, DustRefLinkTarget, data.c_str());

    return DUST_RESULT_ACCEPT_PASS;
}

DustResultType AgentStoreWriter::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}
