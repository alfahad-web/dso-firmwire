#include "l1.h"
#include "../defs/constants.h"
#include "../graphics/graphics.h"
#include "../master/master.h"
#include <iostream>
using namespace std;

void print_graph() {}

void print_axis() {
    int mid_x = SCREEN_WIDTH / 2;
    int mid_y = SCREEN_HEIGHT / 2;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if(abs(y - mid_y) < LINE_WIDTH || abs(x - mid_x) < LINE_WIDTH) {
                safe_pixel_color(x, y, AXIS_COLOR, dispBuffLayer1);
            }
        }
    }
}

void print_axis_annotations() {
    int mid_x = SCREEN_WIDTH / 2;
    int mid_y = SCREEN_HEIGHT / 2;

    int interval_x = X_UNITS / 5;
    int interval_y = Y_UNITS / 5;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if(y == mid_y && abs(x - mid_x) % interval_y == 0) {
                safe_pixel_color(x, y, AXIS_ANNOTATIONS_COLOR, dispBuffLayer1);
            } else if(x == mid_x && abs(y - mid_y) % interval_x == 0) {
                safe_pixel_color(x, y, AXIS_ANNOTATIONS_COLOR, dispBuffLayer1);
            }
        }
    }
}

void print_border() {
    for(int y = 0; y < SCREEN_HEIGHT; y++) {
        for(int x = 0; x < SCREEN_WIDTH; x++) {
            // outline axis
            if(y < LINE_WIDTH || x < LINE_WIDTH || y >= SCREEN_HEIGHT - LINE_WIDTH || x >= SCREEN_WIDTH - LINE_WIDTH) {
                safe_pixel_color(x, y, AXIS_COLOR, dispBuffLayer1);
            }
        }
    }
}

void print_border_annotations() {}

void make_ui_Layer1() {
    print_graph();
    print_axis();
    print_axis_annotations();
    print_border();
    print_border_annotations();
}