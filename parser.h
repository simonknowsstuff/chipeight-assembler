#ifndef CHIPEIGHT_ASSEMBLER_INSTRUCTIONS_H
#define CHIPEIGHT_ASSEMBLER_INSTRUCTIONS_H
#include <cstdint>
#include <vector>
#include "token.h"
#include <stdexcept>

class ParsingErrorException : public std::exception {
private:
    std::string message;

public:
    ParsingErrorException(const char* msg) :
    message(msg) {}

    ParsingErrorException(const std::string& string) :
    message(string) {}

    // Override what() method
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Parser {
private:
    std::vector<Token> _tokens = {};
    int pos = 0;
    int opcode_pos = 3;
    uint16_t opcode = 0x0000;

    // Instructions
    void parse_sys();

    void parse_cls();

    void parse_ret();

    void parse_jp();

    void parse_call();

    void parse_se();

    void parse_sne();

    void parse_ld();

    void parse_add();

    void parse_or();

    void parse_and();

    void parse_xor();

    void parse_sub();

    void parse_shr();

    void parse_subn();

    void parse_shl();

    void parse_rnd();

    void parse_drw();

    void parse_skp();

    void parse_sknp();

    // Keywords
    void parse_instruction();

    void parse_comma();

    void parse_key_press();

    void parse_delay_timer();

    void parse_sound_timer();

    void parse_i();

    void parse_bracket_i();

    void parse_bcd();

    void parse_f();

    uint16_t parse_hex(char hex);

    uint16_t parse_register();

    uint16_t parse_byte();

    uint16_t parse_addr();

    uint16_t parse_nibble();

public:
    Parser(std::vector<Token> tokens);

    uint16_t parse();
};

#endif //CHIPEIGHT_ASSEMBLER_INSTRUCTIONS_H
