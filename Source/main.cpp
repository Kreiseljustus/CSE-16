#include <iostream>
#include <algorithm>

#include "CMemory.h"
#include "CPU.h"
#include "Debug.h"

#include "Utils.h"

std::string programPath;

int main(int argc, char* argv[]) {
	for (int index = 0; index < argc; index++) {
		if (strcmp(argv[index], "--inputPath") == 0) {
			if (index + 1 < argc) {
				programPath = argv[index + 1];
			}
		}
	}

	if (programPath.empty()) programPath = "program.bin";

	Memory* memory = new Memory();

	CPU* cpu = new CPU(*memory);
	MemoryPrinter printer(*memory, *cpu);

	if (!memory->LoadProgram(programPath.c_str())) {
		CSEWARN("Failed to open program!");
		return -1;
	}
    CSEDEBUG("First byte: 0x" << std::hex << (int)memory->Read8Bit(0));

	printer.StartSession();

	printer.WriteDeltaMemory();

	while (true) {
		while (!cpu->halted) {
			cpu->Step();
			printer.WriteDeltaMemory();
		}

		printer.EndSession();

		printProgramHelp();

		std::string answer;
		std::cin >> answer;

		std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

		if (answer == "y" || answer == "yes") {
			answer.clear();

			std::cout << "Do you want to reset the memory before running a new program?" << std::endl;
			std::cout << "Y/N (yes/no)" << std::endl;

			std::cin >> answer;

			std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

			if (answer == "y" || answer == "yes") {
				delete memory;

				memory = new Memory();
			}

			memory->LoadProgram("program.bin");

			printer.StartSession();
			delete cpu;

			cpu = new CPU(*memory);
		}
		else if (answer == "n" || answer == "no") {
			break;
		}
		else {
			std::cout << "Y/N (yes/no)" << std::endl;
		}
	}

	delete cpu;
	delete memory;
}