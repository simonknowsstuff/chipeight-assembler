#include "../include/tester.h"
#include "../include/parser.h"

Tester::Tester() {
}

void Tester::parse_test_cases() {
    struct TestCase {
        std::string instr;
        uint16_t expected_opcode;
        bool is_valid;
    };

    const std::vector cases = {
        TestCase("SYS 0x300", 0x0300, true),
        TestCase("CLS", 0x00E0, true),
        TestCase("RET", 0x00EE, true),
        TestCase("JP 0x300", 0x1300, true),
        TestCase("CALL 0x300", 0x2300, true),
        TestCase("SE V4, 28", 0x3428, true),
        TestCase("SNE V4, 28", 0x4428, true),
        TestCase("SE V4, V5", 0x5450, true),
        TestCase("LD V4, 28", 0x6428, true),
        TestCase("ADD V4, 28", 0x7428, true),
        TestCase("LD V4, V5", 0x8450, true),
        TestCase("OR V4, V5", 0x8451, true),
        TestCase("AND V4, V5", 0x8452, true),
        TestCase("XOR V4, V5", 0x8453, true),
        TestCase("ADD V4, V5", 0x8454, true),
        TestCase("SUB V4, V5", 0x8455, true),
        TestCase("SHR V4", 0x8406, true),
        TestCase("SUBN V4, V5", 0x8457, true),
        TestCase("SHL V4", 0x840E, true),
        TestCase("SNE V4, V5", 0x9450, true),
        TestCase("LD I, 0x300", 0xA300, true),
        TestCase("JP V0, 0x300", 0xB300, true),
        TestCase("RND V4, 28", 0xC428, true),
        TestCase("DRW V4, V5, 0xF", 0xD45F, true),
        TestCase("SKP V4", 0xE49E, true),
        TestCase("SKNP V4", 0xE4A1, true),
        TestCase("LD V4, DT", 0xF407, true),
        TestCase("LD V4, K", 0xF40A, true),
        TestCase("LD DT, V4", 0xF415, true),
        TestCase("LD ST, V4", 0xF418, true),
        TestCase("ADD I, V4", 0xF41E, true),
        TestCase("LD F, V4", 0xF429, true),
        TestCase("LD .BCD, V4", 0xF433, true),
        TestCase("LD [I], V4", 0xF455, true),
        TestCase("LD V4, [I]", 0xF465, true)
    };

    for (const auto &test_case: cases) {
        auto tokenizer = Tokenizer();
        const auto tokens = tokenizer.tokenize(test_case.instr);
        auto parser = Parser();

        try {
            const auto opcode = parser.parse(tokens);
            if (opcode != test_case.expected_opcode) {
                std::cerr << "ERROR: " << test_case.instr
                        << " failed! (opcode mismatch, expected "
                        << test_case.expected_opcode << " but received "
                        << opcode << ")" << std::endl;
                continue;
            }
        } catch (const ParsingErrorException &e) {
            if (test_case.is_valid) {
                std::cerr << "ERROR: " << test_case.instr
                        << " failed! (valid test case failed)"
                        << std::endl;
                continue;
            }
        }

        std::cout << test_case.instr << " passed!" << std::endl;
    }
}

std::vector<uint16_t> Tester::parse_simple_program() {
    const std::vector<std::string> instructions = {
        "CLS",
        "LD V0, 10",
        "LD F, V0",
        "LD V1, 10",
        "LD V2, 10",
        "DRW V1, V2, 0x5",
        "JP 0x20C"
    };

    std::vector<uint16_t> opcodes = {};

    for (const auto &instr: instructions) {
        auto tokenizer = Tokenizer();
        const auto tokens = tokenizer.tokenize(instr);
        auto parser = Parser();
        opcodes.push_back(parser.parse(tokens));
    }

    return opcodes;
}
