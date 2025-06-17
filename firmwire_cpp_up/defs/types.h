#ifndef TYPES_H
#define TYPES_H

#include <windows.h>
#define ll long long int

struct PixelUpdate {
    int x;
    int y;
    ll color;
};

struct PixelUpdateArray {
    PixelUpdate* pixels;
    int count;
};

extern HWND g_hwnd;

#endif