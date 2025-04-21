#include "wave_reading.h"
#include "../../global/global.h"
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "../1_graphing/graphing.h"
#include "../../graphics/graphics.h"
using namespace std;

#define M_PI 3.14159265358979323846

struct Wave {
    vector<int> wave_data_chA; // the wave data in mV vs time in ns
    vector<int> wave_data_chB; // the wave data in mV vs time in ns
    int wave_time_unit; // time unit that the wave data is measured in (ns), suppose 2 ns means the samples are taken after each 2 ns
    int wave_volt_unit; // the voltage unit that the wave data is measured in (mV), suppose 1 mV means the samples are measured in mV
};

struct WaveReading {
    Wave wave;
    int display_time_unit_chA; // time unit in ns, the time interval of 5 minimum points or the smallest rectangle width
    int display_y_unit_chA; // voltage unit in mV, the voltage interval of 5 minimum points or the smallest rectangle height
    int display_time_unit_chB; // time unit in ns, the time interval of 5 minimum points or the smallest rectangle width
    int display_y_unit_chB; // voltage unit in mV, the voltage interval of 5 minimum points or the smallest rectangle height
    int y_offset_chA;
    int y_offset_chB;
    int line_thickness;
    int initial_position_chA; // the index of wave_data that the display now starts from
    int initial_position_chB; // the index of wave_data that the display now starts from
};

void update_wave_reading(WaveReading wave_reading) {
    int time_interval_per_pixel_chA = wave_reading.display_time_unit_chA / X_UNITS; // in ns
    int voltage_interval_per_pixel_chA = wave_reading.display_y_unit_chA / Y_UNITS; // in mV

    int time_interval_per_pixel_chB = wave_reading.display_time_unit_chB / X_UNITS; // in ns
    int voltage_interval_per_pixel_chB = wave_reading.display_y_unit_chB / Y_UNITS; // in mV

    int mid_y_chA = screen_height / 2 + wave_reading.y_offset_chA + global_y_offset;
    int mid_y_chB = screen_height / 2 + wave_reading.y_offset_chB + global_y_offset;

    // Instead of updating the display buffer, check if the pixel value has differed
    // If differed, then request pixel update in queue
    // Wave Reading for chA
    for (int x = 0; x < screen_width; x++) {
        int x_effective = x + global_x_offset;
        int y_val_chA = 0;
        for (int i = 0; i < time_interval_per_pixel_chA; i++) {
            int index = wave_reading.initial_position_chA + x * time_interval_per_pixel_chA + i;
            if (index < wave_reading.wave.wave_data_chA.size()) {
                y_val_chA += wave_reading.wave.wave_data_chA[index];
            }
        }
        y_val_chA /= time_interval_per_pixel_chA;
        int y_pixel_height_chA = y_val_chA / voltage_interval_per_pixel_chA + mid_y_chA; // height from base for this pixel
        print_dot(y_pixel_height_chA, x_effective, WAVE_READING_COLOR_CH_A, wave_reading.line_thickness, WAVE_READING_LAYER);
    }
    // Wave Reading for chB
    for (int x = 0; x < screen_width; x++) {
        int x_effective = x + global_x_offset;
        int y_val_chB = 0;
        for (int i = 0; i < time_interval_per_pixel_chB; i++) {
            int index = wave_reading.initial_position_chB + x * time_interval_per_pixel_chB + i;
            if (index < wave_reading.wave.wave_data_chB.size()) {
                y_val_chB += wave_reading.wave.wave_data_chB[index];
            }
        }
        y_val_chB /= time_interval_per_pixel_chB;
        int y_pixel_height_chB = y_val_chB / voltage_interval_per_pixel_chB + mid_y_chB; // height from base for this pixel
        print_dot(y_pixel_height_chB, x_effective, WAVE_READING_COLOR_CH_B, wave_reading.line_thickness, WAVE_READING_LAYER);
    }
}

void init_wave_reading() {
    WaveReading wave_reading;
    wave_reading.display_time_unit_chA = 50; // 50 ns per minimum width
    wave_reading.display_y_unit_chA = 1000; // 1000 mV per minimum height
    wave_reading.display_time_unit_chB = 50; // 50 ns per minimum width
    wave_reading.display_y_unit_chB = 1000; // 1000 mV per minimum height
    wave_reading.y_offset_chA = 0;
    wave_reading.y_offset_chB = 0;
    wave_reading.line_thickness = LINE_WIDTH;
    wave_reading.initial_position_chA = 0;
    wave_reading.initial_position_chB = 0;

    Wave wave;
    wave.wave_time_unit = 1; // 1 ns time difference between samples
    wave.wave_volt_unit = 1; // 1 mV per unit
    for (int i = 0; i < 1000000; i++) {
        // Define a dummy wave of 100kHz sine wave for chA and a 100kHz square wave for chB given that i is in ns
        wave.wave_data_chA.push_back(static_cast<int>(1000 * sin(i * 2 * M_PI / 100)));
        wave.wave_data_chB.push_back((i % 100 < 50) ? 1000 : -1000);
    }
    wave_reading.wave = wave;

    update_wave_reading(wave_reading);
}

void continue_wave_reading() {}