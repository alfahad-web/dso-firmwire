#include "ui_elem.h"
#include "../global/global.h"

void print_outline() {
    for(int y = 0; y < screen_height; y++) {
        for(int x = 0; x < screen_width; x++) {
            int x_effective = x + global_x_offset;
            int y_effective = y + global_y_offset;
            // outline axis
            if(y < LINE_WIDTH || x < LINE_WIDTH || y >= screen_height - LINE_WIDTH || x >= screen_width - LINE_WIDTH) {
                display_buffer[y_effective - 1][x_effective - 1][ANNOTATIONS_LAYER] = AXIS_COLOR;
                display_buffer[y_effective + 1][x_effective + 1][ANNOTATIONS_LAYER] = AXIS_COLOR;
            }
        }
    }
}