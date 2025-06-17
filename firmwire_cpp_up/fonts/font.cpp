#include <iostream>
#include <vector>
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include "embedded_font.h"
#include "font.h"
using namespace std;

vector<vector<bool>> renderCharacterToBitmap(char c, int fontSize) {
    stbtt_fontinfo font;
    if (!stbtt_InitFont(&font, embeddedFontData, 0)) {
        throw std::runtime_error("Failed to initialize embedded font.");
    }

    float scale = stbtt_ScaleForPixelHeight(&font, fontSize);

    int width, height, xoff, yoff;
    unsigned char* bitmap = stbtt_GetCodepointBitmap(
        &font, 0, scale, c, &width, &height, &xoff, &yoff
    );

    if (!bitmap) throw std::runtime_error("Failed to render character bitmap.");

    vector<vector<bool>> bitmap2D(height, vector<bool>(width));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            bitmap2D[y][x] = bitmap[y * width + x] > 128 ? true : false;
        }
    }

    stbtt_FreeBitmap(bitmap, nullptr);

    return bitmap2D;
}

void print_character(int x, int y, char c, int font_size, int color, int LAYER) {
    vector<vector<bool>> bitmap = renderCharacterToBitmap(c, font_size);
    for (size_t i = 0; i < bitmap.size(); i++) {
        for (size_t j = 0; j < bitmap[i].size(); j++) {
            if (bitmap[i][j]) {
                if (y + i < HEIGHT && x + j < WIDTH) {
                    display_buffer[y + i][x + j][LAYER] = color;
                }
            }
        }
    }
}

void print_text(int x, int y, const string& text, int font_size, vector<int> spacing, int color, int LAYER) {
    int x_now = x;
    for (size_t i = 0; i < text.length(); i++) {
        print_character(x_now, y, text[i], font_size, color, LAYER);
        x_now += spacing[i];
    }
}
