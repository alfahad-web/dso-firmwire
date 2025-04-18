#include "../global/global.h"
#include "graphics.h"
#include <vector>
using namespace std;

void print_dot(int y, int x, int color, int width, int LAYER) {
    for(int i = -width / 2; i <= width / 2; i++) {
        for(int j = -width / 2; j <= width / 2; j++) {
            if (y + i >= 0 && y + i < HEIGHT && x + j >= 0 && x + j < WIDTH) {
                display_buffer[y + i][x + j][LAYER] = color;
            }
        }
    }
}

void print_rectangle(int y, int x, int color, int width, int height, int LAYER) {
    int half_width = width / 2;
    int half_height = height / 2;
    for(int i = -half_height; i <= half_height; i++) {
        for(int j = -half_width; j <= half_width; j++) {
            if (y + i >= 0 && y + i < HEIGHT && x + j >= 0 && x + j < WIDTH) {
                display_buffer[y + i][x + j][LAYER] = color;
            }
        }
    }
}

void print_rounded_rectangle_bottom_left(int y, int x, int color, int width, int height, int corner_radius, int LAYER) {
    for(int i = height - 1; i >= 0; i--) {
        for(int j = 0; j <= width; j++) {
            bool in_top_left_corner = (i < corner_radius && j < corner_radius) && 
                                      ((corner_radius - i) * (corner_radius - i) + (corner_radius - j) * (corner_radius - j) > corner_radius * corner_radius);
            bool in_top_right_corner = (i < corner_radius && j >= width - corner_radius) && 
                                       ((corner_radius - i) * (corner_radius - i) + (j - (width - corner_radius)) * (j - (width - corner_radius)) > corner_radius * corner_radius);
            bool in_bottom_left_corner = (i >= height - corner_radius && j < corner_radius) && 
                                         ((i - (height - corner_radius)) * (i - (height - corner_radius)) + (corner_radius - j) * (corner_radius - j) > corner_radius * corner_radius);
            bool in_bottom_right_corner = (i >= height - corner_radius && j >= width - corner_radius) && 
                                          ((i - (height - corner_radius)) * (i - (height - corner_radius)) + (j - (width - corner_radius)) * (j - (width - corner_radius)) > corner_radius * corner_radius);
            if (!(in_top_left_corner || in_top_right_corner || in_bottom_left_corner || in_bottom_right_corner) && 
                y - i >= 0 && y - i < HEIGHT && x + j >= 0 && x + j < WIDTH) {
                display_buffer[y - i][x + j][LAYER] = color;
            }
        }
    }
}

void print_rounded_rectangle_top_left(int y, int x, int color, int width, int height, int corner_radius, int LAYER) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            bool in_top_left_corner = (i < corner_radius && j < corner_radius) && 
                                      ((corner_radius - i) * (corner_radius - i) + (corner_radius - j) * (corner_radius - j) > corner_radius * corner_radius);
            bool in_top_right_corner = (i < corner_radius && j >= width - corner_radius) && 
                                       ((corner_radius - i) * (corner_radius - i) + (j - (width - corner_radius)) * (j - (width - corner_radius)) > corner_radius * corner_radius);
            bool in_bottom_left_corner = (i >= height - corner_radius && j < corner_radius) && 
                                         ((i - (height - corner_radius)) * (i - (height - corner_radius)) + (corner_radius - j) * (corner_radius - j) > corner_radius * corner_radius);
            bool in_bottom_right_corner = (i >= height - corner_radius && j >= width - corner_radius) && 
                                          ((i - (height - corner_radius)) * (i - (height - corner_radius)) + (j - (width - corner_radius)) * (j - (width - corner_radius)) > corner_radius * corner_radius);
            if (!(in_top_left_corner || in_top_right_corner || in_bottom_left_corner || in_bottom_right_corner) && 
                y + i >= 0 && y + i < HEIGHT && x + j >= 0 && x + j < WIDTH) {
                display_buffer[y + i][x + j][LAYER] = color;
            }
        }
    }
}

void print_bitmap_top_left(int y, int x, int color, int height, int width, int LAYER, const vector<vector<bool>> bitmap) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if (y + i >= 0 && y + i < HEIGHT && x + j >= 0 && x + j < WIDTH) {
                display_buffer[y + i][x + j][LAYER] = color;
            }
        }
    }
}