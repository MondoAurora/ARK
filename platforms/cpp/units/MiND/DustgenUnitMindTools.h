#ifndef DUSTGENUNITMINDTOOLS_H_INCLUDED
#define DUSTGENUNITMINDTOOLS_H_INCLUDED

#include <DustApi.h>

namespace DustUnitMindText {
extern DustToken DustUnitText;
extern DustToken DustTypePlainText;
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
};

namespace DustUnitMindStream {
extern DustToken DustUnitStream;

extern DustToken DustTypeStream;
extern DustToken DustIntStreamPos;
extern DustToken DustRefStreamOk;
extern DustToken DustRefStreamUrl;

extern DustToken DustAgentWriter;
extern DustToken DustAgentReader;
};

#endif // DUSTGENUNITMINDTOOLS_H_INCLUDED
