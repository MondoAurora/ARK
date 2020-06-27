
#include "DustgenUnitTest01.h"


using namespace DustUnitDustTest01;

DustToken DustUnitDustTest01::DustUnitTest01("Test01");

DustToken DustUnitDustTest01::DustAgentTest01(DustUnitTest01, "Agent01", DUST_IDEA_AGENT);
DustToken DustUnitDustTest01::DustAgentTestWindow(DustUnitTest01, "Window", DUST_IDEA_AGENT);
DustToken DustUnitDustTest01::DustAgentTestOpenGL(DustUnitTest01, "OpenGL", DUST_IDEA_AGENT);

DustToken DustUnitDustTest01::DustRefPainter(DustAgentTestWindow, "Painter", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitDustTest01::DustIntHDC(DustAgentTestWindow, "HDC", DUST_VAL_INTEGER, DUST_COLL_SINGLE);
DustToken DustUnitDustTest01::DustIntBufferChanged(DustAgentTestWindow, "BufferChanged", DUST_VAL_INTEGER, DUST_COLL_SINGLE);

DustToken DustUnitDustTest01::DustTypeColor(DustUnitTest01, "Color", DUST_IDEA_TYPE);
DustToken DustUnitDustTest01::DustIntCode(DustTypeColor, "Code", DUST_VAL_INTEGER, DUST_COLL_SINGLE);

DustToken DustUnitDustTest01::DustTypePoint(DustUnitTest01, "Point", DUST_IDEA_TYPE);
DustToken DustUnitDustTest01::DustRealX(DustTypePoint, "X", DUST_VAL_REAL, DUST_COLL_SINGLE);
DustToken DustUnitDustTest01::DustRealY(DustTypePoint, "Y", DUST_VAL_REAL, DUST_COLL_SINGLE);
