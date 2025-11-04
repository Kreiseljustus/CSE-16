#pragma once

#include <iostream>

//If this is enabled you will get errors from C++ when messing something up
//For example a read access violation when trying to read out of bounds
#define enableCPPOutput true

#define CPPOutErr(str) do { if(enableCPPOutput) {std::cerr << str << std::endl;}} while(0)
#define CPPOut(str) do {if(enableCPPOutput) {std::cerr << str << std::endl;}} while(0)

#define MEMORY_SIZE 512
#define PROGRAM_MEM_SIZE 256