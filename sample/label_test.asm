main:
    CLS
    LD V0, 00

loop:
    ADD V0, 01
    SE V0, 10
    JP loop

    CALL finish
    JP main

finish:
    LD V0, 00
    RET