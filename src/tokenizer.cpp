#include "../include/tokenizer.h"

#include <iostream>

Tokenizer::Tokenizer() {
    // Initialize tokenizer
}

std::vector<Token> Tokenizer::tokenize(std::string input) {
    _tokens.clear(); // Clear all tokens before tokenizing input
    // Tokenize every string on the basis of spaces and commas
    std::sregex_token_iterator it(
        input.begin(), input.end(), token_delimiter
    );
    const std::sregex_token_iterator end;
    // Iterate through all strings, create tokens and push to tokens vector
    while (it != end) {
        const auto token = Token(determine_token(*it), *it);
        _tokens.push_back(token);
        ++it;
    }

    return _tokens;
}

Token::Type Tokenizer::determine_token(const std::string& token) {
    if (is_instr(token)) {
        return Token::instr;
    }
    if (is_register(token)) {
        return Token::reg;
    }
    if (is_byte(token)) {
        return Token::byte;
    }
    if (is_address(token)) {
        return Token::addr;
    }
    if (is_comma(token)) {
        return Token::comma;
    }
    if (is_colon(token)) {
        return Token::colon;
    }
    if (is_sound_timer(token)) {
        return Token::sound_timer;
    }
    if (is_delay_timer(token)) {
        return Token::delay_timer;
    }
    if (is_i(token)) {
        return Token::i;
    }
    if (is_bracket_i(token)) {
        return Token::bracket_i;
    }
    if (is_key_press(token)) {
        return Token::key_press;
    }
    if (is_f(token)) {
        return Token::f;
    }
    if (is_bcd(token)) {
        return Token::bcd;
    }
    if (is_nibble(token)) {
        return Token::nibble;
    }
    if (is_label(token)) {
        return Token::label;
    }
    throw std::runtime_error("Could not determine token type for " + token);
}

bool Tokenizer::is_instr(const std::string& token) {
    return std::find(
               begin(INSTRUCTIONS),
               end(INSTRUCTIONS),
               token) != end(INSTRUCTIONS);
}

bool Tokenizer::is_label(const std::string &token) {
    return std::regex_match(token, label_matcher);
}

bool Tokenizer::is_register(const std::string& token) {
    return std::regex_match(token, reg_matcher);
}

bool Tokenizer::is_byte(const std::string& token) {
    return std::regex_match(token, byte_matcher);
}

bool Tokenizer::is_address(const std::string& token) {
    return std::regex_match(token, addr_matcher);
}

bool Tokenizer::is_comma(const std::string& token) {
    return token == ",";
}

bool Tokenizer::is_colon(const std::string &token) {
    return token == ":";
}

bool Tokenizer::is_sound_timer(const std::string& token) {
    return token == "ST";
}

bool Tokenizer::is_delay_timer(const std::string& token) {
    return token == "DT";
}

bool Tokenizer::is_i(const std::string& token) {
    return token == "I";
}

bool Tokenizer::is_bracket_i(const std::string& token) {
    return token == "[I]";
}

bool Tokenizer::is_key_press(const std::string& token) {
    return token == "K";
}

bool Tokenizer::is_nibble(const std::string& token) {
    return std::regex_match(token, nibble_matcher);
}

bool Tokenizer::is_f(const std::string& token) {
    return token == "F";
}

bool Tokenizer::is_bcd(const std::string& token) {
    return token == ".BCD";
}
