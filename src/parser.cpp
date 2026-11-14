#include "../include/parser.h"
#include <iostream>

Parser::Parser() {
}

std::vector<Instruction> Parser::parse_file(Reader &reader, Tokenizer &tokenizer) {
    std::vector<Instruction> instructions = {};
    // First pass
    // Try and get most instructions parsed, except when there's a label
    // we set the fully_parsed flag for the instruction as false
    // as seen in parse_label()
    while (const auto line = reader.read_line()) {
        if (line->empty()) {
            continue;
        }
        const std::vector<Token> tokens = tokenizer.tokenize(*line);
        if (!parse(tokens)) { // Skip instructions that are invalid
            continue;
        }
        instructions.push_back(current_instr);
    }

    // Second pass
    // Read through partly parsed instructions (labels) and
    // assign proper addresses to their opcodes
    for (Instruction& instr : instructions) {
        if (instr.is_fully_parsed()) { // Skip instructions that are fully parsed
            continue;
        }
        for (Token token : instr.get_tokens()) {
            if (token.get_type() == Token::label) { // Find label token
                // Obtain address mapping from label-address map
                const uint16_t valid_addr = valid_labels[token.get_content()];
                instr.or_opcode(valid_addr); // Perform OR of address to opcode
                instr.set_fully_parsed(true); // Mark instruction as fully parsed
            }
        }
    }

    // Finally,
    return instructions;
}

std::optional<Instruction> Parser::parse(std::vector<Token> tokens) {
    _tokens = tokens; // Set tokens from the parameter
    current_instr = Instruction(0x0000, true, tokens); // Reset instruction

    // Check if the token is a valid instruction / label declaration:
    switch (_tokens[pos].get_type()) {
        default:
            throw ParsingErrorException("Line does not begin with an instruction / label");
        case Token::instr:
            parse_instruction();
            break;
        case Token::label:
            parse_label_start();
            break;
    }

    // Reset tokens and position
    _tokens = {};
    pos = 0;

    if (current_instr.get_opcode() == 0) { // If it's a label declaration, return nothing
        return std::nullopt;
    }

    current_addr += 2; // Increment current address
    return current_instr;
}

void Parser::parse_instruction() {
    ++pos;
    // Call appropriate parse function for instruction:
    if (_tokens[pos-1].get_content() == "SYS") {
        parse_sys();
    } else if (_tokens[pos-1].get_content() == "CLS") {
        parse_cls();
    } else if (_tokens[pos-1].get_content() == "RET") {
        parse_ret();
    } else if (_tokens[pos-1].get_content() == "JP") {
        parse_jp();
    } else if (_tokens[pos-1].get_content() == "CALL") {
        parse_call();
    } else if (_tokens[pos-1].get_content() == "SE") {
        parse_se();
    } else if (_tokens[pos-1].get_content() == "SNE") {
        parse_sne();
    } else if (_tokens[pos-1].get_content() == "LD") {
        parse_ld();
    } else if (_tokens[pos-1].get_content() == "ADD") {
        parse_add();
    } else if (_tokens[pos-1].get_content() == "OR") {
        parse_or();
    } else if (_tokens[pos-1].get_content() == "AND") {
        parse_and();
    } else if (_tokens[pos-1].get_content() == "XOR") {
        parse_xor();
    } else if (_tokens[pos-1].get_content() == "SUB") {
        parse_sub();
    } else if (_tokens[pos-1].get_content() == "SHR") {
        parse_shr();
    } else if (_tokens[pos-1].get_content() == "SUBN") {
        parse_subn();
    } else if (_tokens[pos-1].get_content() == "SHL") {
        parse_shl();
    } else if (_tokens[pos-1].get_content() == "RND") {
        parse_rnd();
    } else if (_tokens[pos-1].get_content() == "DRW") {
        parse_drw();
    } else if (_tokens[pos-1].get_content() == "SKP") {
        parse_skp();
    } else if (_tokens[pos-1].get_content() == "SKNP") {
        parse_sknp();
    } else {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid instruction");
    }
}

void Parser::parse_comma() {
    // Check if comma and increment position
    if (_tokens[pos].get_type() != Token::comma) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid comma");
    }
    ++pos;
}

void Parser::parse_colon() {
    // Check if comma and increment position
    if (_tokens[pos].get_type() != Token::colon) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid comma");
    }
    ++pos;
}

void Parser::parse_key_press() {
    // Check if key press and increment position
    if (_tokens[pos].get_type() != Token::key_press) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not valid key press");
    }
    ++pos;
}

void Parser::parse_delay_timer() {
    // Check if delay timer and increment position
    if (_tokens[pos].get_type() != Token::delay_timer) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not delay timer");
    }
    ++pos;
}

void Parser::parse_sound_timer() {
    // Check if sound timer and increment position
    if (_tokens[pos].get_type() != Token::sound_timer) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not sound timer");
    }
    ++pos;
}

void Parser::parse_i() {
    // Check if I and increment position
    if (_tokens[pos].get_type() != Token::i) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not I");
    }
    ++pos;
}

void Parser::parse_bracket_i() {
    // Check if [I] and increment position
    if (_tokens[pos].get_type() != Token::bracket_i) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not [I]");
    }
    ++pos;
}

void Parser::parse_f() {
    // Check if key press and increment position
    if (_tokens[pos].get_type() != Token::f) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not F");
    }
    ++pos;
}

void Parser::parse_bcd() {
    // Check if key press and increment position
    if (_tokens[pos].get_type() != Token::bcd) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not BCD");
    }
    ++pos;
}

uint16_t Parser::parse_hex(const char hex) {
    uint16_t hex_value = 0;
    // Individually get 16 bit value of each character
    if (hex >= '0' && hex <= '9') {
        hex_value = hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        hex_value = hex - 'A' + 10;
    } else {
        throw ParsingErrorException(_tokens[pos].get_content() + " has invalid hex value");
    }
    return hex_value;
}

uint16_t Parser::parse_register() {
    // Check if register and increment position
    if (_tokens[pos].get_type() != Token::reg) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid register");
    }
    const char hex = _tokens[pos].get_content()[1]; // Get 2nd character in token that specifies hex value
    const uint16_t reg_value = parse_hex(hex); // Parse hex value
    ++pos;
    return reg_value;
}

uint16_t Parser::parse_byte() {
    // Check if byte and increment position
    if (_tokens[pos].get_type() != Token::byte) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid byte");
    }
    const std::string byte_str = _tokens[pos].get_content();
    // Convert byte string to 16 bit integer using static casting
    const auto byte_value = static_cast<uint16_t>(std::stoi(byte_str, nullptr, 16));
    ++pos;
    return byte_value;
}

uint16_t Parser::parse_addr() {
    // Check if address and increment position
    if (_tokens[pos].get_type() != Token::addr) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid address");
    }
    const std::string addr_str = _tokens[pos].get_content();
    // Convert address string to 16 bit integer using static casting
    const auto addr_value = static_cast<uint16_t>(std::stoi(addr_str, nullptr, 16));
    ++pos;
    return addr_value;
}

uint16_t Parser::parse_nibble() {
    // Check if nibble and increment position
    if (_tokens[pos].get_type() != Token::nibble) {
        throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid nibble");
    }
    // Same as register logic:
    const char hex = _tokens[pos].get_content()[2]; // Consider the character after 0x
    const uint16_t nibble_value = parse_hex(hex);
    ++pos;
    return nibble_value;
}

void Parser::parse_label_start() {
    const std::string current_label = _tokens[pos].get_content(); // Get label
    ++pos; // Increment position
    parse_colon(); // Parse colon
    // Map label to address of instruction below the label
    valid_labels[current_label] = current_addr;
}

uint16_t Parser::parse_label() {
    // Mark the instruction as not fully parsed for 2nd pass:
    current_instr.set_fully_parsed(false);
    return 0x0000;
}

uint16_t Parser::parse_addr_or_label() {
    switch (_tokens[pos].get_type()) {
        default:
            throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid label / address");
        case Token::addr:
            return parse_addr();
        case Token::label:
            return parse_label();
    }
}

void Parser::parse_sys() {
    // 0nnn - SYS addr
    current_instr.set_opcode(0x0000);
    current_instr.or_opcode(parse_addr_or_label());
}

void Parser::parse_cls() {
    // 00E0 - CLS
    current_instr.set_opcode(0x00E0);
}

void Parser::parse_ret() {
    // 00EE - RET
    current_instr.set_opcode(0x00EE);
}

void Parser::parse_jp() {
    switch (_tokens[pos].get_type()) {
        default:
            throw ParsingErrorException(_tokens[pos].get_content() + " is not register 0 or address");
        case Token::addr:
            // 1nnn - JP addr
            current_instr.set_opcode(0x1000);
            current_instr.or_opcode(parse_addr());
            break;
        case Token::label:
            // 1nnn - JP label
            current_instr.set_opcode(0x1000);
            current_instr.or_opcode(parse_label());
            // break here
            break;
        case Token::reg:
            // Bnnn - JP V0, addr
            current_instr.set_opcode(0xB000);
            const auto parsed_reg = parse_register();
            if (parsed_reg != 0x0000) { // We specifically want V0
                throw ParsingErrorException(_tokens[pos].get_content() + " is not register V0");
            }
            parse_comma();
            current_instr.or_opcode(parse_addr_or_label());
            break;
    }
}

void Parser::parse_call() {
    // 2nnn - CALL addr
    current_instr.set_opcode(0x2000);
    current_instr.or_opcode(parse_addr_or_label());
}

void Parser::parse_se() {
    current_instr.set_opcode(parse_register() << 8);
    parse_comma();
    switch (_tokens[pos].get_type()) {
        case Token::reg:
            // 5xy0 - SE Vx, Vy
            current_instr.or_opcode(0x5000);
            current_instr.or_opcode(parse_register() << 4);
            break;
        case Token::byte:
            // 3xkk - SE Vx, byte
            current_instr.or_opcode(0x3000);
            current_instr.or_opcode(parse_byte());
            break;
        default:
            throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid register or address");
    }
}

void Parser::parse_sne() {
    current_instr.set_opcode(parse_register() << 8);
    parse_comma();
    switch (_tokens[pos].get_type()) {
        default:
            throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid register or address");
        case Token::reg:
            // 9xy0 - SNE Vx, Vy
            current_instr.or_opcode(0x9000);
            current_instr.or_opcode(parse_register() << 4);
            break;
        case Token::byte:
            // 4xkk - SNE Vx, byte
            current_instr.or_opcode(0x4000);
            current_instr.or_opcode(parse_byte());
            break;
    }
}

void Parser::parse_add() {
    if (_tokens[pos].get_type() == Token::i) {
        // Fx1E - ADD I, Vx
        current_instr.set_opcode(0xF01E);
        ++pos;
        parse_comma();
        current_instr.or_opcode(parse_register() << 8);
        return;
    }
    current_instr.or_opcode(parse_register() << 8);
    parse_comma();
    switch (_tokens[pos].get_type()) {
        default:
            throw ParsingErrorException(_tokens[pos].get_content() + " is not a valid register or byte");
        case Token::reg:
            // 8xy4 - ADD Vx, Vy
            current_instr.or_opcode(0x8004);
            current_instr.or_opcode(parse_register() << 4);
            break;
        case Token::byte:
            // 7xkk - ADD Vx, byte
            current_instr.or_opcode(0x7000);
            current_instr.or_opcode(parse_byte());
            break;
    }
}

void Parser::parse_or() {
    // 8xy1 - OR Vx, Vy
    current_instr.set_opcode(0x8001);
    current_instr.or_opcode(parse_register() << 8);
    parse_comma();
    current_instr.or_opcode(parse_register() << 4);
}

void Parser::parse_and() {
    // 8xy2 - AND Vx, Vy
    current_instr.set_opcode(0x8002);
    current_instr.or_opcode(parse_register() << 8);
    parse_comma();
    current_instr.or_opcode(parse_register() << 4);
}

void Parser::parse_xor() {
    // 8xy3 - XOR Vx, Vy
    current_instr.set_opcode(0x8003);
    current_instr.or_opcode(parse_register() << 8);
    parse_comma();
    current_instr.or_opcode(parse_register() << 4);
}

void Parser::parse_sub() {
    // 8xy5 - SUB Vx, Vy
    current_instr.set_opcode(0x8005);
    current_instr.or_opcode(parse_register() << 8);
    parse_comma();
    current_instr.or_opcode(parse_register() << 4);
}

void Parser::parse_shr() {
    // 8xy6 - SHR Vx
    // (It actually is SHR Vx {, Vy}, but I don't see the second operand being used anywhere)
    // (I'll be simply using SHL Vx for my implementation)
    // TODO: Ensure SHR Vx {, Vy} is compatible as well
    current_instr.set_opcode(0x8006);
    current_instr.or_opcode(parse_register() << 8);
}

void Parser::parse_subn() {
    // 8xy7 - SUB Vx, Vy
    current_instr.set_opcode(0x8007);
    current_instr.or_opcode(parse_register() << 8);
    parse_comma();
    current_instr.or_opcode(parse_register() << 4);
}

void Parser::parse_shl() {
    // 8xyE - SHL Vx
    // (It actually is SHL Vx {, Vy}, same as SHR)
    // TODO: Ensure SHL Vx {, Vy} is compatible as well
    current_instr.set_opcode(0x800E);
    current_instr.or_opcode(parse_register() << 8);
}

void Parser::parse_rnd() {
    // Cxkk - RND Vx, byte
    current_instr.set_opcode(0xC000);
    current_instr.or_opcode(parse_register() << 8);
    parse_comma();
    current_instr.or_opcode(parse_byte());
}

void Parser::parse_drw() {
    // Dxyn - DRW Vx, Vy, nibble
    current_instr.set_opcode(0xD000);
    current_instr.or_opcode(parse_register() << 8);
    parse_comma();
    current_instr.or_opcode(parse_register() << 4);
    parse_comma();
    current_instr.or_opcode(parse_nibble());
}

void Parser::parse_skp() {
    // Ex9E - SKP Vx
    current_instr.set_opcode(0xE09E);
    current_instr.or_opcode(parse_register() << 8);
}

void Parser::parse_sknp() {
    // ExA1 - SKNP Vx
    current_instr.set_opcode(0xE0A1);
    current_instr.or_opcode(parse_register() << 8);
}

void Parser::parse_ld() {
    if (_tokens[pos].get_type() == Token::reg) {
        current_instr.set_opcode(parse_register() << 8);
        parse_comma();
        switch (_tokens[pos].get_type()) {
            default:
                throw ParsingErrorException(
                    _tokens[pos].get_content() +
                    " is not a valid register, byte, DT, K or [I]");
            case Token::reg:
                // 8xy0 - LD Vx, Vy
                current_instr.or_opcode(0x8000);
                current_instr.or_opcode(parse_register() << 4);
                break;
            case Token::byte:
                // 6xkk - LD Vx, byte
                current_instr.or_opcode(0x6000);
                current_instr.or_opcode(parse_byte());
                break;
            case Token::delay_timer:
                // Fx07 - LD Vx, DT
                current_instr.or_opcode(0xF007);
                parse_delay_timer();
                break;
            case Token::key_press:
                // Fx0A - LD Vx, [I]
                current_instr.or_opcode(0xF00A);
                parse_key_press();
                break;
            case Token::bracket_i:
                // Fx65 - LD Vx, DT
                current_instr.or_opcode(0xF065);
                parse_bracket_i();
                break;
        }
        return;
    }
    if (_tokens[pos].get_type() == Token::delay_timer) {
        // Fx15 - LD DT, Vx
        current_instr.set_opcode(0xF015);
        parse_delay_timer();
        parse_comma();
        current_instr.or_opcode(parse_register() << 8);
        return;
    }
    if (_tokens[pos].get_type() == Token::sound_timer) {
        // Fx18 - LD ST, Vx
        current_instr.set_opcode(0xF018);
        parse_sound_timer();
        parse_comma();
        current_instr.or_opcode(parse_register() << 8);
        return;
    }
    if (_tokens[pos].get_type() == Token::i) {
        // Annn - LD I, addr
        current_instr.set_opcode(0xA000);
        parse_i();
        parse_comma();
        current_instr.or_opcode(parse_addr_or_label());
        return;
    }
    if (_tokens[pos].get_type() == Token::f) {
        // Fx29 - LD F, Vx
        current_instr.set_opcode(0xF029);
        parse_f();
        parse_comma();
        current_instr.or_opcode(parse_register() << 8);
        return;
    }
    if (_tokens[pos].get_type() == Token::bcd) {
        // Fx33 - LD B, Vx
        current_instr.set_opcode(0xF033);
        parse_bcd();
        parse_comma();
        current_instr.or_opcode(parse_register() << 8);
        return;
    }
    if (_tokens[pos].get_type() == Token::bracket_i) {
        // Fx55 - LD [I], Vx
        current_instr.set_opcode(0xF055);
        parse_bracket_i();
        parse_comma();
        current_instr.or_opcode(parse_register() << 8);
        return;
    }
    throw ParsingErrorException(
    _tokens[pos].get_content() +
    " is not a valid register, DT, ST, I, F, .BCD or [I]");
}
