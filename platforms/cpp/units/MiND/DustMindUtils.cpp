
#include "DustMindUtils.h"

using namespace DustUnitMindGeometry;
using namespace DustUnitMindGeneric;

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
