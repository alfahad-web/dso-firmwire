#ifndef ANNOTATIONS_H
#define ANNOTATIONS_H

#include "../../global/global.h"

void init_annotations();
void continue_annotations();
void print_dot(int x, int y, int color, int width, int LAYER);
void print_rectangle(int x, int y, int color, int width, int height, int LAYER);

#endif
