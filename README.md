# CHIP-8 assembler
This personal project aims to recreate a CHIP-8 assembler in C++ without the use of any LLM tools.
The goal for me by the end of the project is to:
- Understand how assemblers work
- Spark an interest in compiler design

I would call this an extension of my [CHIP-8 emulator](https://github.com/simonknowsstuff/chipeight) project.

## Background
I'm interested in emulators and how they work. I built a CHIP-8 emulator, so naturally assemblers and compilers seemed
to be an interesting domain to tackle.

## What works so far
- [x] Tokenizing statements
- [x] Converting instructions to opcodes
- [ ] Read a file with instructions
- [ ] Label support

## References used
- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#Cxkk
- https://chip8.hexdocs.pm/readme.html
- https://www.geeksforgeeks.org/compiler-design/recursive-descent-parser/

Special thanks to [Technohacker](https://github.com/Technohacker) (again) for guiding me through this project!