#ifndef CHIPEIGHT_ASSEMBLER_INSTRUCTIONS_H
#define CHIPEIGHT_ASSEMBLER_INSTRUCTIONS_H
#include <cstdint>
#include <map>
#include <vector>
#include <optional>
#include "reader.h"
#include "token.h"
#include "instruction.h"
#include "tokenizer.h"
#include "parser.h"

class ParsingErrorException : public std::exception {
private:
    std::string message;

public:
    ParsingErrorException(const char *msg) : message(msg) {
    }

    ParsingErrorException(const std::string &string) : message(string) {
    }

    // Override what() method
    const char *what() const noexcept override {
        return message.c_str();
    }
};

class Parser {
private:
    // Initialise variables
    std::vector<Token> _tokens = {};
    int pos = 0;
    uint16_t current_addr = 0x200;
    Instruction current_instr = Instruction(0x0000, true, {});
    // Map labels to addresses
    std::map<std::string, uint16_t> valid_labels = {};

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

    void parse_colon();

    void parse_key_press();

    void parse_delay_timer();

    void parse_sound_timer();

    void parse_i();

    void parse_bracket_i();

    void parse_bcd();

    void parse_f();

    void parse_label_start();

    uint16_t parse_label();

    uint16_t parse_hex(char hex);

    uint16_t parse_register();

    uint16_t parse_byte();

    uint16_t parse_addr();

    uint16_t parse_nibble();

    uint16_t parse_addr_or_label();

    std::optional<Instruction> parse(std::vector<Token> tokens);

public:
    Parser();

    std::vector<Instruction> parse_file(Reader &reader, Tokenizer &tokenizer);
};

#endif //CHIPEIGHT_ASSEMBLER_INSTRUCTIONS_H
