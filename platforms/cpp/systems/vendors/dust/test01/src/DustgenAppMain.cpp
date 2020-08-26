#include <DustMain.h>
#include <DustApi.h>

#include <iostream>

#include <vendors/dust/DustgenUnitTest01.h>
#include <dust/DustgenUnitHttp.h>
#include <dust/DustgenUnitStore.h>
#include <MiND/DustgenUnitMindCore.h>
#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustMindUtils.h>

using namespace std;
using namespace DustUnitDustTest01;
using namespace DustUnitDustHttp;
using namespace DustUnitDustStore;
using namespace DustUnitMindNarrative;
using namespace DustUnitMindDialog;
using namespace DustUnitMindGeometry;
using namespace DustUnitMindDrawing;
using namespace DustUnitMindGeneric;

int main(int argc, char **argv)
{
    cout << "calling bootDust..." << endl;

    DustModular::init("DustModDplStl", "DustModText");

    DustModular::addModule("DustModWinGui");
    DustModular::addModule("DustModGraphOpenGl");
    DustModular::addModule("DustModTest01");
    DustModular::addModule("DustModHttpYHirose");
    DustModular::addModule("DustModStoreQJson");

    DustEntity netGetter = DustData::createEntity(DustAgentHttpGetter);
    DustEntity jsonReader = DustData::createEntity(DustAgentStoreReader);

    DustEntity wnd = DustData::createEntity(DustAgentOSWindow);

    DustEntity gl = DustData::createEntity(DustAgentOpenGL);

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

    DustEntity glDraw = DustData::createEntity(DustTypeCollection);

    DustEntity e1 = DustData::createEntity(DustTypeGeoInclude);
    DustData::setRef(e1, DustRefLinkTarget, path);
    DustData::setRef(e1, DustRefCollectionMembers, DustMindUtils::geoCreateData(DustTagGeoRoleRotate, 0.0f, 0.0f, 1.0f));
    DustData::setRef(glDraw, DustRefCollectionMembers, e1);

    e1 = DustData::createEntity(DustTypeGeoInclude);
    DustData::setRef(e1, DustRefLinkTarget, path);
    DustData::setRef(e1, DustRefCollectionMembers, DustMindUtils::geoCreateData(DustTagGeoRoleRotate, 0.0f, 0.1f, 0.0f));
    DustData::setRef(glDraw, DustRefCollectionMembers, e1);

    e1 = DustData::createEntity(DustTypeGeoInclude);
    DustData::setRef(e1, DustRefLinkTarget, path);
    DustData::setRef(e1, DustRefCollectionMembers, DustMindUtils::geoCreateData(DustTagGeoRoleRotate, 0.1f, 0.0f, 0.0f));
    DustData::setRef(glDraw, DustRefCollectionMembers, e1);

    DustData::setRef(gl, DustRefLinkTarget, glDraw);

    DustEntity eMain;
    eMain = DustData::createEntity(DustAgentDialog);
    DustData::setRef(eMain, DustRefCollectionMembers, wnd);
    DustData::setRef(eMain, DustRefCollectionMembers, netGetter);
    DustData::setRef(eMain, DustRefCollectionMembers, jsonReader);
    DustData::setRef(eMain, DustRefCollectionMembers, gl);

    DustData::setRef(DUST_CTX_APP, DustRefAppMain, eMain);

    DustModular::launch();

    cout << "Success." << endl;

    return 0;
}
