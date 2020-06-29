#ifndef DUSTGENUNITMINDTOOLS_H_INCLUDED
#define DUSTGENUNITMINDTOOLS_H_INCLUDED

#include <DustApi.h>

namespace DustUnitMindText {
extern DustToken DustUnitText;

extern DustToken DustTypePlainText;

extern DustToken DustTypeChar;
extern DustToken DustIntCharCode;

extern DustToken DustTypeNumberText;
extern DustToken DustRefNumberFormat;
extern DustToken DustIntNumberRadix;

extern DustToken DustConstantCharQuot;
extern DustToken DustConstantCharSolidus;
extern DustToken DustConstantCharReverseSolidus;

extern DustToken DustConstantCharCtrlTAB;
extern DustToken DustConstantCharCtrlLF;
extern DustToken DustConstantCharCtrlCR;
extern DustToken DustConstantCharCtrlFF;
extern DustToken DustConstantCharCtrlBS;

extern DustToken DustAgentDictionary;

extern DustToken DustAgentCharMatcher;
extern DustToken DustAgentTokenMatcher;
extern DustToken DustAgentNumberSci;
extern DustToken DustAgentNumberRad;
};

namespace DustUnitMindTime {
extern DustToken DustUnitTime;

extern DustToken DustRefTimeText;

extern DustToken DustTagTimeType;
extern DustToken DustTagTimeTypeDate;
extern DustToken DustTagTimeTypeTime;
extern DustToken DustTagTimeTypeDateTime;
extern DustToken DustTagTimeTypeDuration;

extern DustToken DustTypeEvent;

extern DustToken DustTagEventLevel;
extern DustToken DustTagEventLevelCritical;
extern DustToken DustTagEventLevelError;
extern DustToken DustTagEventLevelWarning;
extern DustToken DustTagEventLevelnfo;
extern DustToken DustTagEventLevelTrace;
extern DustToken DustTagEventLevelDebug;

extern DustToken DustAgentTime;
};

namespace DustUnitMindGeometry {
extern DustToken DustUnitGeometry;

extern DustToken DustTypeGeoInfo;
extern DustToken DustRefGeoInfoData;

extern DustToken DustTagGeoRole;
extern DustToken DustTagGeoRolePlace;
extern DustToken DustTagGeoRoleRotate;
extern DustToken DustTagGeoRoleScale;

extern DustToken DustTagGeoData;
extern DustToken DustTagCartesianX;
extern DustToken DustTagCartesianY;
extern DustToken DustTagCartesianZ;
extern DustToken DustTagAngleTheta;

extern DustToken DustTypeGeoInclude; // requires ref to target, collection of parameters

extern DustToken DustTypeGeoPath; // requires collection of GeoInfoData points
extern DustToken DustTypeGeoArea; // requires Range
extern DustToken DustRefAreaInfo;
extern DustToken DustTypeGeoComposite; // requires collection of inclusions
extern DustToken DustTypeGeoImage; // requires Binary

extern DustToken DustTagArea;
extern DustToken DustTagAreaRect;
extern DustToken DustTagAreaRoundRect;
extern DustToken DustTagAreaEllipse;
};

namespace DustUnitMindDrawing {
extern DustToken DustUnitDrawing;

extern DustToken DustAgentOSWindow;
extern DustToken DustAgentOpenGL;

extern DustToken DustIntOSWindowWinHDC;
extern DustToken DustIntWindowBufferChanged;
};

namespace DustUnitMindGeneric {
extern DustToken DustUnitGeneric;

extern DustToken DustTypeConnected;
extern DustToken DustRefConnectedRequires;
extern DustToken DustRefConnectedExtends;

extern DustToken DustTypeCollection;
extern DustToken DustRefCollectionMembers;
extern DustToken DustRefCollectionSeparator;

extern DustToken DustTypeLink;
extern DustToken DustRefLinkSource;
extern DustToken DustRefLinkTarget;

extern DustToken DustTypeLimits;
extern DustToken DustIntLimitsMin;
extern DustToken DustIntLimitsMax;

extern DustToken DustTypeRange;
extern DustToken DustRefRangeBegin;
extern DustToken DustRefRangeEnd;

extern DustToken DustTypeColor;
extern DustToken DustRefColorComp;
extern DustToken DustTagColor;
extern DustToken DustTagColorRed;
extern DustToken DustTagColorGreen;
extern DustToken DustTagColorBlue;

extern DustToken DustTypeColored;
extern DustToken DustRefColoredColor;

extern DustToken DustGenTag;
extern DustToken DustGenTagClosed;
};

namespace DustUnitMindBinary {
extern DustToken DustUnitBinary;

extern DustToken DustTypeBinary;
extern DustToken DustRefBinaryUrl;

extern DustToken DustTagBinaryType;

extern DustToken DustTypeStream;
extern DustToken DustRefStreamBinary;
extern DustToken DustIntStreamPos;
extern DustToken DustIntStreamOk;

extern DustToken DustAgentStreamWriter;
extern DustToken DustAgentStreamReader;
};

#endif // DUSTGENUNITMINDTOOLS_H_INCLUDED
