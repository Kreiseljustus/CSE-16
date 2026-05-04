#pragma once

#include <stdint.h>

#include "OpCodes.h"
#include "CMemory.h"

class MemoryPrinter;

struct Flags {
	bool zero		= false;
	bool carry		= false;
	bool negative	= false;
};

class CPU {
public:
	CPU(Memory& memory)
		: memory(memory), A(0), B(0), C(0), D(0), PC(0), SP(0xFFFF), BP(0xFFFF) {}

	void Step();

public:
	bool halted = false;
private:
	OpCode FetchNextInstruction();
	
	uint16_t& GetRegister(uint16_t index);

	void setAFlags();
private:
	uint16_t A, B, C, D;
	uint16_t PC;
	uint16_t SP;
	uint16_t BP;

	Flags flags;

	Memory& memory;

	friend class MemoryPrinter;
};