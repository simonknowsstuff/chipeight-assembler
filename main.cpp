#include "include/tokenizer.h"
#include "include/tester.h"
#include "include/parser.h"
#include "include/translator.h"
#include "include/reader.h"
#include "include/token.h"

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        throw std::runtime_error("ASM path and/or ROM path not specified!");
    }

    // argv[1] = ASM path, argv[2] = ROM path
    auto reader = Reader(argv[1]);
    auto tokenizer = Tokenizer();
    auto translator = Translator();
    while (auto line = reader.read_line()) {
        std::vector<Token> tokens = tokenizer.tokenize(*line);
        auto parser = Parser(tokens);
        uint16_t parsed_opcode = parser.parse();
        std::cout << parsed_opcode << std::endl;
        translator.add_opcode(parsed_opcode);
    }
    translator.translate_to_file(argv[2]);

    return 0;
}
