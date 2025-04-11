#ifndef GLOBAL_H
#define GLOBAL_H

#include <queue>

#define HEIGHT 480
#define WIDTH 854

#define BG_LAYER 0

extern int display_buffer[HEIGHT][WIDTH][6];
extern std::queue<int> request_queue;

#endif
