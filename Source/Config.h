#pragma once

#include <iostream>

#define MAX_MEM (1<<16) // 2^16

#define ENABLE_DEBUG true

#define DEBUG_WRITE_PATH "Memory.bin"
#define CSEDEBUG(str) if (ENABLE_DEBUG) do {std::cout << "[DEBUG] " << str << "\n";} while(0)
#define CSEWARN(str) if (ENABLE_DEBUG) do {std::cout << "[WARN] " << str << "\n";} while(0)