#include "graphing.h"
#include "../../global/global.h"
#include "../../graphics/graphics.h"
#include <stdlib.h>

struct Graph {
    int x_units;
    int y_units;
    int line_width;
};

void update_graph(Graph graph) {
    int mid_x = screen_width / 2 + global_x_offset;
    int mid_y = screen_height / 2 + global_y_offset;

    int interval_x = graph.x_units / 5;
    int interval_y = graph.y_units / 5;

    //instead of updating the display buffer, check if the pixel value has differed
    //if differed, then request pixel update in queue
    for (int y = 0; y < screen_height; y++) {
        for (int x = 0; x < screen_width; x++) {
            int y_effective = y + global_y_offset;
            int x_effective = x + global_x_offset;
            if(abs(y_effective - mid_y) % graph.x_units == 0 && abs(x_effective - mid_x) % interval_y == 0) {
                print_dot(y_effective, x_effective, GRAPHING_COLOR, graph.line_width, GRAPHING_LAYER);
            } else if(abs(x_effective - mid_x) % graph.y_units == 0 && abs(y_effective - mid_y) % interval_x == 0) {
                print_dot(y_effective, x_effective, GRAPHING_COLOR, graph.line_width, GRAPHING_LAYER);
            }
        }
    }
}

void init_graphing() {
    Graph graph;
    graph.x_units = X_UNITS;
    graph.y_units = Y_UNITS;
    graph.line_width = 2;

    update_graph(graph);
}

void continue_graphing() {}