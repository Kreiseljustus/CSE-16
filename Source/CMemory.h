#pragma once

#include <stdint.h>

#include "Config.h"

class MemoryPrinter;

class Memory {
	friend class MemoryPrinter;
public:
	Memory() = default;

	uint8_t Read8Bit(uint16_t address) const;
	uint16_t Read16Bit(uint16_t address) const;

	//When writing watch out for truncation!!!
	//Values over 255 or 2^16 will overflow!
	void Write8Bit(uint8_t value, uint16_t address);
	void Write16Bit(uint16_t value, uint16_t address);

private:
	uint8_t memory[MAX_MEM]{};
};