#include <iostream>
#include <string>

#include "WinGui.h"

#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustgenUnitMindCore.h>
#include <vendors/dust/DustgenUnitTest01.h>


using namespace std;
using namespace DustUnitDustTest01;

LRESULT CALLBACK WinGuiWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

DustResultType WinGuiWindow::DustResourceInit()
{
    HINSTANCE hInstance = GetModuleHandle(0);
    WNDCLASSEX wcex;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WinGuiWindowProc;
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
        return DUST_RESULT_REJECT;

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

    ShowWindow(hwnd, SW_SHOWDEFAULT);

    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    hDC = GetDC(hwnd);

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

    iFormat = ChoosePixelFormat(hDC, &pfd);

    SetPixelFormat(hDC, iFormat, &pfd);

    DustRef dlg(DUST_CTX_DIALOG);
    DustData::setInteger(dlg, DustIntHDC, (long) hDC);

    return DUST_RESULT_ACCEPT;
}

DustResultType WinGuiWindow::DustActionExecute()
{
    MSG msg;
    DustRef dlg(DUST_CTX_DIALOG);

    if (!DustData::getInteger(dlg, DustIntHDC, 0))
    {
        return DUST_RESULT_ACCEPT;
    }

    if (DustData::getInteger(dlg, DustIntBufferChanged, 0))
    {
        SwapBuffers(hDC);
        DustData::setInteger(dlg, DustIntBufferChanged, 0);
    }

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
                DustData::setInteger(dlg, DustIntHDC, 0);
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return DUST_RESULT_ACCEPT_PASS;
}

DustResultType WinGuiWindow::DustResourceRelease()
{
    if ( hDC )
    {
        ReleaseDC(hwnd, hDC);
        DestroyWindow(hwnd);
        hDC = 0;
    }

    return DUST_RESULT_ACCEPT;
}
