#pragma once

//This includes old opcodes from CSE1 to allow backwards compatibility
enum OpCode {
    LDA = 0x01, //Load a value into register A
    LDB = 0x02, //Load a value into register B
    ADD = 0x03, //Adds A + B registers and stores in A
    SUB = 0x04, //Subtracts A - B registers and stores in A
    OUTV = 0x05, //Output a value. Arg1: memory adress to value
    STA = 0x06, //Store A into memory. Arg1: memory adress to store
    LDM = 0x07, //Load A from memory. Arg1: memory adress to load
    JEZ = 0x08, //Jump when zero flag is set to 1. Arg1: memory adress to jump to
    JNZ = 0x09, //Jump when zero flag is set to 0. Arg1: memory adress to jump to
    MUL = 0x0A, //Multiply A * B and stores in A
    DIV = 0x0B, //Divide A / B and stores in A
    INP = 0x0C, //Takes input and stores in memory adress. Arg1: memory adress to store
    LD = 0x0D, //Load a register with a value from a memory adress. Arg1: register (0x01 = A, 0x02 = B), Arg2: memory adress to load

    HLT = 0xFF //Stops the cpu
};
