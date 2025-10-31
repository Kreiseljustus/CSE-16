#pragma once

#include <cstdint>
#include "Config.h"

#define VALID_W_MEM_ADDR(addr) ((addr > PROGRAM_MEM_SIZE - 1) && (addr < MEMORY_SIZE))
#define VALID_R_MEM_ADDR(addr) ((addr >= 0) && (addr <= MEMORY_SIZE))

class Memory {
public:
	uint8_t mem[MEMORY_SIZE];

	uint8_t Read8(uint16_t addr);
	uint16_t Read16(uint16_t addr);
	void Write8(uint16_t addr, uint8_t val);
	void Write16(uint16_t addr, uint16_t val);
};