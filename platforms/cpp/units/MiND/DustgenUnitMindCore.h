#ifndef DUSTGENUNITMINDCORE_H_INCLUDED
#define DUSTGENUNITMINDCORE_H_INCLUDED

#include <DustApi.h>

namespace DustUnitMindModel {
extern DustToken DustUnitModel;

extern DustToken DustTypeEntity;
extern DustToken DustRefGlobalId;
extern DustToken DustRefOwner;

extern DustToken DustTypeUnit;
};

namespace DustUnitMindIdea {
extern DustToken DustUnitIdea;

extern DustToken DustTypeType;
extern DustToken DustTypeMember;
extern DustToken DustTypeAgent;
extern DustToken DustTypeConst;
extern DustToken DustTypeTag;

extern DustToken DustConstValInteger;
extern DustToken DustConstValReal;
extern DustToken DustConstValRef;

extern DustToken DustConstCollSet;
extern DustToken DustConstCollArr;
extern DustToken DustConstCollMap;
};

namespace DustUnitMindNarrative {
extern DustToken DustUnitNarrative;

extern DustToken DustConstResultReject;
extern DustToken DustConstResultAcceptPass;
extern DustToken DustConstResultAccept;
extern DustToken DustConstResultAcceptRead;
extern DustToken DustConstResultRead;
};

namespace DustUnitMindDialog {
extern DustToken DustUnitDialog;

extern DustToken DustConstChangeRefSet;
extern DustToken DustConstChangeRefRemove;
extern DustToken DustConstChangeClear;
};

#endif // DUSTGENUNITMINDCORE_H_INCLUDED
