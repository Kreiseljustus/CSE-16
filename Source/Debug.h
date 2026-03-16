#pragma once

#include <string>
#include <fstream>

#include "Config.h"
#include "CMemory.h"


class MemoryPrinter {
public:
	MemoryPrinter() = delete;
	MemoryPrinter(const Memory& mem) : mem(mem), prevMem(new uint8_t[MAX_MEM]) {};
	~MemoryPrinter();

	void StartSession();
	void WriteDeltaMemory();
	void EndSession();
private:
	const Memory& mem;
	std::ofstream file;

	uint8_t* prevMem;

	int deltaStep{ 0 };
	bool session{ false };
};