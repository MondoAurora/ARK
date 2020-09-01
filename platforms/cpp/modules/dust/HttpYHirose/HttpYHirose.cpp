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

class ClientHelper
{
public:
    string hostName;
    long port;
    string path;

    ClientHelper() {
        DustRef self;
        DustEntity host;

        host = DustData::getRef(self, DustRefServiceHost);
        DustMindUtils::readPlainText(host, DustRefHostName, &hostName);

        port = DustData::getInteger(self, DustIntServicePort);
        DustMindUtils::readPlainText(self, DustRefServicePath, &path);
    }

    virtual ~ClientHelper() { }

    inline void optLogRes(const char* cmd, shared_ptr<httplib::Response> res) {
        if (res) {
            DustUtils::log()  << cmd << " return status: " << res->status
                << ", content type: " << res->get_header_value("Content-Type") << endl
                << res->body << endl << endl;
        }
    }
};


DustResultType AgentHttpGetter::DustResourceInit()
{
    ClientHelper cliHlp;
    httplib::Client client(cliHlp.hostName, cliHlp.port);

    auto res = client.Get(cliHlp.path.c_str());
    const char * ret = res ? res->body.c_str() : 0;

    DustRef self;
    DustMindUtils::setPlainText(self, DustRefLinkTarget, ret);

    cliHlp.optLogRes("GET", res);

    return DUST_RESULT_ACCEPT_PASS;
}

DustResultType AgentHttpGetter::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}

DustResultType AgentHttpPoster::DustResourceInit()
{
    ClientHelper cliHlp;
    httplib::Client client(cliHlp.hostName, cliHlp.port);

    DustRef self;
    string data;
    DustMindUtils::readPlainText(self, DustRefLinkSource, &data);

    auto res = client.Post(cliHlp.path.c_str(), data.c_str(), "application/json" );

    cliHlp.optLogRes("POST", res);

    return DUST_RESULT_ACCEPT;
}

DustResultType AgentHttpPoster::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}
