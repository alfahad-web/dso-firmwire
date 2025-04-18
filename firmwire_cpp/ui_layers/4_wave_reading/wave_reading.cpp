#include "wave_reading.h"
#include "../../global/global.h"
#include <stdlib.h>

struct Wave {
    vector<int> wave_data; // the wave data in mV vs time in ns
    int wave_time_unit; // time unit that the wave data is measured in (ns), suppose 2 ns means the samples are taken after each 2 ns
    int wave_volt_unit; // the voltage unit that the wave data is measured in (mV), suppose 1 mV means the samples are measured in mV
};

struct WaveReading {
    Wave wave;
    int display_time_unit; // time unit in ns, the time interval of 5 minimum points or the smallest rectangle width
    int display_y_unit; // voltage unit in mV, the voltage interval of 5 minimum points or the smallest rectangle height
    int x_offset;
    int y_offset_chA;
    int y_offset_chB;
    int line_thickness;
    int initial_position; // the index of  wave_data that the display now starts from
};

void print_dot(int x, int y, int color, int width) {
    for(int i = -width / 2; i <= width / 2; i++) {
        for(int j = -width / 2; j <= width / 2; j++) {
            if (x + i >= 0 && x + i < HEIGHT && y + j >= 0 && y + j < WIDTH) {
                display_buffer[x + i][y + j][WAVE_READING_LAYER] = color;
            }
        }
    }
}

void update_wave_reading(WaveReading wave_reading) {
    int time_interval_per_pixel = wave_reading.display_time_unit / X_UNITS; // in ns
    int voltage_interval_per_pixel = wave_reading.display_y_unit / Y_UNITS; // in mV

    //instead of updating the display buffer, check if the pixel value has differed
    //if differed, then request pixel update in queue
    for (int x = 0; x < WIDTH; x++) {
        int y_val = 0, diff =  wave_reading.initial_position;
        for(int i = 0; i < time_interval_per_pixel; i++) {
            // linear progression a + nd; a => wave_reading.initial_position; n => x; d => time_interval_per_pixel;
            y_val += wave_reading.wave[wave_reading.initial_position + x * time_interval_per_pixel];
        }
        y_val /= time_interval_per_pixel;
        int y_pixel_height = y_val / voltage_interval_per_pixel; // height from the x_axis for this pixel
    }
}

void init_wave_reading() {
    WaveReading wave_reading;
    wave_reading.display_time_unit = 50; // 50 ns per minimum width
    wave_reading.display_y_unit = 1000; // 1000 mV per minimum height
    wave_reading.x_offset = 0;
    wave_reading.y_offset = 0;
    wave_reading.line_width = 2;

    Wave wave;
    wave.wave_time_unit = 1; // 1 ns time difference between samples
    for (int i = 0; i < 1000000; i++) {
        //define a dummy wave of 100kHz sine wave given that i is in ns
        wave.wave_data.push_back(sin(i * 2 * M_PI / 10));
    }
    wave_reading.wave = wave;

    update_wave_reading(wave_reading);
}

void continue_wave_reading() {}