cmake_minimum_required(VERSION 4.3)
project(chipeight_assembler)

set(CMAKE_CXX_STANDARD 20)

add_executable(chipeight_assembler main.cpp
        tokenizer.cpp
        tokenizer.h
        token.h
        parser.cpp
        parser.h
        translator.cpp
        translator.h
)
