#ifndef CHIPEIGHT_ASSEMBLER_TRANSLATOR_H
#define CHIPEIGHT_ASSEMBLER_TRANSLATOR_H
#include <cstdint>
#include <string>
#include <vector>

class Translator {
private:
    std::vector<uint16_t> _opcodes;

    std::pair<uint8_t, uint8_t> split_opcode(uint16_t opcode);

public:
    Translator();

    void add_opcode(uint16_t opcode);

    void load_opcodes(const std::vector<std::uint16_t> opcodes);

    void translate_to_file(const std::string& filename);
};

#endif //CHIPEIGHT_ASSEMBLER_TRANSLATOR_H
