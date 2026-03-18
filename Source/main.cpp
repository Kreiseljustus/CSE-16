#include <iostream>

#include "CMemory.h"
#include "CPU.h"
#include "Debug.h"

int main() {
	Memory* memory = new Memory();

	MemoryPrinter printer(*memory);
	CPU cpu(*memory);

    memory->LoadProgram("program.bin");
    CSEDEBUG("First byte: 0x" << std::hex << (int)memory->Read8Bit(0));

	printer.StartSession();

	while (!cpu.halted) {
		cpu.Step();
		printer.WriteDeltaMemory();
	}

	printer.EndSession();

	delete memory;
}