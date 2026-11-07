#ifndef CHIPEIGHT_ASSEMBLER_TOKENIZER_H
#define CHIPEIGHT_ASSEMBLER_TOKENIZER_H
#include <array>
#include <regex>
#include <string>
#include <vector>
#include "token.h"

class Tokenizer {
private:
    std::vector<Token> _tokens;

    std::regex reg_matcher = std::regex("V[A-F0-9]");

    std::regex byte_matcher = std::regex("[A-F0-9][A-F0-9]");

    std::regex addr_matcher = std::regex("[A-F0-9][A-F0-9][A-F0-9]");

    std::regex nibble_matcher = std::regex("0x[A-F0-9]");

    // std::regex label_matcher = std::regex(R"(\\w+:)");

    std::regex token_delimiter = std::regex(R"(\w+|,|\[\w+\]|\.[A-Z]+)");

    const std::array<std::string, 21> INSTRUCTIONS = {
        "SYS", "CLS", "RET", "JP", "CALL", "SE", "SNE",
        "LD", "ADD", "OR", "AND", "XOR", "ADD", "SUB",
        "SHR", "SUBN", "SHL", "RND", "DRW", "SKP", "SKNP"
    };

    Token::Type determine_token(const std::string &token);

    // bool is_label(const std::string& token);

    bool is_instr(const std::string &token);

    bool is_register(const std::string &token);

    bool is_byte(const std::string &token);

    bool is_address(const std::string &token);

    bool is_comma(const std::string &token);

    bool is_sound_timer(const std::string &token);

    bool is_delay_timer(const std::string &token);

    bool is_i(const std::string &token);

    bool is_bracket_i(const std::string &token);

    bool is_key_press(const std::string &token);

    bool is_nibble(const std::string &token);

    bool is_f(const std::string &token);

    bool is_bcd(const std::string &token);

public:
    Tokenizer();

    std::vector<Token> tokenize(std::string input);
};

#endif //CHIPEIGHT_ASSEMBLER_TOKENIZER_H
