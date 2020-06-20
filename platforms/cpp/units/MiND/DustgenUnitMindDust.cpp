
#include "DustgenUnitMindDust.h"

using namespace DustUnitMindNative;

DustToken DustUnitMindNative::DustUnitNative("Native");

DustToken DustUnitMindNative::DustTypeModule(DustUnitNative, "Module", DUST_IDEA_TYPE);
DustToken DustUnitMindNative::DustRefModuleAgents(DustTypeModule, "Agents", DUST_VAL_REF, DUST_COLL_SET);
DustToken DustUnitMindNative::DustRefModuleAlgorithms(DustTypeModule, "Algorithms", DUST_VAL_REF, DUST_COLL_SET);

DustToken DustUnitMindNative::DustTypeService(DustUnitNative, "Service", DUST_IDEA_TYPE);
DustToken DustUnitMindNative::DustTypeCommand(DustUnitNative, "Command", DUST_IDEA_TYPE);

DustToken DustUnitMindNative::DustServiceAction(DustUnitNative, "Action", DUST_NATIVE_SERVICE);
DustToken DustUnitMindNative::DustCommandActionExecute(DustServiceAction, "Execute", DUST_NATIVE_COMMAND);
DustToken DustUnitMindNative::DustServiceResource(DustUnitNative, "Resource", DUST_NATIVE_SERVICE);
DustToken DustUnitMindNative::DustCommandResourceInit(DustServiceResource, "Init", DUST_NATIVE_COMMAND);
DustToken DustUnitMindNative::DustCommandResourceRelease(DustServiceResource, "Release", DUST_NATIVE_COMMAND);
DustToken DustUnitMindNative::DustServiceLogic(DustUnitNative, "Logic", DUST_NATIVE_SERVICE);

DustToken DustUnitMindNative::DustAgentCall(DustUnitNative, "Call", DUST_IDEA_AGENT);
DustToken DustUnitMindNative::DustRefAgentCallCommand(DustAgentCall, "Command", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindNative::DustRefAgentCallTarget(DustAgentCall, "Target", DUST_VAL_REF, DUST_COLL_SINGLE);
DustToken DustUnitMindNative::DustRefAgentCallParam(DustAgentCall, "Param", DUST_VAL_REF, DUST_COLL_SINGLE);


using namespace DustUnitMindDust;

DustToken DustUnitMindDust::DustUnitDust("Dust");

DustToken DustUnitMindDust::DustAgentRuntime(DustUnitDust, "Runtime", DUST_IDEA_AGENT);
DustToken DustUnitMindDust::DustRefRuntimeApps(DustAgentRuntime, "Apps", DUST_VAL_REF, DUST_COLL_SET);
DustToken DustUnitMindDust::DustRefRuntimeThreads(DustAgentRuntime, "Threads", DUST_VAL_REF, DUST_COLL_SET);

DustToken DustUnitMindDust::DustAgentThread(DustUnitDust, "Thread", DUST_IDEA_AGENT);
DustToken DustUnitMindDust::DustAgentState(DustUnitDust, "State", DUST_IDEA_AGENT);
