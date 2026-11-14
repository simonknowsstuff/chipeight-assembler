cmake_minimum_required(VERSION 4.3)
project(chipeight_assembler)

set(CMAKE_CXX_STANDARD 20)

add_executable(chipeight_assembler main.cpp
        src/tokenizer.cpp
        include/tokenizer.h
        include/token.h
        src/parser.cpp
        include/parser.h
        src/translator.cpp
        include/translator.h
#        src/tester.cpp
#        include/tester.h
        src/reader.cpp
        include/reader.h
        include/instruction.h
)
