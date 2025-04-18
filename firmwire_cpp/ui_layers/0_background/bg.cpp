#include "bg.h"
#include "../../global/global.h"

void init_bg() {
    for (int y = 0; y < screen_height; y++) {
        for (int x = 0; x < screen_width; x++) {
            int x_effective = x + global_x_offset;
            int y_effective = y + global_y_offset;
            display_buffer[y_effective][x_effective][BG_LAYER] = BG_COLOR;
        }
    }
}

void continue_bg() {}