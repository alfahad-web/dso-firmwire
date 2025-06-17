#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <string>
using namespace std;

void print_dot(int x, int y, int color, int width, vector<vector<int>> &layer_buffer);
void print_rectangle(int x, int y, int color, int width, int height, vector<vector<int>> &layer_buffer);
void print_rounded_rectangle_bottom_left(int y, int x, int color, int width, int height, int corner_radius, vector<vector<int>> &layer_buffer);
void print_rounded_rectangle_top_left(int y, int x, int color, int width, int height, int corner_radius, vector<vector<int>> &layer_buffer);
void print_pointer(int y, int x, int color, vector<vector<int>> &layer_buffer);
void print_polygon(const std::vector<std::pair<int, int>>& points, int color, vector<vector<int>> &layer_buffer);
void safe_pixel_color(int x, int y, int color, vector<vector<int>> &layer_buffer);

#endif
