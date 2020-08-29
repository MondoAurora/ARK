
#include "DustMindUtils.h"

using namespace DustUnitMindGeometry;
using namespace DustUnitMindGeneric;
using namespace DustUnitMindText;

using namespace std;

void DustMindUtils::setPlainText(DustEntity entity, DustEntity token, const char* str,  long key)
{
    DustEntity eTxt = DustData::getRef(entity, token, DUST_ENTITY_INVALID, key);
    if ( !eTxt ) {
        eTxt = DustData::createEntity(DustTypePlainText);
        DustData::setRef(entity, token, eTxt, key);
    }

    string *pStr = (string *) DustData::getNative(eTxt);
    (*pStr) = str;
}

bool DustMindUtils::readPlainText(DustEntity entity, DustEntity token, string* pTarget,  long key)
{
    DustEntity eTxt = DustData::getRef(entity, token, DUST_ENTITY_INVALID, key);
    if ( eTxt ) {
        string *pStr = (string *) DustData::getNative(eTxt, DUST_ENTITY_APPEND, false);
//        string *pStr = (string *) DustData::getNative(eTxt);
        if ( pStr ) {
            (*pTarget) = *pStr;
            return true;
        }
    }
    return false;
}

DustEntity DustMindUtils::setColor(double red, double green, double blue, DustEntity col)
{
    if (! col )
    {
        col = DustData::createEntity(DustTypeColor);
    }

    DustData::setReal(col, DustRefColorComp, red, DustTagColorRed);
    DustData::setReal(col, DustRefColorComp, green, DustTagColorGreen);
    DustData::setReal(col, DustRefColorComp, blue, DustTagColorBlue);

    return col;
}

DustEntity DustMindUtils::geoCreateData(DustEntity role, double x, double y, double z)
{
    DustEntity gd = DustData::createEntity(DustTypeGeoInfo);

    DustUtils::tag(gd, DUST_ACCESS_SET, role);

    DustData::setReal(gd, DustRefGeoInfoData, x, DustTagCartesianX);
    DustData::setReal(gd, DustRefGeoInfoData, y, DustTagCartesianY);
    DustData::setReal(gd, DustRefGeoInfoData, z, DustTagCartesianZ);

    return gd;
}

DustEntity DustMindUtils::geoPath(DustEntity path, DustEntity color, double x, double y, double z)
{
    if ( DUST_ENTITY_INVALID == path )
    {
        path = DustData::createEntity(DustTypeGeoPath);
    }
    DustEntity pt = geoCreateData(DustTagGeoRolePlace, x, y, z);
    DustData::setRef(path, DustRefCollectionMembers, pt);

    if ( color )
    {
        DustData::setRef(pt, DustRefColoredColor, color);
    }

    return path;
}
