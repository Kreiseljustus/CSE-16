#include "Debug.h"

MemoryPrinter::~MemoryPrinter() {
	if (session) EndSession();
	delete[] prevMem;
}

void MemoryPrinter::StartSession() {
	file = std::ofstream(DEBUG_WRITE_PATH, std::ios::binary | std::ios::out);
	file.write("sessionstart", 12);
	file.write(MemSessFormatVersion, sizeof(MemSessFormatVersion));
	file.write(reinterpret_cast<const char*>(mem.memory), MAX_MEM);
	std::memcpy(prevMem, mem.memory, MAX_MEM);
	deltaStep = 0;

	session = true;
}

void MemoryPrinter::WriteDeltaMemory() {
	if (!session) { CSEWARN("Tried to write delta memory without an ongoing session! Use MemoryPrinter::StartSession()"); return; }
	bool writtenStep = false;

	for (int i = 0; i < MAX_MEM; i++) {
		if (mem.memory[i] != prevMem[i]) {
			if (!writtenStep) {
				file.write("STEP", 4);
				file.write(reinterpret_cast<const char*>(&deltaStep), sizeof(deltaStep));
				writtenStep = true;
			}

			file.write(reinterpret_cast<const char*>(&i), sizeof(i));
			file.write(reinterpret_cast<const char*>(&mem.memory[i]), 1);

			prevMem[i] = mem.memory[i];
		}
	}

	writeReg(cpu.A);
	writeReg(cpu.B);
	writeReg(cpu.C);
	writeReg(cpu.D);

	file.write("ST", 2);
	file.write(reinterpret_cast<const char*>(&cpu.SP), sizeof(cpu.SP));

	file.write("PC", 2);
	file.write(reinterpret_cast<const char*>(&cpu.PC), sizeof(cpu.PC));

	deltaStep++;
}

void MemoryPrinter::EndSession() {
	file.write("sessionend", 10);
	file.close();

	session = false;
}

void MemoryPrinter::writeReg(uint16_t regValue) {
	file.write("REG", 3);
	file.write(reinterpret_cast<const char*>(&regValue), sizeof(regValue));
}
