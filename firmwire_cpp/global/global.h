#ifndef GLOBAL_H
#define GLOBAL_H

#include <queue>

#define HEIGHT 480
#define WIDTH 854

#define BG_LAYER 0
#define GRAPHING_LAYER 1
#define AXIS_LAYER 2

#define BG_COLOR 0x222425
#define GRAPHING_COLOR 0x2d4d64
#define AXIS_COLOR 0xFFFFFF
#define AXIS_ANNOTATIONS_COLOR 0xFFFFFF

extern int display_buffer[HEIGHT][WIDTH][6];
extern std::queue<int> request_queue;

extern int X_UNITS;
extern int Y_UNITS;

#endif
