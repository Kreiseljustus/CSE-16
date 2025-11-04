#pragma once

class CPU;

#include "OpCodes.h"

class OpCodeHandler {
public:
	OpCodeHandler(CPU* cpu);

	void handleOpCode(OpCode opcode);

private:
	CPU* cpu;
};