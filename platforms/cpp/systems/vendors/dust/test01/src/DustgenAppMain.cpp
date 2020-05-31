#include <DustMain.h>
#include <DustApi.h>

#include <iostream>

#include <vendors/dust/DustgenUnitTest01.h>
#include <MiND/DustgenUnitMindCore.h>

using namespace std;
using namespace DustUnitDustTest01;
using namespace DustUnitMindNarrative;

int main(int argc, char **argv)
{
    cout << "calling bootDust..." << endl;

    dustBoot(argc, argv);

    DustEntity wnd = DustData::createEntity(DustAgentTestWindow);
    DustEntity gl = DustData::createEntity(DustAgentTestOpenGL);

    DustData::setRef(wnd, DustRefPainter, gl);

    DustData::setRef(DUST_CTX_APP, DustRefAppMain, wnd);

    dustLaunch();

    cout << "Success." << endl;

    dustShutdown();

    return 0;
}
