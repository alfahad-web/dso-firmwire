#ifndef FONT_H
#define FONT_H

#include <vector>
using namespace std;

vector<vector<bool>> renderCharacterToBitmap(char c, int fontSize);
void print_character(int x, int y, char c, int font_size, int color, int LAYER);
void print_text(int x, int y, const string& text, int font_size, vector<int> spacing, int color, int LAYER);

#endif

