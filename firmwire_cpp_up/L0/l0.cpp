#include "l0.h"
#include "../defs/constants.h"
#include "../master/master.h"
#include <iostream>
using namespace std;

void make_ui_Layer0() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            dispBuffLayer0[y][x] = BG_COLOR;
        }
    }
}