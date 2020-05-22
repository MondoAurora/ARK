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

extern DustToken DustTagVal;
extern DustToken DustTagValInteger;
extern DustToken DustTagValReal;
extern DustToken DustTagValRef;

extern DustToken DustTagColl;
extern DustToken DustTagCollSingle;
extern DustToken DustTagCollSet;
extern DustToken DustTagCollArr;
extern DustToken DustTagCollMap;
};

namespace DustUnitMindNarrative {
extern DustToken DustUnitNarrative;

extern DustToken DustTagResult;
extern DustToken DustTagResultReject;
extern DustToken DustTagResultAcceptPass;
extern DustToken DustTagResultAccept;
extern DustToken DustTagResultAcceptRead;
extern DustToken DustTagResultRead;

extern DustToken DustAgentDialog;
extern DustToken DustAgentSequence;
extern DustToken DustAgentSelect;
extern DustToken DustAgentRepeat;
};

namespace DustUnitMindDialog {
extern DustToken DustUnitDialog;

extern DustToken DustTagAccess;
extern DustToken DustTagAccessGet;
extern DustToken DustTagAccessSet;
extern DustToken DustTagAccessMove;
extern DustToken DustTagAccessRemove;
extern DustToken DustTagAccessClear;
};

#endif // DUSTGENUNITMINDCORE_H_INCLUDED
