#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
using namespace std;

void print_dot(int x, int y, int color, int width, int LAYER);
void print_rectangle(int x, int y, int color, int width, int height, int LAYER);
void print_bitmap_top_left(int x, int y, int color, int width, int height, int LAYER, const vector<vector<bool>> bitmap);
void print_rounded_rectangle_bottom_left(int y, int x, int color, int width, int height, int corner_radius, int LAYER);
void print_rounded_rectangle_top_left(int y, int x, int color, int width, int height, int corner_radius, int LAYER);


#endif
