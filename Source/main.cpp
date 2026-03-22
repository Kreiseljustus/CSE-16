#include <iostream>

#include "CMemory.h"
#include "CPU.h"
#include "Debug.h"

#include <algorithm>

int main() {
	Memory* memory = new Memory();

	MemoryPrinter printer(*memory);
	CPU* cpu = new CPU(*memory);

    memory->LoadProgram("program.bin");
    CSEDEBUG("First byte: 0x" << std::hex << (int)memory->Read8Bit(0));

	printer.StartSession();

	while (true) {
		while (!cpu->halted) {
			cpu->Step();
			printer.WriteDeltaMemory();
		}

		printer.EndSession();

		std::cout << "Done running program!" << std::endl;
		std::cout << "Load program.bin in current working directory? (You can change the program now)" << std::endl;
		std::cout << "[Warning] The current memory will stay! Only the program memory will be overwritten (starting at adress 0-program size" << std::endl;
		std::cout << "[Warning] If your program is big enough you might overwrite data!" << std::endl;
		std::cout << "[Warning] This will also overwrite the current Memory.bin debug output with this programs actions!!!" << std::endl;

		std::cout << "Y/N (yes/no)" << std::endl;

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

	delete memory;
}