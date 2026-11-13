#ifndef CHIPEIGHT_ASSEMBLER_TESTER_H
#define CHIPEIGHT_ASSEMBLER_TESTER_H
#include <string>
#include <cstdint>
#include <vector>
#include <iostream>
#include <ostream>
#include "parser.h"
#include "tokenizer.h"

class Tester {
private:

public:
    Tester();

    void parse_test_cases();

    std::vector<uint16_t> parse_simple_program();
};

#endif //CHIPEIGHT_ASSEMBLER_TESTER_H
