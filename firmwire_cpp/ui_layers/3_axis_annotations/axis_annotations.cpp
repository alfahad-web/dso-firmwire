#include "axis_annotations.h"
#include "../../global/global.h"
#include "../../graphics/graphics.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

struct AxisAnnotations {
    int x_units;
    int y_units;
};

int rect_width = AXIS_ANNOTATIONS_WIDTH;
int rect_height = AXIS_ANNOTATIONS_HEIGHT;

void update_axis_annotations(AxisAnnotations axis_annotations) {
    int mid_x = screen_width / 2 + global_x_offset;
    int mid_y = screen_height / 2 + global_y_offset;

    int interval_x = axis_annotations.x_units / 5;
    int interval_y = axis_annotations.y_units / 5;

    //instead of updating the display buffer, check if the pixel value has differed
    //if differed, then request pixel update in queue
    for (int y = 0; y < screen_height; y++) {
        for (int x = 0; x < screen_width; x++) {
            int y_effective = y + global_y_offset;
            int x_effective = x + global_x_offset;
            if(y_effective == mid_y && abs(x_effective - mid_x) % interval_y == 0) {
                print_rectangle(y_effective, x_effective, AXIS_ANNOTATIONS_COLOR, rect_height, rect_width, AXIS_ANNOTATIONS_LAYER);
            } else if(x_effective == mid_x && abs(y_effective - mid_y) % interval_x == 0) {
                print_rectangle(y_effective, x_effective, AXIS_ANNOTATIONS_COLOR, rect_width, rect_height, AXIS_ANNOTATIONS_LAYER);
            }
            // graph outline
            // if(y_effective == 0 && x_effective % interval_y == 0) {
            //     print_rectangle(y_effective, x_effective, AXIS_ANNOTATIONS_COLOR, rect_height, rect_width, AXIS_ANNOTATIONS_LAYER);
            // } 
            // else if(x_effective == mid_x && abs(y_effective - mid_y) % interval_x == 0) {
            //     print_rectangle(y_effective, x_effective, AXIS_ANNOTATIONS_COLOR, rect_width, rect_height, AXIS_ANNOTATIONS_LAYER);
            // }
        }
    }
}

void init_axis_annotations() {
    AxisAnnotations axis_annotations;
    axis_annotations.x_units = X_UNITS;
    axis_annotations.y_units = Y_UNITS;

    update_axis_annotations(axis_annotations);
}

void continue_axis_annotations() {}