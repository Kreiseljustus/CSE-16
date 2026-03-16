#pragma once

#include <cstdint>

#include <vector>

#include "memory.h"
#include "OpCodeHandler.h"

class CPU {

	friend class OpCodeHandler;

public:
	void run(int tickSpeedMS = 0);

	uint16_t getA() const { return A; }
	uint16_t getB() const { return B; }
	uint16_t getC() const { return C; }
	uint16_t getD() const { return D; }

	void setA(uint16_t value) { A = value; }
	void setB(uint16_t value) { B = value; }
	void setC(uint16_t value) { C = value; }
	void setD(uint16_t value) { D = value; }

	uint16_t& getPC() { return PC; }
	uint8_t& getFlags() { return Flags; }

	Memory& getMemory() { return memory; }

	std::vector<uint8_t> convertCSE1ProgramTo16Bit(const std::vector<uint8_t>& oldProgram) {
		std::vector<uint8_t> newProgram;
		for (size_t i = 0; i < oldProgram.size(); i++) {
			uint8_t opcode = oldProgram[i];

			if (opcode == LDA || opcode == LDB || opcode == STA || opcode == OUTV ||
				opcode == JEZ || opcode == JNZ || opcode == INP || opcode == LDM) {
				newProgram.push_back(opcode);
				newProgram.push_back(oldProgram[i + 1]); // low byte
				newProgram.push_back(0x00);              // high byte
				i += 1;
			}
			else if (opcode == LD) {
				newProgram.push_back(opcode);
				newProgram.push_back(oldProgram[i + 1]); // reg
				newProgram.push_back(oldProgram[i + 2]); // low
				newProgram.push_back(0x00);              // high
				i += 2;
			}
			else {
				newProgram.push_back(opcode);
			}
		}
		return newProgram;
	}

	void loadProgram(const std::vector<uint8_t>& program) {

		if (!VALID_R_MEM_ADDR(program.size() - 1) && enableCPPOutput) {
			CPPOutErr("Program size is too big!");
			return;
		}

		//skip the 2-byte header
		size_t offset = 2;

		bool is8Bit = program.size() > 1 && program[0] == 0xFE && program[1] == 0x08;

		if (is8Bit) {
			CPPOut("Program is 8-Bit");
			std::vector<uint8_t> programCopy(program.begin() + offset, program.end());

			std::vector<uint8_t> newProgram = convertCSE1ProgramTo16Bit(programCopy);

			for (size_t i = 0; i < newProgram.size(); i++) {
				memory.mem[i] = newProgram[i];
			}
		}
		else {
			CPPOut("Program is 16-Bit. Size = " << program.size());
			for (size_t i = offset; i < program.size(); i++) {
				memory.mem[i - offset] = program[i];
			}
		}

		PC = 0;
	}
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
	uint8_t Flags = 0;

	Memory memory;
	OpCodeHandler* opcodeHandler;

	void tick();
};