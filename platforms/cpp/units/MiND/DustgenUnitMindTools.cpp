
#include "DustgenUnitMindTools.h"

using namespace DustUnitMindText;

DustToken DustUnitMindText::DustUnitText("MindText");

DustToken DustUnitMindText::DustTypePlainText(DustUnitText, "PlainText", DUST_IDEA_TYPE);

DustToken DustUnitMindText::DustTypeChar(DustUnitText, "Char", DUST_IDEA_TYPE);
DustToken DustUnitMindText::DustIntCharCode(DustTypeChar, "Code", DUST_VAL_INTEGER, DUST_COLL_SINGLE);

DustToken DustUnitMindText::DustTypeNumberText(DustUnitText, "NumberText", DUST_IDEA_TYPE);
DustToken DustUnitMindText::DustRefNumberFormat(DustTypeNumberText, "Format", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindText::DustIntNumberRadix(DustTypeNumberText, "Radix", DUST_VAL_INTEGER, DUST_COLL_SINGLE);

DustToken DustUnitMindText::DustConstantCharQuot(DustUnitText, "Quote", DUST_NATIVE_CONSTANT);
DustToken DustUnitMindText::DustConstantCharSolidus(DustUnitText, "Solidus", DUST_NATIVE_CONSTANT);
DustToken DustUnitMindText::DustConstantCharReverseSolidus(DustUnitText, "ReverseSolidus", DUST_NATIVE_CONSTANT);

DustToken DustUnitMindText::DustConstantCharCtrlTAB(DustUnitText, "Tab", DUST_NATIVE_CONSTANT);
DustToken DustUnitMindText::DustConstantCharCtrlLF(DustUnitText, "LineFeed", DUST_NATIVE_CONSTANT);
DustToken DustUnitMindText::DustConstantCharCtrlCR(DustUnitText, "CarriageReturn", DUST_NATIVE_CONSTANT);
DustToken DustUnitMindText::DustConstantCharCtrlFF(DustUnitText, "FormFeed", DUST_NATIVE_CONSTANT);
DustToken DustUnitMindText::DustConstantCharCtrlBS(DustUnitText, "Backspace", DUST_NATIVE_CONSTANT);

DustToken DustUnitMindText::DustAgentDictionary(DustUnitText, "Dictionary", DUST_IDEA_AGENT);

DustToken DustUnitMindText::DustAgentCharMatcher(DustUnitText, "CharMatcher", DUST_IDEA_AGENT);
DustToken DustUnitMindText::DustAgentTokenMatcher(DustUnitText, "TokenMatcher", DUST_IDEA_AGENT);
DustToken DustUnitMindText::DustAgentNumberSci(DustUnitText, "NumberSci", DUST_IDEA_AGENT);
DustToken DustUnitMindText::DustAgentNumberRad(DustUnitText, "NumberRad", DUST_IDEA_AGENT);

using namespace DustUnitMindEvent;

DustToken DustUnitMindEvent::DustUnitEvent("Event");

DustToken DustUnitMindEvent::DustTypeEvent(DustUnitEvent, "Event", DUST_IDEA_TYPE);

DustToken DustUnitMindEvent::DustTagEventLevel(DustUnitEvent, "EventLevel", DUST_IDEA_TAG);
DustToken DustUnitMindEvent::DustTagEventLevelCritical(DustTagEventLevel, "Critical", DUST_IDEA_TAG);
DustToken DustUnitMindEvent::DustTagEventLevelError(DustTagEventLevel, "Error", DUST_IDEA_TAG);
DustToken DustUnitMindEvent::DustTagEventLevelWarning(DustTagEventLevel, "Warning", DUST_IDEA_TAG);
DustToken DustUnitMindEvent::DustTagEventLevelnfo(DustTagEventLevel, "lnfo", DUST_IDEA_TAG);
DustToken DustUnitMindEvent::DustTagEventLevelTrace(DustTagEventLevel, "Trace", DUST_IDEA_TAG);
DustToken DustUnitMindEvent::DustTagEventLevelDebug(DustTagEventLevel, "Debug", DUST_IDEA_TAG);

DustToken DustUnitMindEvent::DustAgentTime(DustUnitEvent, "Time", DUST_IDEA_AGENT);



using namespace DustUnitMindGeometry;

DustToken DustUnitMindGeometry::DustUnitGeometry("Geometry");

DustToken DustUnitMindGeometry::DustTypeGeoInfo(DustUnitGeometry, "GeoInfo", DUST_IDEA_TYPE);
DustToken DustUnitMindGeometry::DustRefGeoInfoData(DustTypeGeoInfo, "Data", DUST_VAL_REAL, DUST_COLL_MAP);

DustToken DustUnitMindGeometry::DustTagGeoRole(DustUnitGeometry, "Role", DUST_IDEA_TAG);
DustToken DustUnitMindGeometry::DustTagGeoRolePlace(DustTagGeoRole, "Place", DUST_IDEA_TAG);
DustToken DustUnitMindGeometry::DustTagGeoRoleRotate(DustTagGeoRole, "Rotate", DUST_IDEA_TAG);
DustToken DustUnitMindGeometry::DustTagGeoRoleScale(DustTagGeoRole, "Scale", DUST_IDEA_TAG);

DustToken DustUnitMindGeometry::DustTagGeoData(DustUnitGeometry, "GeoData", DUST_IDEA_TAG);
DustToken DustUnitMindGeometry::DustTagCartesianX(DustTagGeoData, "CartesianX", DUST_IDEA_TAG);
DustToken DustUnitMindGeometry::DustTagCartesianY(DustTagGeoData, "CartesianY", DUST_IDEA_TAG);
DustToken DustUnitMindGeometry::DustTagCartesianZ(DustTagGeoData, "CartesianZ", DUST_IDEA_TAG);

DustToken DustUnitMindGeometry::DustTypeGeoInclude(DustUnitGeometry, "Include", DUST_IDEA_TYPE);

DustToken DustUnitMindGeometry::DustTypeGeoPath(DustUnitGeometry, "Path", DUST_IDEA_TYPE);
DustToken DustUnitMindGeometry::DustTypeGeoArea(DustUnitGeometry, "Area", DUST_IDEA_TYPE);
DustToken DustUnitMindGeometry::DustRefAreaInfo(DustTypeGeoArea, "Info", DUST_VAL_REF, DUST_COLL_MAP);
DustToken DustUnitMindGeometry::DustTypeGeoComposite(DustUnitGeometry, "Composite", DUST_IDEA_TYPE);
DustToken DustUnitMindGeometry::DustTypeGeoImage(DustUnitGeometry, "Image", DUST_IDEA_TYPE);

DustToken DustUnitMindGeometry::DustTagArea(DustUnitGeometry, "Area", DUST_IDEA_TAG);
DustToken DustUnitMindGeometry::DustTagAreaRect(DustTagArea, "Rect", DUST_IDEA_TAG);
DustToken DustUnitMindGeometry::DustTagAreaEllipse(DustTagArea, "Ellipse", DUST_IDEA_TAG);


using namespace DustUnitMindGeneric;

DustToken DustUnitMindGeneric::DustUnitGeneric("Generic");

DustToken DustUnitMindGeneric::DustTypeConnected(DustUnitGeneric, "Connected", DUST_IDEA_TYPE);
DustToken DustUnitMindGeneric::DustRefConnectedRequires(DustTypeConnected, "Requires", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindGeneric::DustRefConnectedExtends(DustTypeConnected, "Extends", DUST_VAL_REF, DUST_COLL_SINGLE);

DustToken DustUnitMindGeneric::DustTypeCollection(DustUnitGeneric, "Collection", DUST_IDEA_TYPE);
DustToken DustUnitMindGeneric::DustRefCollectionMembers(DustTypeCollection, "Members", DUST_VAL_REF, DUST_COLL_ARR);
DustToken DustUnitMindGeneric::DustRefCollectionSeparator(DustTypeCollection, "Separator", DUST_VAL_REF, DUST_COLL_SINGLE);

DustToken DustUnitMindGeneric::DustTypeLink(DustUnitGeneric, "Link", DUST_IDEA_TYPE);
DustToken DustUnitMindGeneric::DustRefLinkSource(DustTypeLink, "Source", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindGeneric::DustRefLinkTarget(DustTypeLink, "Target", DUST_VAL_REF, DUST_COLL_SINGLE);

DustToken DustUnitMindGeneric::DustTypeLimits(DustUnitGeneric, "Limits", DUST_IDEA_TYPE);
DustToken DustUnitMindGeneric::DustIntLimitsMin(DustTypeLimits, "Min", DUST_VAL_INTEGER, DUST_COLL_SINGLE);
DustToken DustUnitMindGeneric::DustIntLimitsMax(DustTypeLimits, "Max", DUST_VAL_INTEGER, DUST_COLL_SINGLE);

DustToken DustUnitMindGeneric::DustTypeRange(DustUnitGeneric, "Range", DUST_IDEA_TYPE);
DustToken DustUnitMindGeneric::DustRefRangeBegin(DustTypeRange, "Begin", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindGeneric::DustRefRangeEnd(DustTypeRange, "End", DUST_VAL_REF, DUST_COLL_SINGLE);

DustToken DustUnitMindGeneric::DustTypeColor(DustUnitGeneric, "Color", DUST_IDEA_TYPE);
DustToken DustUnitMindGeneric::DustRefColorComp(DustTypeColor, "Comp", DUST_VAL_REAL, DUST_COLL_MAP);
DustToken DustUnitMindGeneric::DustTagColor(DustUnitGeneric, "Color", DUST_IDEA_TAG);
DustToken DustUnitMindGeneric::DustTagColorRed(DustTagColor, "Red", DUST_IDEA_TAG);
DustToken DustUnitMindGeneric::DustTagColorGreen(DustTagColor, "Green", DUST_IDEA_TAG);
DustToken DustUnitMindGeneric::DustTagColorBlue(DustTagColor, "Blue", DUST_IDEA_TAG);

DustToken DustUnitMindGeneric::DustGenTag(DustUnitGeneric, "GenericTag", DUST_IDEA_TAG);
DustToken DustUnitMindGeneric::DustGenTagClosed(DustGenTag, "Closed", DUST_IDEA_TAG);

using namespace DustUnitMindBinary;

DustToken DustUnitMindBinary::DustUnitBinary("Binary");

DustToken DustUnitMindBinary::DustTypeBinary(DustUnitBinary, "Binary", DUST_IDEA_TYPE);
DustToken DustUnitMindBinary::DustRefBinaryUrl(DustTypeBinary, "Url", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindBinary::DustTagBinaryType(DustUnitBinary, "BinaryType", DUST_IDEA_TAG);

DustToken DustUnitMindBinary::DustTypeStream(DustUnitBinary, "Stream", DUST_IDEA_TYPE);
DustToken DustUnitMindBinary::DustIntStreamPos(DustTypeStream, "Pos", DUST_VAL_INTEGER, DUST_COLL_SINGLE);
DustToken DustUnitMindBinary::DustIntStreamOk(DustTypeStream, "Ok", DUST_VAL_INTEGER, DUST_COLL_SINGLE);
DustToken DustUnitMindBinary::DustRefStreamBinary(DustTypeStream, "Binary", DUST_VAL_REF, DUST_COLL_SINGLE);

DustToken DustUnitMindBinary::DustAgentStreamWriter(DustUnitBinary, "Writer", DUST_IDEA_AGENT);
DustToken DustUnitMindBinary::DustAgentStreamReader(DustUnitBinary, "Reader", DUST_IDEA_AGENT);

