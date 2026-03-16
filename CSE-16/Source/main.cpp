#include <iostream>

#include "CPU.h"

#include "OpCodes.h"

int main() {
	CPU* cpu = new CPU();

    std::vector<uint8_t> program = {
    0xFE, 0x16,
	LDA, 0x07, 0x00,
	LDB, 0x30, 0x00,
	ADD,
	STA, 0xF0, 0xFF,
	OUTV, 0xF0, 0xFF,
	HLT
    };

	cpu->loadProgram(program);

	cpu->run();
}