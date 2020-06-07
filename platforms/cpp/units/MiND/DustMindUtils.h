#ifndef DUSTMINDUTILS_H_INCLUDED
#define DUSTMINDUTILS_H_INCLUDED

#include <DustUtils.h>

#include "DustgenUnitMindTools.h"

using namespace DustUnitMindGeometry;
using namespace DustUnitMindGeneric;

class DustMindUtils {
public:
    static DustEntity setColor(double red, double green, double blue, DustEntity col = DUST_ENTITY_INVALID);

    static DustEntity geoCreateData(DustEntity role, double x, double y, double z);
    static DustEntity geoPath(DustEntity path, DustEntity color, double x, double y, double z = 0.0);
};


#endif // DUSTMINDUTILS_H_INCLUDED
