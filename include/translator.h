#ifndef CHIPEIGHT_ASSEMBLER_TRANSLATOR_H
#define CHIPEIGHT_ASSEMBLER_TRANSLATOR_H
#include <cstdint>
#include <string>
#include <vector>
#include "instruction.h"

class Translator {
private:
    std::vector<Instruction> _instructions;

    std::pair<uint8_t, uint8_t> split_opcode(uint16_t opcode);

public:
    Translator();

    void add_instruction(const Instruction instr);

    void load_instructions(const std::vector<Instruction>& instructions);

    void translate_to_file(const std::string& filename);
};

#endif //CHIPEIGHT_ASSEMBLER_TRANSLATOR_H
