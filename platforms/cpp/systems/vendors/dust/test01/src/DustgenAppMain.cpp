#include <DustMain.h>
#include <DustApi.h>

#include <iostream>

#include <vendors/dust/DustgenUnitTest01.h>
#include <MiND/DustgenUnitMindCore.h>
#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustMindUtils.h>

using namespace std;
using namespace DustUnitDustTest01;
using namespace DustUnitMindNarrative;
using namespace DustUnitMindDialog;
using namespace DustUnitMindGeometry;
using namespace DustUnitMindGeneric;

int main(int argc, char **argv)
{
    cout << "calling bootDust..." << endl;

    DustModular::init("DustModDplStl", "DustModText");

    DustModular::addModule("DustModWinGui");
    DustModular::addModule("DustModGraphOpenGl");
    DustModular::addModule("DustModTest01");

    DustEntity wnd = DustData::createEntity(DustAgentTestWindow);

//    DustEntity gl = DustData::createEntity(DustAgentTestOpenGL);
//    DustData::setRef(wnd, DustRefPainter, gl);
    DustEntity gl = wnd;

    DustEntity col1 = DustMindUtils::setColor(1.0f, 0.0f, 0.0f);
    DustEntity col2 = DustMindUtils::setColor(0.0f, 1.0f, 0.0f);

    DustEntity path = DustMindUtils::geoPath(DUST_ENTITY_INVALID, col2, 0.0, 1.0);
    DustMindUtils::geoPath(path, col1, 0.5, 0.0);
    DustMindUtils::geoPath(path, col2, 0.5, 0.2);
    DustMindUtils::geoPath(path, col1, 0.2, -0.2);
    DustMindUtils::geoPath(path, col1, -0.2, -0.2);
    DustMindUtils::geoPath(path, col2, -0.5, 0.2);
    DustMindUtils::geoPath(path, col1, -0.5, 0.0);

    DustUtils::tag(path, DUST_ACCESS_SET, DustGenTagClosed);

    int len = DustData::getMemberCount(path, DustRefCollectionMembers);
    cout << "Path members " << len << endl;

    DustEntity e1 = DustData::createEntity(DustTypeGeoInclude);
    DustData::setRef(e1, DustRefLinkTarget, path);
    DustData::setRef(e1, DustRefCollectionMembers, DustMindUtils::geoCreateData(DustTagGeoRoleRotate, 0.0f, 0.0f, 1.0f));
    DustData::setRef(gl, DustRefCollectionMembers, e1);

    e1 = DustData::createEntity(DustTypeGeoInclude);
    DustData::setRef(e1, DustRefLinkTarget, path);
    DustData::setRef(e1, DustRefCollectionMembers, DustMindUtils::geoCreateData(DustTagGeoRoleRotate, 0.0f, 0.1f, 0.0f));
    DustData::setRef(gl, DustRefCollectionMembers, e1);

    e1 = DustData::createEntity(DustTypeGeoInclude);
    DustData::setRef(e1, DustRefLinkTarget, path);
    DustData::setRef(e1, DustRefCollectionMembers, DustMindUtils::geoCreateData(DustTagGeoRoleRotate, 0.1f, 0.0f, 0.0f));
    DustData::setRef(gl, DustRefCollectionMembers, e1);

    DustEntity eMain;
    eMain = DustData::createEntity(DustAgentTest01);
//    eMain = wnd;

    DustData::setRef(DUST_CTX_APP, DustRefAppMain, eMain);

    DustModular::launch();

    cout << "Success." << endl;

    return 0;
}
