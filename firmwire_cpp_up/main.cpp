#include <windows.h>
#include <thread>
#include <vector>
#include <algorithm>
#include "master/master.h"
#include "defs/constants.h"
#include "defs/types.h"
#include <iostream>

using namespace std;

HWND g_hwnd = nullptr;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_UPDATE_PIXELS: {
            PixelUpdateArray* arr = reinterpret_cast<PixelUpdateArray*>(lParam);
            HDC hdc = GetDC(hwnd);
            for (int i = 0; i < arr->count; ++i) {
                SetPixel(hdc, arr->pixels[i].x, arr->pixels[i].y, arr->pixels[i].color);
            }
            ReleaseDC(hwnd, hdc);
            delete[] arr->pixels;
            delete arr;
            return 0;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    // AllocConsole();
    // freopen("CONOUT$", "w", stdout);
    // freopen("CONOUT$", "w", stderr);

    const char CLASS_NAME[] = "PixelWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    g_hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Dynamic Pixel Updater",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, WIDTH + 10, HEIGHT + 35,
        NULL, NULL, hInstance, NULL
    );

    if (!g_hwnd) return 0;
    ShowWindow(g_hwnd, nCmdShow);

    // start the master thread
    thread(master).detach();

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
