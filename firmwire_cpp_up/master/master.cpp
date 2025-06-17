#include <iostream>
#include <vector>
#include "../defs/constants.h"
#include <thread>
#include <chrono>
#include <windows.h>
#include "master.h"
#include "../defs/types.h"
#include "../L0/l0.h"
#include "../L1/l1.h"

using namespace std;

// function to update any number of pixels asynchronously to the main window
void updatePixels(const std::vector<PixelUpdate>& pixels) {
    PixelUpdateArray* arr = new PixelUpdateArray;
    arr->count = pixels.size();
    arr->pixels = new PixelUpdate[arr->count];
    std::copy(pixels.begin(), pixels.end(), arr->pixels);

    // Send message to main window to update
    PostMessage(g_hwnd, WM_UPDATE_PIXELS, 0, reinterpret_cast<LPARAM>(arr));
}

// 2D arrays for every layers and 2D dispBuff
vector<vector<ll>> dispBuffLayer0 = vector<vector<ll>>(HEIGHT, vector<ll>(WIDTH, 0));
vector<vector<ll>> dispBuffLayer1 = vector<vector<ll>>(HEIGHT, vector<ll>(WIDTH, 0));
vector<vector<ll>> dispBuffLayer2 = vector<vector<ll>>(HEIGHT, vector<ll>(WIDTH, 0));
vector<vector<ll>> dispBuffLayer3 = vector<vector<ll>>(HEIGHT, vector<ll>(WIDTH, 0));
vector<vector<ll>> dispBuffLayer4 = vector<vector<ll>>(HEIGHT, vector<ll>(WIDTH, 0));
vector<vector<ll>> dispBuff = vector<vector<ll>>(HEIGHT, vector<ll>(WIDTH, 0));

// behavior variables as struct behaviorState
struct behaviorState {
    
};

// 0 => pixel not set
// +ve => pixel set by this layer
// -ve => pixel set by previous layer
// but dispBuff is always positive
void synchronize_layers() {
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            if (dispBuffLayer0[x][y] == 0) {
                dispBuffLayer0[x][y] = -abs(dispBuff[x][y]);
            }
            if (dispBuffLayer1[x][y] == 0) {
                dispBuffLayer1[x][y] = -abs(dispBuffLayer0[x][y]);
            }
            if (dispBuffLayer2[x][y] == 0) {
                dispBuffLayer2[x][y] = -abs(dispBuffLayer1[x][y]);
            }
            if (dispBuffLayer3[x][y] == 0) {
                dispBuffLayer3[x][y] = -abs(dispBuffLayer2[x][y]);
            }
            if (dispBuffLayer4[x][y] == 0) {
                dispBuffLayer4[x][y] = -abs(dispBuffLayer3[x][y]);
            }
        }
    }
}

void recalcBehaviorState(behaviorState& state) {
    
}

void update_ui() {
    vector<PixelUpdate> pixels;
    bool changed = false;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            ll pixelVal = abs(dispBuffLayer4[y][x]);
            if (pixelVal != dispBuff[y][x]) {
                pixels.push_back({x, y, pixelVal});
                dispBuff[y][x] = pixelVal;
                changed = true;
            }
        }   
    }
    if (changed) {
        updatePixels(pixels);
        changed = false;
    }
}

void master() {
    // start the waveReader thread

    // initialize the behavior state
    behaviorState state;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(SCREEN_REFRESH_DELAY));
        
        recalcBehaviorState(state);
        
        make_ui_Layer0();
        make_ui_Layer1();
        // make_ui_Layer2();
        // make_ui_Layer3();
        // make_ui_Layer4();
        
        synchronize_layers();

        update_ui();
    }
}