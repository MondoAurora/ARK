
#include "DustgenUnitMindCore.h"

using namespace DustUnitMindModel;

DustToken DustUnitMindModel::DustUnitModel("Model");
DustToken DustUnitMindModel::DustTypeEntity(DustUnitModel, "Entity", DUST_IDEA_TYPE);
DustToken DustUnitMindModel::DustRefUnit(DustTypeEntity, "Unit", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindModel::DustIntId(DustTypeEntity, "Id", DUST_VAL_INTEGER, DUST_COLL_SINGLE);
DustToken DustUnitMindModel::DustRefPrimaryType(DustTypeEntity, "PrimaryType", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindModel::DustRefGlobalId(DustTypeEntity, "GlobalId", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindModel::DustRefOwner(DustTypeEntity, "Owner", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindModel::DustRefTags(DustTypeEntity, "Tags", DUST_VAL_REF, DUST_COLL_SET);

DustToken DustUnitMindModel::DustTypeUnit(DustUnitModel, "Unit", DUST_IDEA_TYPE);

using namespace DustUnitMindIdea;

DustToken DustUnitMindIdea::DustUnitIdea("Idea");
DustToken DustUnitMindIdea::DustTypeType(DustUnitIdea, "Type", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustTypeMember(DustUnitIdea, "Member", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustTypeAgent(DustUnitIdea, "Agent", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustTypeTag(DustUnitIdea, "Tag", DUST_IDEA_TYPE);

DustToken DustUnitMindIdea::DustConstValInteger(DustUnitIdea, "Integer", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustConstValReal(DustUnitIdea, "Real", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustConstValRef(DustUnitIdea, "Ref", DUST_IDEA_TAG);

DustToken DustUnitMindIdea::DustConstCollSingle(DustUnitIdea, "Single", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustConstCollSet(DustUnitIdea, "Set", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustConstCollArr(DustUnitIdea, "Arr", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustConstCollMap(DustUnitIdea, "Map", DUST_IDEA_TAG);

using namespace DustUnitMindNarrative;
DustToken DustUnitMindNarrative::DustUnitNarrative("Narrative");

DustToken DustUnitMindNarrative::DustConstResultReject(DustUnitNarrative, "Reject", DUST_IDEA_TAG);
DustToken DustUnitMindNarrative::DustConstResultRead(DustUnitNarrative, "Read", DUST_IDEA_TAG);
DustToken DustUnitMindNarrative::DustConstResultAcceptPass(DustUnitNarrative, "AcceptPass", DUST_IDEA_TAG);
DustToken DustUnitMindNarrative::DustConstResultAccept(DustUnitNarrative, "Accept", DUST_IDEA_TAG);
DustToken DustUnitMindNarrative::DustConstResultAcceptRead(DustUnitNarrative, "AcceptRead", DUST_IDEA_TAG);

using namespace DustUnitMindDialog;
DustToken DustUnitMindDialog::DustUnitDialog("Dialog");

DustToken DustUnitMindDialog::DustConstAccessGet(DustUnitDialog, "Get", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustConstAccessSet(DustUnitDialog, "Set", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustConstAccessMove(DustUnitDialog, "Move", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustConstAccessRemove(DustUnitDialog, "Remove", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustConstAccessClear(DustUnitDialog, "Clear", DUST_IDEA_TAG);

