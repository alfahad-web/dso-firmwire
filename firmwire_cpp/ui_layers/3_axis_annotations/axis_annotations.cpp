#include "axis_annotations.h"
#include "../../global/global.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

struct AxisAnnotations {
    int x_units;
    int y_units;
    int x_offset;
    int y_offset;
};

int rect_width = 6;
int rect_height = 2;

void print_rectangle(int x, int y, int color, int width, int height) {
    for(int i = -width / 2; i <= width / 2; i++) {
        for(int j = -height / 2; j <= height / 2; j++) {
            if (x + i >= 0 && x + i < HEIGHT && y + j >= 0 && y + j < WIDTH) {
                display_buffer[x + i][y + j][AXIS_ANNOTATIONS_LAYER] = color;
            }
        }
    }
}

void update_axis_annotations(AxisAnnotations axis_annotations) {
    int mid_y = WIDTH / 2 + axis_annotations.x_offset;
    int mid_x = HEIGHT / 2 + axis_annotations.y_offset;

    int interval_x = axis_annotations.x_units / 5;
    int interval_y = axis_annotations.y_units / 5;

    //instead of updating the display buffer, check if the pixel value has differed
    //if differed, then request pixel update in queue
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            if(x == mid_x && abs(y - mid_y) % interval_y == 0) {
                print_rectangle(x, y, AXIS_ANNOTATIONS_COLOR, rect_width, rect_height);
            } else if(y == mid_y && abs(x - mid_x) % interval_x == 0) {
                print_rectangle(x, y, AXIS_ANNOTATIONS_COLOR, rect_height, rect_width);
            }
        }
    }
}

void init_axis_annotations() {
    AxisAnnotations axis_annotations;
    axis_annotations.x_units = X_UNITS;
    axis_annotations.y_units = Y_UNITS;
    axis_annotations.x_offset = 0;
    axis_annotations.y_offset = 0;

    update_axis_annotations(axis_annotations);
}

void continue_axis_annotations() {}