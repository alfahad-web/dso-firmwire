#include "annotations.h"
#include "../../global/global.h"
#include <stdlib.h>
#include <iostream>
#include <map>
#include "../../graphics/graphics.h"
using namespace std;

#define LOGO_COLOR 0x2596be

struct Annotations {
    string stop_run_mode;
    string trigger_mode;
    int sample_rate;
    string sample_rate_units;
    int captured_sample_cnt; // in MSa

    string ch_A_coupling;
    int ch_A_volt_per_div;
    string ch_A_volt_per_div_units;
    int ch_A_time_per_div;
    string ch_A_time_per_div_units;
    int ch_A_ground_level; // pixel cnt from bottom of the screen

    string ch_B_coupling;
    int ch_B_volt_per_div;
    string ch_B_volt_per_div_units;
    int ch_B_time_per_div;
    string ch_B_time_per_div_units;
    int ch_B_ground_level; // pixel cnt from bottom of the screen

};

map<string, string> stop_run_mode_map = {
    {"STOP", "STOP"},
    {"RUN", "RUN"}
};

map<string, string> trigger_mode_map = {
    {"AUTO", "AUTO"},
    {"RISING", "RISING"},
    {"FALLING", "FALLING"}
};

map<string, string> ch_coupling_map = {
    {"DC", "DC"},
    {"AC", "AC"}
};

map<string, string> ch_volt_per_div_units_map = {
    {"V", "V"},
    {"mV", "mV"},
    {"μV", "μV"}
};

map<string, string> ch_time_per_div_units_map = {
    {"s", "s"},
    {"ms", "ms"},
    {"μs", "μs"},
    {"ns", "ns"}
};

map<string, string> sample_rate_units_map = {
    {"MSa", "MSa"},
    {"KSa", "KSa"}
};

void print_outline() {
    for(int y = 0; y < screen_height; y++) {
        for(int x = 0; x < screen_width; x++) {
            int x_effective = x + global_x_offset;
            int y_effective = y + global_y_offset;
            if(y < LINE_WIDTH || x < LINE_WIDTH || y >= screen_height - LINE_WIDTH || x >= screen_width - LINE_WIDTH) {
                display_buffer[y_effective - 1][x_effective - 1][ANNOTATIONS_LAYER] = AXIS_COLOR;
                display_buffer[y_effective + 1][x_effective + 1][ANNOTATIONS_LAYER] = AXIS_COLOR;
            }
        }
    }
}

void update_annotations(Annotations annotations) {
    // logo
    // print_rounded_rectangle_bottom_left(GLOBAL_Y_MARGIN - 8, GLOBAL_X_MARGIN, LOGO_COLOR, 120, GLOBAL_Y_MARGIN - 12, 2, ANNOTATIONS_LAYER);

    // graph outline
    print_outline();

    // pointer for chA
    print_pointer(2, HEIGHT / 2 - 5, WAVE_READING_COLOR_CH_A, ANNOTATIONS_LAYER);
    // pointer for chB
    print_pointer(2, HEIGHT / 2 - 5, WAVE_READING_COLOR_CH_B, ANNOTATIONS_LAYER);
}

void init_annotations() {
    Annotations annotations;
    annotations.stop_run_mode = stop_run_mode_map["STOP"];
    annotations.trigger_mode = trigger_mode_map["AUTO"];
    annotations.sample_rate = 10;
    annotations.sample_rate_units = sample_rate_units_map["MSa"];
    annotations.captured_sample_cnt = 10;

    annotations.ch_A_coupling = ch_coupling_map["DC"];
    annotations.ch_A_volt_per_div = 1;
    annotations.ch_A_volt_per_div_units = ch_volt_per_div_units_map["V"];
    annotations.ch_A_time_per_div = 50;
    annotations.ch_A_time_per_div_units = ch_time_per_div_units_map["ns"];
    annotations.ch_A_ground_level = HEIGHT / 2;

    annotations.ch_B_coupling = ch_coupling_map["DC"];
    annotations.ch_B_volt_per_div = 1;
    annotations.ch_B_volt_per_div_units = ch_volt_per_div_units_map["V"];
    annotations.ch_B_time_per_div = 50;
    annotations.ch_B_time_per_div_units = ch_time_per_div_units_map["ns"];
    annotations.ch_B_ground_level = HEIGHT / 2;

    update_annotations(annotations);
}

void continue_annotations() {}