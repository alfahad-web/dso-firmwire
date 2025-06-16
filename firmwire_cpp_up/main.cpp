#include <windows.h>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

#define WIDTH 854
#define HEIGHT 480
#define WM_UPDATE_PIXELS (WM_USER + 1)

struct PixelUpdate {
    int x, y;
    COLORREF color;
};

struct PixelUpdateArray {
    PixelUpdate* pixels;
    int count;
};

HWND g_hwnd = nullptr;

// 👇 Call this function to update any number of pixels asynchronously
void updatePixels(const std::vector<PixelUpdate>& pixels) {
    // Launch a short-lived thread
    std::thread([pixels]() {
        PixelUpdateArray* arr = new PixelUpdateArray;
        arr->count = pixels.size();
        arr->pixels = new PixelUpdate[arr->count];
        std::copy(pixels.begin(), pixels.end(), arr->pixels);

        // Send message to main window to update
        PostMessage(g_hwnd, WM_UPDATE_PIXELS, 0, reinterpret_cast<LPARAM>(arr));
    }).detach();
}

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
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
        NULL, NULL, hInstance, NULL
    );

    if (!g_hwnd) return 0;
    ShowWindow(g_hwnd, nCmdShow);

    // 🔁 Example usage of dynamic pixel update
    std::thread([]() {
        for (int y = 0; y < HEIGHT; ++y) {
            std::vector<PixelUpdate> row;
            for (int x = 0; x < WIDTH; ++x) {
                row.push_back({ x, y, RGB(x % 256, y % 256, (x + y) % 256) });
            }
            updatePixels(row); // send one row at a time
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }).detach();

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
