#include <iostream>

#include "CMemory.h"
#include "Debug.h"

int main() {
	Memory* memory = new Memory();

	MemoryPrinter printer(*memory);
	printer.StartSession();

	memory->Write16Bit(4096, 0);

	printer.WriteDeltaMemory();

	memory->Write8Bit(300, 2);

	printer.WriteDeltaMemory();

	printer.EndSession();

	delete memory;
}