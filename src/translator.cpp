#include "../include/translator.h"
#include <iostream>
#include <fstream>

Translator::Translator() {
}

std::pair<uint8_t, uint8_t> Translator::split_opcode(const uint16_t opcode) {
    // Split opcode into 1 byte each, big endian order
    auto first_half = static_cast<uint8_t>(opcode >> 8);
    auto second_half = static_cast<uint8_t>(opcode & 0xFF);
    return std::pair {first_half, second_half};
}

void Translator::add_opcode(const uint16_t opcode) {
    _opcodes.push_back(opcode);
}

void Translator::load_opcodes(const std::vector<uint16_t> opcodes) {
    _opcodes = opcodes;
}

void Translator::translate_to_file(const std::string& filename) {
    // Main loop to write opcode into the ROM file
    std::ofstream wf(filename, std::ios::out | std::ios::binary);
    if (!wf || !wf.is_open()) {
        throw std::runtime_error("Could not write into file " + filename);
    }
    for (const auto opcode : _opcodes) {
        auto [high, low] = split_opcode(opcode);
        const uint8_t bytes[] = {high, low};
        wf.write(reinterpret_cast<const char *>(bytes), 2);
    }
    std::cout << "ROM written to " << filename << std::endl;
}
