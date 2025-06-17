#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../defs/constants.h"
#include "graphics.h"
#include "../fonts/font.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

void print_dot(int y, int x, int color, int width, vector<vector<int>> &layer_buffer) {
    for(int i = -width / 2; i <= width / 2; i++) {
        for(int j = -width / 2; j <= width / 2; j++) {
            if (y + i >= 0 && y + i < HEIGHT && x + j >= 0 && x + j < WIDTH) {
                layer_buffer[y + i][x + j] = color;
            }
        }
    }
}

void print_rectangle(int y, int x, int color, int width, int height, vector<vector<int>> &layer_buffer) {
    int half_width = width / 2;
    int half_height = height / 2;
    for(int i = -half_height; i <= half_height; i++) {
        for(int j = -half_width; j <= half_width; j++) {
            int yy = y + i, xx = x + j;
            if (yy >= 0 && yy < HEIGHT && xx >= 0 && xx < WIDTH) {
                layer_buffer[yy][xx] = color;
                print_dot(yy, xx, color, 3, layer_buffer);
            }
        }
    }
}

void print_rounded_rectangle_bottom_left(int y, int x, int color, int width, int height, int corner_radius, vector<vector<int>> &layer_buffer) {
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
            int yy = y - i, xx = x + j;
            if (!(in_top_left_corner || in_top_right_corner || in_bottom_left_corner || in_bottom_right_corner) &&
                yy >= 0 && yy < HEIGHT && xx >= 0 && xx < WIDTH) {
                layer_buffer[yy][xx] = color;
            }
        }
    }   
}

void print_rounded_rectangle_top_left(int y, int x, int color, int width, int height, int corner_radius, vector<vector<int>> &layer_buffer) {
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
            int yy = y + i, xx = x + j;
            if (!(in_top_left_corner || in_top_right_corner || in_bottom_left_corner || in_bottom_right_corner) &&
                yy >= 0 && yy < HEIGHT && xx >= 0 && xx < WIDTH) {
                layer_buffer[yy][xx] = color;
            }
        }
    }
}

bool is_point_in_polygon(int x, int y, const vector<pair<int, int>>& points) {
    bool inside = false;
    for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++) {
        int xi = points[i].first, yi = points[i].second;
        int xj = points[j].first, yj = points[j].second;

        bool intersect = ((yi > y) != (yj > y)) &&
                         (x < (xj - xi) * (y - yi) / (double)(yj - yi) + xi);
        if (intersect) inside = !inside;
    }
    return inside;
}

void print_polygon(const vector<pair<int, int>>& points, int color, vector<vector<int>> &layer_buffer) {
    if (points.size() < 3) return;

    int min_x = WIDTH, max_x = 0, min_y = HEIGHT, max_y = 0;
    for (const auto& point : points) {
        min_x = min(min_x, point.first);
        max_x = max(max_x, point.first);
        min_y = min(min_y, point.second);
        max_y = max(max_y, point.second);
    }

    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            if (is_point_in_polygon(x, y, points)) {
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                    layer_buffer[y][x] = color;
                }
            }
        }
    }
}

vector<pair<int, int>> transform_points(const vector<pair<int, int>>& points, int x, int y) {
    vector<pair<int, int>> transformed_points;
    for (const auto& point : points) {
        transformed_points.push_back({point.first + x, point.second + y});
    }
    return transformed_points;
}

void print_pointer(int x, int y, int color, vector<vector<int>> &layer_buffer) {
    int width = 15;
    int height = 10;

    vector<pair<int, int>> pointer_points_custom = {
        {0, 0},
        {width * 2 / 3, 0},
        {width, height / 2},
        {width * 2 / 3, height},
        {0, height}
    };
    print_polygon(transform_points(pointer_points_custom, x, y), color, layer_buffer);
}

void safe_pixel_color(int x, int y, int color, vector<vector<int>> &layer_buffer) {
    if (x < 0 || x > WIDTH - GLOBAL_X_MARGIN * 2 || y < 0 || y > HEIGHT - GLOBAL_Y_MARGIN * 2) {
        throw runtime_error("Pixel is out of bounds");
    }
    int x_shifted = x + GLOBAL_X_MARGIN;
    int y_shifted = y + GLOBAL_Y_MARGIN;
    layer_buffer[y_shifted][x_shifted] = color;
}
