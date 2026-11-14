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

void Translator::add_instruction(const Instruction instr) {
    if (!instr.is_fully_parsed()) { // Label / invalid opcode
        return;
    }
    _instructions.push_back(instr);
}

void Translator::load_instructions(const std::vector<Instruction>& instructions) {
    _instructions = instructions;
}

void Translator::translate_to_file(const std::string& filename) {
    // Main loop to write opcode into the ROM file
    std::ofstream wf(filename, std::ios::out | std::ios::binary);
    if (!wf || !wf.is_open()) {
        throw std::runtime_error("Could not write into file " + filename);
    }
    for (const auto instr : _instructions) {
        auto [high, low] = split_opcode(instr.get_opcode());
        const uint8_t bytes[] = {high, low};
        wf.write(reinterpret_cast<const char *>(bytes), 2);
    }
    std::cout << "ROM written to " << filename << std::endl;
}
