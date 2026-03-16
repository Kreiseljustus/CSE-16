#include "CMemory.h"

uint8_t Memory::Read8Bit(uint16_t address) const {
	return memory[address];
}

uint16_t Memory::Read16Bit(uint16_t address) const {
	return memory[address] | (memory[address + 1] << 8);
}

void Memory::Write8Bit(uint8_t value, uint16_t address) {
	memory[address] = value;
}

void Memory::Write16Bit(uint16_t value, uint16_t address) {
	memory[address] = value & 0xFF;
	memory[address + 1] = (value >> 8) & 0xFF;
}