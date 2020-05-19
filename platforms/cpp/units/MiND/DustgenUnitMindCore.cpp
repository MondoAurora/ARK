
#include "DustgenUnitMindCore.h"

using namespace DustUnitMindModel;

DustToken DustUnitMindModel::DustUnitModel("Model");
DustToken DustUnitMindModel::DustTypeEntity(DustUnitModel, "Entity", DUST_IDEA_TYPE);
DustToken DustUnitMindModel::DustRefGlobalId(DustTypeEntity, "GlobalId", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindModel::DustRefOwner(DustTypeEntity, "Owner", DUST_VAL_REF, DUST_COLL_SINGLE);

DustToken DustUnitMindModel::DustTypeUnit(DustUnitModel, "Unit", DUST_IDEA_TYPE);

using namespace DustUnitMindIdea;

DustToken DustUnitMindIdea::DustUnitIdea("Idea");
DustToken DustUnitMindIdea::DustTypeType(DustUnitIdea, "Type", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustTypeMember(DustUnitIdea, "Member", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustTypeAgent(DustUnitIdea, "Agent", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustTypeConst(DustUnitIdea, "Const", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustTypeTag(DustUnitIdea, "Tag", DUST_IDEA_TYPE);

DustToken DustUnitMindIdea::DustConstValInteger(DustUnitIdea, "Integer", DUST_IDEA_CONST);
DustToken DustUnitMindIdea::DustConstValReal(DustUnitIdea, "Real", DUST_IDEA_CONST);
DustToken DustUnitMindIdea::DustConstValRef(DustUnitIdea, "Ref", DUST_IDEA_CONST);

DustToken DustUnitMindIdea::DustConstCollSet(DustUnitIdea, "Set", DUST_IDEA_CONST);
DustToken DustUnitMindIdea::DustConstCollArr(DustUnitIdea, "Arr", DUST_IDEA_CONST);
DustToken DustUnitMindIdea::DustConstCollMap(DustUnitIdea, "Map", DUST_IDEA_CONST);

using namespace DustUnitMindNarrative;
DustToken DustUnitMindNarrative::DustUnitNarrative("Narrative");

DustToken DustUnitMindNarrative::DustConstResultReject(DustUnitNarrative, "Reject", DUST_IDEA_CONST);
DustToken DustUnitMindNarrative::DustConstResultRead(DustUnitNarrative, "Read", DUST_IDEA_CONST);
DustToken DustUnitMindNarrative::DustConstResultAcceptPass(DustUnitNarrative, "AcceptPass", DUST_IDEA_CONST);
DustToken DustUnitMindNarrative::DustConstResultAccept(DustUnitNarrative, "Accept", DUST_IDEA_CONST);
DustToken DustUnitMindNarrative::DustConstResultAcceptRead(DustUnitNarrative, "AcceptRead", DUST_IDEA_CONST);

using namespace DustUnitMindDialog;
DustToken DustUnitMindDialog::DustUnitDialog("Dialog");

DustToken DustUnitMindDialog::DustConstAccessGet(DustUnitDialog, "Get", DUST_IDEA_CONST);
DustToken DustUnitMindDialog::DustConstAccessSet(DustUnitDialog, "Set", DUST_IDEA_CONST);
DustToken DustUnitMindDialog::DustConstAccessMove(DustUnitDialog, "Move", DUST_IDEA_CONST);
DustToken DustUnitMindDialog::DustConstAccessRemove(DustUnitDialog, "Remove", DUST_IDEA_CONST);
DustToken DustUnitMindDialog::DustConstAccessClear(DustUnitDialog, "Clear", DUST_IDEA_CONST);

