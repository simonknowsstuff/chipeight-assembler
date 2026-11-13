#include "../include/reader.h"

Reader::Reader(const std::string& filename) {
    rom_file = std::ifstream(filename);
    if (!rom_file.is_open()) {
        throw std::runtime_error("Could not load ROM file");
    }
}

std::optional<std::string> Reader::read_line() {
    std::string line;
    if (getline(rom_file, line)) {
        return line;
    }
    return std::nullopt;
}
