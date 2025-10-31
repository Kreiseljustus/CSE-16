#pragma once

#include <cstdint>

#include <vector>

#include "memory.h"

class CPU {
public:
	void run(int tickSpeedMS);
private:

	bool m_Running = false;

	//4 16 bit registers
	uint16_t A = 0;
	uint16_t B = 0;
	uint16_t C = 0;
	uint16_t D = 0;

	uint16_t PC = 0;

	//First bit = Invalid adress provided
	//Second bit = Previous math operation is 0
	//Third bit = Carry flag (unsigned overflow)
	//Fourth bit = Divide by Zero
	//Fith bit = Unused
	//Sixth bit = Unused
	//Seventh bit = Unused
	//Eighth bit = Unused
	uint16_t Flags = 0;

	Memory memory;

	void tick();

	void loadProgram(const std::vector<uint8_t>& program) {

		if (!VALID_R_MEM_ADDR(program.size() - 1) && enableCPPOutput) {
			CPPOutErr("Program size is to big!");
			return;
		}

		for (size_t i = 0; i < program.size(); i++) {
			memory.mem[i] = program[i];
		}

		PC = 0;
	}
};