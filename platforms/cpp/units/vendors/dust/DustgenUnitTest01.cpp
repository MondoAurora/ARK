
#include "DustgenUnitTest01.h"


using namespace DustUnitDustTest01;

DustToken DustUnitDustTest01::DustUnitTest01("Test01");

DustToken DustUnitDustTest01::DustTypeColor(DustUnitTest01, "Color", DUST_IDEA_TYPE);
DustToken DustUnitDustTest01::DustIntCode(DustTypeColor, "Code", DUST_VAL_INTEGER, DUST_COLL_SINGLE);

DustToken DustUnitDustTest01::DustTypePoint(DustUnitTest01, "Point", DUST_IDEA_TYPE);
DustToken DustUnitDustTest01::DustRealX(DustTypePoint, "X", DUST_VAL_REAL, DUST_COLL_SINGLE);
DustToken DustUnitDustTest01::DustRealY(DustTypePoint, "Y", DUST_VAL_REAL, DUST_COLL_SINGLE);
