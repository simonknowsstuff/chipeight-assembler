#ifndef CHIPEIGHT_ASSEMBLER_TOKEN_H
#define CHIPEIGHT_ASSEMBLER_TOKEN_H
#include <string>

class Token {
private:
    std::string _content;

public:
    enum Type {
        label,
        instr,
        reg,
        byte,
        addr,
        comma,
        colon,
        sound_timer,
        delay_timer,
        i,
        bracket_i,
        key_press,
        nibble,
        f,
        bcd
    } _type;

    Token(const Type type, const std::string &content) {
        _type = type;
        _content = content;
    };

    Type get_type() {
        return _type;
    };

    std::string get_content() {
        return _content;
    };
};

#endif //CHIPEIGHT_ASSEMBLER_TOKEN_H
