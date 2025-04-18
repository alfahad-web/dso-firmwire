#include <windows.h>
#include <vector>
#include <queue>
#include "ui_layers/0_background/bg.h"
#include "ui_layers/1_graphing/graphing.h"
#include "ui_layers/2_axis/axis.h"
#include "ui_layers/3_axis_annotations/axis_annotations.h"
#include "global/global.h"
#include <thread>
using namespace std;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            for (int y = 0; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                    int pixelValue = abs(display_buffer[y][x][5]);
                    int r = (pixelValue >> 16) & 0xFF;
                    int g = (pixelValue >> 8) & 0xFF;
                    int b = pixelValue & 0xFF;
                    SetPixel(hdc, x, y, RGB(r, g, b));
                }
            }

            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void init_display_buffer() {
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            for (int z = 0; z < 6; z++) {
                display_buffer[x][y][z] = 0;
            }
        }
    }
}

void synchronize_layers() {
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            for (int z = 1; z < 6; z++) {
                if(display_buffer[x][y][z] == 0) {
                    display_buffer[x][y][z] = -abs(display_buffer[x][y][z - 1]);
                }
            }
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int windowWidth = WIDTH + 100;
    int windowHeight = HEIGHT + 100;

    //this will not go here, here we will process just the request queue
    //every layer will have separate thread and will be processed in parallel
    //they all will request pixel update into the queue, and we will process it in this loop

    //initialize the display buffer
    {
        init_display_buffer();

        init_bg();
        init_graphing();
        init_axis();
        init_axis_annotations();
        // init_wave_reading();
        // init_annotations();

        synchronize_layers();
    }

    //start the parallel threads for every layer
    {
        std::thread backgroundThread(continue_bg);
        backgroundThread.detach();

        std::thread graphingThread(continue_graphing);
        graphingThread.detach();

        std::thread axisThread(continue_axis);
        axisThread.detach();

        std::thread axisAnnotationsThread(continue_axis_annotations);
        axisAnnotationsThread.detach();
    }

    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Sample Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
