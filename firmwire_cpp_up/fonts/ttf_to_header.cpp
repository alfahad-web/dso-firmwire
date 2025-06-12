#include <fstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>

void generateHeader(const std::string& fontPath, const std::string& savePath, const std::string& outHeaderName, const std::string& varName) {
    std::ifstream in(fontPath, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open font file: " << fontPath << "\n";
        return;
    }

    std::vector<unsigned char> data(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());

    std::string fullOutputPath = savePath + outHeaderName;
    std::ofstream out(fullOutputPath);
    if (!out) {
        std::cerr << "Failed to write header file: " << fullOutputPath << "\n";
        return;
    }

    out << "// Auto-generated header for embedded font\n";
    out << "#pragma once\n\n";
    out << "const unsigned char " << varName << "[] = {\n    ";

    for (size_t i = 0; i < data.size(); ++i) {
        out << std::setw(3) << static_cast<int>(data[i]) << ",";
        if ((i + 1) % 16 == 0) out << "\n    ";
    }

    out << "\n};\n\n";
    out << "const int " << varName << "_size = " << data.size() << ";\n";

    std::cout << "Header file generated: " << fullOutputPath << " with " << data.size() << " bytes.\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <font_file.ttf> <save_path/>\n";
        return 1;
    }

    std::string fontPath = argv[1];
    std::string savePath = argv[2];
    std::string outputHeader = "embedded_font.h";
    std::string variableName = "embeddedFontData";

    generateHeader(fontPath, savePath, outputHeader, variableName);
    return 0;
}