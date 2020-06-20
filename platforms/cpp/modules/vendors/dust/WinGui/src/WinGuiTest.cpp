#include <iostream>
#include <string>

#include "WinGui.h"

#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustgenUnitMindCore.h>
#include <vendors/dust/DustgenUnitTest01.h>

#include <windows.h>

using namespace std;
using namespace DustUnitDustTest01;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void MyInitWindow(HWND hwnd, HDC*);
void MyReleaseWindow(HWND, HDC);

HDC hDC;

void updateGraphics(BOOL bQuit)
{
    DustRef self;

    DustData::setInteger(self, DustIntHDC, bQuit ? 0 : (long) hDC);

//    DustEntity painter = DustData::getRef(self, DustRefPainter);
//    DustNativeLogic *pl = (DustNativeLogic*) DustData::getNative(painter);
    DustNativeLogic *pl = (DustNativeLogic*) DustData::getNative(self, DustAgentTestOpenGL);

    if ( pl )
    {
        if ( DUST_RESULT_REJECT != pl->DustActionExecute() )
        {
            SwapBuffers(hDC);
        }
    }

    Sleep (0.1f);
}

int WINAPI sw()
{
    HINSTANCE hInstance = GetModuleHandle(0);
    WNDCLASSEX wcex;
    HWND hwnd;
    MSG msg;
    BOOL bQuit = FALSE;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "FleetMan",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          256,
                          256,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    MyInitWindow(hwnd, &hDC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        updateGraphics(bQuit);
    }

    MyReleaseWindow(hwnd, hDC);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
    }
    break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void MyInitWindow(HWND hwnd, HDC* hDC)
{
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);
}

void MyReleaseWindow (HWND hwnd, HDC hDC)
{
    ReleaseDC(hwnd, hDC);
    DestroyWindow(hwnd);
}

DustResultType AgentWindow::DustActionExecute()
{
    sw();
    return DUST_RESULT_ACCEPT;
}
