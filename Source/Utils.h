#pragma once

#include <iostream>

void printProgramHelp() {
	std::cout << "Done running program!" << std::endl;
	std::cout << "Load program.bin in current working directory? (You can change the program now)" << std::endl;
	std::cout << "[Warning] The current memory will stay! Only the program memory will be overwritten (starting at adress 0 to program size" << std::endl;
	std::cout << "[Warning] If your program is big enough you might overwrite data!" << std::endl;
	std::cout << "[Warning] This will also overwrite the current Memory.bin debug output with this programs actions!!!" << std::endl;

	std::cout << "Y/N (yes/no)" << std::endl;
}