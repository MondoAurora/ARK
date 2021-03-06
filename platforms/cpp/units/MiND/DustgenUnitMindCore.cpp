
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

DustToken DustUnitMindModel::DustTypeValue(DustUnitModel, "Value", DUST_IDEA_TYPE);
DustToken DustUnitMindModel::DustIntValueKey(DustTypeValue, "Key", DUST_VAL_INTEGER, DUST_COLL_SINGLE);
DustToken DustUnitMindModel::DustIntValue(DustTypeValue, "Int", DUST_VAL_INTEGER, DUST_COLL_SINGLE);
DustToken DustUnitMindModel::DustRealValue(DustTypeValue, "Real", DUST_VAL_REAL, DUST_COLL_SINGLE);
DustToken DustUnitMindModel::DustRefValue(DustTypeValue, "Ref", DUST_VAL_REF, DUST_COLL_SINGLE);

DustToken DustUnitMindModel::DustTypeUnit(DustUnitModel, "Unit", DUST_IDEA_TYPE);
DustToken DustUnitMindModel::DustTypeSystem(DustUnitModel, "System", DUST_IDEA_TYPE);

using namespace DustUnitMindIdea;

DustToken DustUnitMindIdea::DustUnitIdea("Idea");
DustToken DustUnitMindIdea::DustTypeType(DustUnitIdea, "Type", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustTypeMember(DustUnitIdea, "Member", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustTypeAgent(DustUnitIdea, "Agent", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustTypeTag(DustUnitIdea, "Tag", DUST_IDEA_TYPE);

DustToken DustUnitMindIdea::DustTypeConstant(DustUnitIdea, "Constant", DUST_IDEA_TYPE);
DustToken DustUnitMindIdea::DustConstantNull(DustUnitIdea, "Null", DUST_IDEA_CONSTANT);
DustToken DustUnitMindIdea::DustConstantTrue(DustUnitIdea, "True", DUST_IDEA_CONSTANT);
DustToken DustUnitMindIdea::DustConstantFalse(DustUnitIdea, "False", DUST_IDEA_CONSTANT);

DustToken DustUnitMindIdea::DustTagVal(DustUnitIdea, "ValueType", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustTagValInteger(DustTagVal, "Integer", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustTagValReal(DustTagVal, "Real", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustTagValRef(DustTagVal, "Ref", DUST_IDEA_TAG);

DustToken DustUnitMindIdea::DustTagColl(DustUnitIdea, "CollectionType", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustTagCollSingle(DustTagColl, "Single", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustTagCollSet(DustTagColl, "Set", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustTagCollArr(DustTagColl, "Arr", DUST_IDEA_TAG);
DustToken DustUnitMindIdea::DustTagCollMap(DustTagColl, "Map", DUST_IDEA_TAG);

using namespace DustUnitMindNarrative;
DustToken DustUnitMindNarrative::DustUnitNarrative("Narrative");

DustToken DustUnitMindNarrative::DustTagResult(DustUnitNarrative, "ResultType", DUST_IDEA_TAG);
DustToken DustUnitMindNarrative::DustTagResultReject(DustTagResult, "Reject", DUST_IDEA_TAG);
DustToken DustUnitMindNarrative::DustTagResultRead(DustTagResult, "Read", DUST_IDEA_TAG);
DustToken DustUnitMindNarrative::DustTagResultAcceptPass(DustTagResult, "AcceptPass", DUST_IDEA_TAG);
DustToken DustUnitMindNarrative::DustTagResultAccept(DustTagResult, "Accept", DUST_IDEA_TAG);
DustToken DustUnitMindNarrative::DustTagResultAcceptRead(DustTagResult, "AcceptRead", DUST_IDEA_TAG);

DustToken DustUnitMindNarrative::DustAgentSequence(DustUnitNarrative, "Sequence", DUST_IDEA_AGENT);
DustToken DustUnitMindNarrative::DustAgentRepeat(DustUnitNarrative, "Repeat", DUST_IDEA_AGENT);
DustToken DustUnitMindNarrative::DustAgentSelect(DustUnitNarrative, "Select", DUST_IDEA_AGENT);

using namespace DustUnitMindDialog;
DustToken DustUnitMindDialog::DustUnitDialog("Dialog");

DustToken DustUnitMindDialog::DustTagCtx(DustUnitDialog, "Ctx", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagCtxSelf(DustTagCtx, "Self", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagCtxDialog(DustTagCtx, "Dialog", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagCtxApp(DustTagCtx, "App", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagCtxSystem(DustTagCtx, "System", DUST_IDEA_TAG);

DustToken DustUnitMindDialog::DustAgentDialog(DustUnitDialog, "Dialog", DUST_IDEA_AGENT);
DustToken DustUnitMindDialog::DustAgentApp(DustUnitDialog, "App", DUST_IDEA_AGENT);

DustToken DustUnitMindDialog::DustRefAppSystem(DustAgentApp, "System", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindDialog::DustRefAppMain(DustAgentApp, "Main", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindDialog::DustRefAppDialogs(DustAgentApp, "Dialogs", DUST_VAL_REF, DUST_COLL_SET);

DustToken DustUnitMindDialog::DustTagAccess(DustUnitDialog, "AccessType", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagAccessGet(DustTagAccess, "Get", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagAccessSet(DustTagAccess, "Set", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagAccessMove(DustTagAccess, "Move", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagAccessRemove(DustTagAccess, "Remove", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagAccessClear(DustTagAccess, "Clear", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagAccessCreate(DustTagAccess, "Create", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagAccessDelete(DustTagAccess, "Delete", DUST_IDEA_TAG);
DustToken DustUnitMindDialog::DustTagAccessSetType(DustTagAccess, "SetType", DUST_IDEA_TAG);
