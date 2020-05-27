
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


using namespace DustUnitMindStream;

DustToken DustUnitMindStream::DustUnitStream("Stream");

DustToken DustUnitMindStream::DustTypeStream(DustUnitStream, "Stream", DUST_IDEA_TYPE);
DustToken DustUnitMindStream::DustIntStreamPos(DustTypeStream, "Pos", DUST_VAL_INTEGER, DUST_COLL_SINGLE);
DustToken DustUnitMindStream::DustIntStreamOk(DustTypeStream, "Ok", DUST_VAL_INTEGER, DUST_COLL_SINGLE);
DustToken DustUnitMindStream::DustRefStreamUrl(DustTypeStream, "Url", DUST_VAL_REF, DUST_COLL_SINGLE);

DustToken DustUnitMindStream::DustAgentWriter(DustUnitStream, "Writer", DUST_IDEA_AGENT);
DustToken DustUnitMindStream::DustAgentReader(DustUnitStream, "Reader", DUST_IDEA_AGENT);

