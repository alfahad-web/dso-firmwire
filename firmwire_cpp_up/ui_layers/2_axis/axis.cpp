#include "axis.h"
#include "../../global/global.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Axis {
    int x_units;
    int y_units;
    int line_width;
};

void update_axis(Axis axis) {
    int mid_x = screen_width / 2 + global_x_offset;
    int mid_y = screen_height / 2 + global_y_offset;

    //instead of updating the display buffer, check if the pixel value has differed
    //if differed, then request pixel update in queue
    for (int y = 0; y < screen_height; y++) {
        for (int x = 0; x < screen_width; x++) {
            int x_effective = x + global_x_offset;
            int y_effective = y + global_y_offset;
            if(abs(y_effective - mid_y) < axis.line_width || abs(x_effective - mid_x) < axis.line_width) {
                display_buffer[y_effective][x_effective][AXIS_LAYER] = AXIS_COLOR;
            }
        }
    }
}

void init_axis() {
    Axis axis;
    axis.x_units = X_UNITS;
    axis.y_units = Y_UNITS;
    axis.line_width = LINE_WIDTH;

    update_axis(axis);
}

void continue_axis() {}