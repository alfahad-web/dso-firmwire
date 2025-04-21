#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../global/global.h"
#include "graphics.h"
#include <vector>
#include <iostream>
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
                print_dot(y + i, x + j, color, 3, LAYER);
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

bool is_point_in_polygon(int x, int y, const std::vector<std::pair<int, int>>& points) {
    bool inside = false;
    for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++) {
        int xi = points[i].first, yi = points[i].second;
        int xj = points[j].first, yj = points[j].second;

        bool intersect = ((yi > y) != (yj > y)) &&
                         (x < (xj - xi) * (y - yi) / (yj - yi) + xi);
        if (intersect) inside = !inside;
    }
    return inside;
}

void print_polygon(const std::vector<std::pair<int, int>>& points, int color, int LAYER) {
    if (points.size() < 3) return; // A polygon must have at least 3 points

    // Find the bounding box of the polygon
    int min_x = WIDTH, max_x = 0, min_y = HEIGHT, max_y = 0;
    for (const auto& point : points) {
        min_x = std::min(min_x, point.first);
        max_x = std::max(max_x, point.first);
        min_y = std::min(min_y, point.second);
        max_y = std::max(max_y, point.second);
    }

    // Scan through the bounding box and determine if each point is inside the polygon
    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            if (is_point_in_polygon(x, y, points)) {
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                    display_buffer[y][x][LAYER] = color;
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
void print_pointer(int x, int y, int color, int LAYER) {
    int width = 15;
    int height = 10;

    vector<pair<int, int>> pointer_points_custom = {
        {0, 0},
        {width * 2 / 3, 0},
        {width, height / 2},
        {width * 2 / 3, height},
        {0, height}
    };
    print_polygon(transform_points(pointer_points_custom, x, y), color, LAYER);
}