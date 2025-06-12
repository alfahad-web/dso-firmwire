#include "global.h"

int display_buffer[HEIGHT][WIDTH][6];
std::queue<int> request_queue;

int screen_width = WIDTH - GLOBAL_X_MARGIN * 2;
int screen_height = HEIGHT - GLOBAL_Y_MARGIN * 2;

int global_x_offset = GLOBAL_X_MARGIN;
int global_y_offset = GLOBAL_Y_MARGIN;