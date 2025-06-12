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

// int main() {
//     try {
//         vector<vector<bool>> bitmap = renderCharacterToBitmap('a', 40);  // You can change the char or size
//         for (int y = 0; y < bitmap.size(); ++y) {
//             for (int x = 0; x < bitmap[y].size(); ++x) {
//                 cout << (bitmap[y][x] ? '#' : ' ');
//             }
//             cout << "\n";
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << "\n";
//     }
//     return 0;
// }
