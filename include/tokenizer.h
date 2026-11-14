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

    // Programs should not access register F, so we limit till E
    std::regex reg_matcher = std::regex(R"(V[A-E0-9])");

    std::regex byte_matcher = std::regex(R"([A-F0-9]{2})");

    std::regex addr_matcher = std::regex(R"(0x[A-F0-9]{3})");

    std::regex nibble_matcher = std::regex(R"(0x[A-F0-9])");

    std::regex label_matcher = std::regex(R"([A-Za-z_][A-Za-z0-9_]*)");

    std::regex token_delimiter = std::regex(
        R"(\[I\]|\.BCD|0[xX][0-9A-Fa-f]+|[A-Za-z_][A-Za-z0-9_]*|[0-9]+|,|:)"
    );

    const std::array<std::string, 21> INSTRUCTIONS = {
        "SYS", "CLS", "RET", "JP", "CALL", "SE", "SNE",
        "LD", "ADD", "OR", "AND", "XOR", "ADD", "SUB",
        "SHR", "SUBN", "SHL", "RND", "DRW", "SKP", "SKNP"
    };

    Token::Type determine_token(const std::string &token);

    bool is_label(const std::string& token);

    bool is_colon(const std::string& token);

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
