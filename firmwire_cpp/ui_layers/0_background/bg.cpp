#include "bg.h"
#include "../../global/global.h"

void init_bg() {
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            display_buffer[x][y][BG_LAYER] = BG_COLOR;
        }
    }
}

void continue_bg() {}