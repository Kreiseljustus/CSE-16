#include "memory.h"

#include <iostream>

uint8_t Memory::Read8(uint16_t addr) {
    if (!VALID_R_MEM_ADDR(addr)) {
        CPPOutErr("Read access violation at " << addr);
        //Maybe set flag in cpu

        return 0;
    }
    return mem[addr];
}

uint16_t Memory::Read16(uint16_t addr) {
    if (!VALID_R_MEM_ADDR(addr + 1)) {
        CPPOutErr("Read access violation at " << addr);
        //Maybe set flag in cpu?
        
        return 0;
    }
    uint8_t lowByte = mem[addr];
    uint8_t highByte = mem[addr + 1];
    return (highByte << 8) | lowByte;
}

void Memory::Write8(uint16_t addr, uint8_t val) {
    if (!VALID_W_MEM_ADDR(addr)) { 
        CPPOutErr("Write access violation at " << addr);

        return;
    }
    mem[addr] = val;
}

void Memory::Write16(uint16_t addr, uint16_t val) {
    if (!VALID_W_MEM_ADDR(addr) && !VALID_W_MEM_ADDR(addr + 1)) {
        CPPOutErr("Write access violation at " << addr);

        return;
    }
    uint8_t lowByte = val & 0xFF;
    uint8_t highByte = val >> 8;

    mem[addr] = lowByte;
    mem[addr + 1] = highByte;
}
