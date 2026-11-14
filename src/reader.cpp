#include "../include/reader.h"
#include <iostream>

Reader::Reader(const std::string& filename) {
    asm_file = std::ifstream(filename);
    if (!asm_file.is_open()) {
        throw std::runtime_error("Could not load ASM file");
    }
}

std::optional<std::string> Reader::read_line() {
    std::string line;
    if (getline(asm_file, line)) {
        return line;
    }
    return std::nullopt;
}
