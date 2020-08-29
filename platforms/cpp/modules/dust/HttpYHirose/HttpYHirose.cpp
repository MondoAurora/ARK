#include <iostream>
#include <string>

#include "HttpYHirose.h"

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x501
#define IPV6_V6ONLY 0
#define _stricmp strcmp

#include <Windows.h>
#include <iostream>
#include <cstring>
#include "httplib/httplib.h"

#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustMindUtils.h>


using namespace std;

using namespace DustUnitMindGeneric;
using namespace DustUnitMindText;
using namespace DustUnitMindNet;

class ClientConfig
{
public:
    string hostName;
    long port;
    string path;

    ClientConfig()
    {
        DustRef self;
        DustEntity host;

        host = DustData::getRef(self, DustRefServiceHost);
        DustMindUtils::readPlainText(host, DustRefHostName, &hostName);

        port = DustData::getInteger(self, DustIntServicePort);
        DustMindUtils::readPlainText(self, DustRefServicePath, &path);
    }

    virtual ~ClientConfig() { }
};


DustResultType AgentHttpGetter::DustResourceInit()
{
    ClientConfig ccfg;
    httplib::Client client(ccfg.hostName, ccfg.port);

    auto res = client.Get(ccfg.path.c_str());
    const char * ret = res ? res->body.c_str() : 0;

    DustRef self;
    DustMindUtils::setPlainText(self, DustRefLinkTarget, ret);

    if (res)
    {
        DustUtils::log()  << "GET return status: " << res->status << ", content type: " << res->get_header_value("Content-Type") << endl;
        DustUtils::log()  << res->body << endl << endl;
    }

    return DUST_RESULT_ACCEPT_PASS;
}

DustResultType AgentHttpGetter::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}

DustResultType AgentHttpPoster::DustResourceInit()
{
    ClientConfig ccfg;
    httplib::Client client(ccfg.hostName, ccfg.port);

    DustRef self;
    string data;
    DustMindUtils::readPlainText(self, DustRefLinkSource, &data);

    auto res = client.Post(ccfg.path.c_str(), data.c_str(), "application/json" );

    if (res)
    {
        DustUtils::log()  << "POST return status: " << res->status << ", content type: " << res->get_header_value("Content-Type") << endl;
        DustUtils::log()  << res->body << endl << endl;
    }

    return DUST_RESULT_ACCEPT;
}

DustResultType AgentHttpPoster::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}
