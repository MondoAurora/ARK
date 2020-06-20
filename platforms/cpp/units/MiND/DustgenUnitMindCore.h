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

extern DustToken DustTypeValue;
extern DustToken DustIntValueKey;
extern DustToken DustIntValue;
extern DustToken DustRealValue;
extern DustToken DustRefValue;

extern DustToken DustTypeUnit;
extern DustToken DustTypeSystem;
};

namespace DustUnitMindIdea {
extern DustToken DustUnitIdea;

extern DustToken DustTypeType;
extern DustToken DustTypeMember;
extern DustToken DustTypeAgent;
extern DustToken DustTypeTag;

extern DustToken DustTypeConstant;
extern DustToken DustConstantNull;
extern DustToken DustConstantTrue;
extern DustToken DustConstantFalse;

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

extern DustToken DustAgentSequence;
extern DustToken DustAgentSelect;
extern DustToken DustAgentRepeat;
};

namespace DustUnitMindDialog {
extern DustToken DustUnitDialog;

extern DustToken DustTagCtx;
extern DustToken DustTagCtxSelf;
extern DustToken DustTagCtxDialog;
extern DustToken DustTagCtxApp;
extern DustToken DustTagCtxSystem;

extern DustToken DustAgentApp;
extern DustToken DustAgentDialog;

extern DustToken DustRefAppSystem;
extern DustToken DustRefAppMain;
extern DustToken DustRefAppDialogs;

extern DustToken DustTagAccess;
extern DustToken DustTagAccessGet;
extern DustToken DustTagAccessSet;
extern DustToken DustTagAccessMove;
extern DustToken DustTagAccessRemove;
extern DustToken DustTagAccessClear;
extern DustToken DustTagAccessCreate;
extern DustToken DustTagAccessDelete;
extern DustToken DustTagAccessSetType;
};

#endif // DUSTGENUNITMINDCORE_H_INCLUDED
