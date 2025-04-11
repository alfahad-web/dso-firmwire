#include "bg.h"
#include "../../global/global.h"

#define BG_COLOR 0x222425
void init_background() {
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            display_buffer[x][y][BG_LAYER] = BG_COLOR;
        }
    }
}