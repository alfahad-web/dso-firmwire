#ifndef GLOBAL_H
#define GLOBAL_H

#include <queue>

#define HEIGHT 480
#define WIDTH 854

#define BG_LAYER 0
#define GRAPHING_LAYER 1
#define AXIS_LAYER 2
#define AXIS_ANNOTATIONS_LAYER 3
#define WAVE_READING_LAYER 4
#define ANNOTATIONS_LAYER 5

#define BG_COLOR 0x222425
#define GRAPHING_COLOR 0x2d4d64
#define AXIS_COLOR 0xFFFFFF
#define AXIS_ANNOTATIONS_COLOR 0xFFFFFF
#define WAVE_READING_COLOR_CH_A 0xDBDE64
#define WAVE_READING_COLOR_CH_B 0xA9E27F

#define X_UNITS 50
#define Y_UNITS 50

#define GLOBAL_X_MARGIN 20
#define GLOBAL_Y_MARGIN 40

extern int display_buffer[HEIGHT][WIDTH][6];
extern std::queue<int> request_queue;

extern int screen_width;
extern int screen_height;
extern int global_x_offset;
extern int global_y_offset;

#endif
