#pragma once

#include <cstdint>
#include "Config.h"

#define VALID_W_MEM_ADDR(addr) ((addr) >= (PROGRAM_MEM_SIZE) && (addr) < (MEMORY_SIZE))
#define VALID_R_MEM_ADDR(addr) ((addr) < (MEMORY_SIZE))

class Memory {
public:
	Memory() { std::memset(mem, 0, sizeof(mem)); }

	uint8_t mem[MEMORY_SIZE];

	uint8_t Read8(uint16_t addr);
	uint16_t Read16(uint16_t addr);
	void Write8(uint16_t addr, uint8_t val);
	void Write16(uint16_t addr, uint16_t val);
};