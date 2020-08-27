#ifndef SRC_WINGUI_H_
#define SRC_WINGUI_H_

#include <DustKernel.h>

#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustgenUnitMindCore.h>

#include <windows.h>

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
