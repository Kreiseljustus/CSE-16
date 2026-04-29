#pragma once

#include <string>
#include <fstream>

#include "Config.h"
#include "CMemory.h"
#include "CPU.h"

#define MemSessFormatVersion "1.1"

class MemoryPrinter {
public:
	MemoryPrinter() = delete;
	MemoryPrinter(const Memory& mem, const CPU& cpu) : mem(mem), cpu(cpu), prevMem(new uint8_t[MAX_MEM]) {};
	~MemoryPrinter();

	void StartSession();
	void WriteDeltaMemory();
	void EndSession();
private:
	void writeReg(uint16_t regValue);
private:
	const Memory& mem;
	const CPU& cpu;
	std::ofstream file;

	uint8_t* prevMem;

	int deltaStep{ 0 };
	bool session{ false };
};