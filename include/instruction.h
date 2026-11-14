#ifndef CHIPEIGHT_ASSEMBLER_INSTRUCTION_H
#define CHIPEIGHT_ASSEMBLER_INSTRUCTION_H
#include <cstdint>
#include "token.h"
#include <optional>

class Instruction {
private:
    uint16_t _opcode = 0x0000;
    bool _fully_parsed = false;
    uint16_t _label_addr;
    std::vector<Token> _tokens;

public:
    Instruction(
        const uint16_t opcode,
        const bool fully_parsed,
        const std::vector<Token> tokens
    ) {
        _opcode = opcode;
        _fully_parsed = fully_parsed;
        _tokens = tokens;
    }

    bool is_fully_parsed() const {
        return _fully_parsed;
    }

    void set_fully_parsed(const bool value) {
        _fully_parsed = value;
    }

    uint16_t get_opcode() const {
        return _opcode;
    }

    void set_opcode(const uint16_t opcode) {
        _opcode = opcode;
    }

    void or_opcode(const uint16_t opcode) {
        _opcode |= opcode;
    }

    std::optional<std::uint16_t> get_label_addr() const {
        if (_label_addr) {
            return _label_addr;
        }
        return std::nullopt;
    }

    void set_label_addr(const uint16_t label_addr) {
        _label_addr = label_addr;
    }

    std::vector<Token> get_tokens() {
        return _tokens;
    }

    void set_tokens(const std::vector<Token>& tokens) {
        _tokens = tokens;
    }
};

#endif //CHIPEIGHT_ASSEMBLER_INSTRUCTION_H
