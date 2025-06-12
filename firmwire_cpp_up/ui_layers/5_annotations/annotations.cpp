#include "annotations.h"
#include "../../global/global.h"
#include <stdlib.h>
#include <iostream>
#include <map>
#include "../../graphics/graphics.h"
#include "../../ui_elements/ui_elem.h"
using namespace std;

#define LOGO_COLOR 0x2596be
#define STOP_RUN_MODE_FILL 0xf8765a
#define STOP_RUN_MODE_STROKE DEFAULT_BG_COLOR
#define TRIGGER_MODE_FILL 0x5a98f8
#define TRIGGER_MODE_STROKE DEFAULT_BG_COLOR

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

    string ch_B_coupling;
    int ch_B_volt_per_div;
    string ch_B_volt_per_div_units;
    int ch_B_time_per_div;
    string ch_B_time_per_div_units;

    int ch_A_ground_level; // pixel cnt from bottom of the screen
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

void update_annotations(Annotations annotations) {
    // // logo
    // int logo_width = 120, logo_height = GLOBAL_Y_MARGIN - 16;
    // print_rounded_rectangle_bottom_left(GLOBAL_Y_MARGIN - 8, GLOBAL_X_MARGIN, LOGO_COLOR, logo_width, logo_height, 2, ANNOTATIONS_LAYER);
    
    // // stop_run_mode
    // vector<int> font_spacing_stop_run_mode = {11, 11, 14};
    // int stop_run_mode_width = 60, stop_run_mode_height = GLOBAL_Y_MARGIN - 20;
    // print_rounded_rectangle_bottom_left(GLOBAL_Y_MARGIN - 8, GLOBAL_X_MARGIN + logo_width + 10, STOP_RUN_MODE_FILL, stop_run_mode_width, stop_run_mode_height, 2, ANNOTATIONS_LAYER);
    // int stop_run_mode_text_x_offset = 7;
    // int stop_run_mode_text_y_offset = 8;
    // int stop_run_mode_text_x = GLOBAL_X_MARGIN + logo_width + 10 + stop_run_mode_text_x_offset;
    // int stop_run_mode_text_y = GLOBAL_Y_MARGIN - 8 - stop_run_mode_height + stop_run_mode_text_y_offset;
    // print_text(stop_run_mode_text_x, stop_run_mode_text_y, "STOP", 20, font_spacing_stop_run_mode, STOP_RUN_MODE_STROKE, ANNOTATIONS_LAYER);
    
    // // trigger_mode
    // vector<int> font_spacing_trigger_mode = {13, 11, 11};
    // int trigger_mode_width = 60, trigger_mode_height = GLOBAL_Y_MARGIN - 20;
    // print_rounded_rectangle_bottom_left(GLOBAL_Y_MARGIN - 8, GLOBAL_X_MARGIN + logo_width + stop_run_mode_width + 10 + 5, TRIGGER_MODE_FILL, trigger_mode_width, trigger_mode_height, 2, ANNOTATIONS_LAYER);
    // int trigger_mode_text_x_offset = 7;
    // int trigger_mode_text_y_offset = 8;
    // int trigger_mode_text_x = GLOBAL_X_MARGIN + logo_width + stop_run_mode_width + 10 + trigger_mode_text_x_offset;
    // int trigger_mode_text_y = GLOBAL_Y_MARGIN - 8 - trigger_mode_height + trigger_mode_text_y_offset;
    // print_text(trigger_mode_text_x, trigger_mode_text_y, "AUTO", 20, font_spacing_trigger_mode, TRIGGER_MODE_STROKE, ANNOTATIONS_LAYER);

    // // sample_rate
    // // sample_rate_units
    // // captured_sample_cnt

    // graph outline
    print_outline();

    // // pointer for chA
    // print_pointer(2, annotations.ch_A_ground_level, WAVE_READING_COLOR_CH_A, ANNOTATIONS_LAYER);
    // // pointer for chB
    // print_pointer(2, annotations.ch_B_ground_level, WAVE_READING_COLOR_CH_B, ANNOTATIONS_LAYER);

    // print text
    // vector<int> font_spacing_x = {14, 12, 12, 12};
    // print_text(10, 10, "ABCD", 20, font_spacing_x, 0xFFFFFF, ANNOTATIONS_LAYER);
    // int x_now = 10;
    // for(int i = 0; i < 4; i++) {
    //     print_dot(10, x_now, 0xFFFFFF, 2, ANNOTATIONS_LAYER);
    //     x_now += font_spacing_x[i];
    // }
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
    annotations.ch_A_ground_level = HEIGHT / 2 - 5;

    annotations.ch_B_coupling = ch_coupling_map["DC"];
    annotations.ch_B_volt_per_div = 1;
    annotations.ch_B_volt_per_div_units = ch_volt_per_div_units_map["V"];
    annotations.ch_B_time_per_div = 50;
    annotations.ch_B_time_per_div_units = ch_time_per_div_units_map["ns"];
    annotations.ch_B_ground_level = HEIGHT / 2 - 5;

    update_annotations(annotations);
}

void continue_annotations() {}