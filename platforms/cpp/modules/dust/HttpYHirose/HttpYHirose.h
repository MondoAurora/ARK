#ifndef SRC_WINGUI_H_
#define SRC_WINGUI_H_

#include <DustKernel.h>

#include <dust/DustgenUnitHttp.h>

class AgentHttpGetter : public DustNativeLogic
{
    virtual DustResultType DustResourceInit();
    virtual DustResultType DustActionExecute();
};

class AgentHttpPoster : public DustNativeLogic
{
    virtual DustResultType DustResourceInit();
    virtual DustResultType DustActionExecute();
};

#endif /* SRC_WINGUI_H_ */
