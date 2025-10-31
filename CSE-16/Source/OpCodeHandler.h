#pragma once

#include "memory.h"

class OpCodeHandler {
public:
	OpCodeHandler(Memory& memory);

	void handleOpCode();

private:
	Memory& memory;
};