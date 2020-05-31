#ifndef DUSTGENUNITMINDDUST_H_INCLUDED
#define DUSTGENUNITMINDDUST_H_INCLUDED

#include <DustApi.h>

namespace DustUnitMindNative
{
extern DustToken DustUnitNative;

extern DustToken DustTypeModule;
extern DustToken DustRefModuleAgents;
extern DustToken DustRefModuleAlgorithms;

extern DustToken DustTypeConstant;
extern DustToken DustConstantNull;
extern DustToken DustConstantTrue;
extern DustToken DustConstantFalse;

extern DustToken DustTypeService;
extern DustToken DustTypeCommand;

extern DustToken DustServiceAction;
extern DustToken DustCommandActionExecute;
extern DustToken DustServiceResource;
extern DustToken DustCommandResourceInit;
extern DustToken DustCommandResourceRelease;
extern DustToken DustServiceLogic;

extern DustToken DustAgentCall;
extern DustToken DustRefAgentCallCommand;
extern DustToken DustRefAgentCallTarget;
extern DustToken DustRefAgentCallParam;
};

namespace DustUnitMindDust
{
extern DustToken DustUnitDust;
extern DustToken DustAgentRuntime;

extern DustToken DustAgentCore;
extern DustToken DustAgentPda;
extern DustToken DustAgentState;
}

#endif // DUSTGENUNITMINDDUST_H_INCLUDED
