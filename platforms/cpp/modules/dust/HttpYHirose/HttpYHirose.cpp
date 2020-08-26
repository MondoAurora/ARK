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

using namespace std;


DustResultType AgentHttpGetter::DustResourceInit()
{
    httplib::Client client("montru.ai", 8081);

    auto res = client.Get("/", [](uint64_t len, uint64_t total)
        {
            printf("%d / %d bytes => %d%% complete\n",
                   (int)len, (int)total,
                   (int)(len*100/total));
            return true;
        }
    );

    if (res)
    {
        cout << res->status << endl;
        cout << res->get_header_value("Content-Type") << endl;
        cout << res->body << endl;
    }

    return DUST_RESULT_ACCEPT;
}

DustResultType AgentHttpGetter::DustActionExecute()
{
    return DUST_RESULT_ACCEPT_PASS;
}
