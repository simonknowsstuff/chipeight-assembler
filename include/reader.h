#ifndef CHIPEIGHT_ASSEMBLER_READER_H
#define CHIPEIGHT_ASSEMBLER_READER_H
#include <string>
#include <fstream>
#include <optional>

class Reader {
private:
    std::ifstream asm_file;

public:
    Reader(const std::string& filename);

    std::optional<std::string> read_line();
};

#endif //CHIPEIGHT_ASSEMBLER_READER_H
