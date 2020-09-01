#include <iostream>
#include <string>

#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustMindUtils.h>

#include <DustKernel.h>

#include "StoreJsonNlohmann.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

DustResultType AgentStoreReader::DustResourceInit()
{
    DustRef self;
    string data;
    DustMindUtils::readPlainText(self, DustRefLinkSource, &data);

    auto val = json::parse(data);

    DustUtils::log() << "StoreReader received string " << data << endl
        << "   as JSON value: " << val << endl;

    return DUST_RESULT_ACCEPT_PASS;
}


DustResultType AgentStoreReader::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}

DustResultType jsonVisitor(DustVisitState state, DustAccessData &data, void* pHint)
{
    switch ( state ) {
    case DUST_VISIT_VALUE:
        DustUtils::log() << "jsonVisitor received entity: " << data.entity
            << " token: " << data.token << " key: " << data.key
            << " valLong: " << data.valLong << " valDouble: " << data.valDouble
            << endl;
        break;
    default:
        break;
    }

    return DUST_RESULT_ACCEPT_PASS;
}


DustResultType AgentStoreWriter::DustResourceInit()
{
    json val = "{ \"data\" : { \"id\" : \"test01\" , \"target\" : \"World\" , \"from\" : \"CPP client\" } } "_json;
    string data = val.dump();
    DustUtils::log() << "StoreWriter created " << data << endl;

    DustRef self;

    DustEntity target = DustData::getRef(self, DustRefLinkSource);
    DustAccessData da(DUST_ACCESS_VISIT, target, DUST_ENTITY_INVALID);
    DustDiscovery::visit(da, jsonVisitor, &val);

    DustMindUtils::setPlainText(self, DustRefLinkTarget, data.c_str());

    return DUST_RESULT_ACCEPT_PASS;
}

DustResultType AgentStoreWriter::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}
