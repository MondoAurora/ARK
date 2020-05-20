#ifndef DUSTGENUNITMINDCORE_H_INCLUDED
#define DUSTGENUNITMINDCORE_H_INCLUDED

#include <DustApi.h>

namespace DustUnitMindModel {
extern DustToken DustUnitModel;

extern DustToken DustTypeEntity;
extern DustToken DustRefUnit;
extern DustToken DustIntId;
extern DustToken DustRefPrimaryType;
extern DustToken DustRefGlobalId;
extern DustToken DustRefOwner;
extern DustToken DustRefTags;

extern DustToken DustTypeUnit;
};

namespace DustUnitMindIdea {
extern DustToken DustUnitIdea;

extern DustToken DustTypeType;
extern DustToken DustTypeMember;
extern DustToken DustTypeAgent;
extern DustToken DustTypeTag;

extern DustToken DustConstValInteger;
extern DustToken DustConstValReal;
extern DustToken DustConstValRef;

extern DustToken DustConstCollSingle;
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

extern DustToken DustConstAccessGet;
extern DustToken DustConstAccessSet;
extern DustToken DustConstAccessMove;
extern DustToken DustConstAccessRemove;
extern DustToken DustConstAccessClear;
};

#endif // DUSTGENUNITMINDCORE_H_INCLUDED
