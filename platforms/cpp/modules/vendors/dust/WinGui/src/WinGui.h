#ifndef SRC_WINGUI_H_
#define SRC_WINGUI_H_

#include <DustKernel.h>

#include <vendors/dust/DustgenUnitTest01.h>

#include <windows.h>

class AgentWindow : public DustNativeLogic
{
public:
    virtual DustResultType DustActionExecute();
};

class WinGuiWindow : public DustNativeLogic
{
    HDC hDC;
    HWND hwnd;

public:

    virtual DustResultType DustResourceInit();
    virtual DustResultType DustActionExecute();
    virtual DustResultType DustResourceRelease();
};

#endif /* SRC_WINGUI_H_ */
