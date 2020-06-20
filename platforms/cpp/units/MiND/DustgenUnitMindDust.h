#ifndef DUSTGENUNITMINDDUST_H_INCLUDED
#define DUSTGENUNITMINDDUST_H_INCLUDED

#include <DustApi.h>

namespace DustUnitMindNative
{
extern DustToken DustUnitNative;

extern DustToken DustTypeModule;
extern DustToken DustRefModuleAgents;
extern DustToken DustRefModuleAlgorithms;

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
extern DustToken DustAgentThread;
extern DustToken DustAgentState;

extern DustToken DustRefRuntimeApps;
extern DustToken DustRefRuntimeThreads;
}

#endif // DUSTGENUNITMINDDUST_H_INCLUDED
