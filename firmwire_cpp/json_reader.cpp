#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>

void readAndPrintWidgetStates(const std::string& filename) {
    std::ifstream file(filename, std::ifstream::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    Json::Value root;
    file >> root;

    std::cout << "Buttons:" << std::endl;
    const Json::Value buttons = root["buttons"];
    for (Json::ValueConstIterator it = buttons.begin(); it != buttons.end(); ++it) {
        std::cout << it.key().asString() << ": " << it->asBool() << std::endl;
    }

    std::cout << "Sliders:" << std::endl;
    const Json::Value sliders = root["sliders"];
    for (Json::ValueConstIterator it = sliders.begin(); it != sliders.end(); ++it) {
        std::cout << it.key().asString() << ": " << it->asDouble() << std::endl;
    }
}

int main() {
    readAndPrintWidgetStates("frontend_python/widget_states.json");
    return 0;
}
