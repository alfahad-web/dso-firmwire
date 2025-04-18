#include "axis.h"
#include "../../global/global.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Axis {
    int x_units;
    int y_units;
    int x_offset;
    int y_offset;
    int line_width;
};

void update_axis(Axis axis) {
    int mid_y = WIDTH / 2 + axis.x_offset;
    int mid_x = HEIGHT / 2 + axis.y_offset;

    //instead of updating the display buffer, check if the pixel value has differed
    //if differed, then request pixel update in queue
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            if(abs(x - mid_x) < axis.line_width || abs(y - mid_y) < axis.line_width) {
                display_buffer[x][y][AXIS_LAYER] = AXIS_COLOR;
            } else {
                display_buffer[x][y][AXIS_LAYER] = 0;
            }
        }
    }
}

void init_axis() {
    Axis axis;
    axis.x_units = X_UNITS;
    axis.y_units = Y_UNITS;
    axis.x_offset = 0;
    axis.y_offset = 0;
    axis.line_width = 2;

    update_axis(axis);
}

void continue_axis() {}