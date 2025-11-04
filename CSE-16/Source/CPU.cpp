#include "CPU.h"

#include <chrono>
#include <thread>

void CPU::run(int tickSpeedMS) {
	using namespace std::chrono_literals;

	opcodeHandler = new OpCodeHandler(this);

	m_Running = true;

	while (m_Running) {
		tick();

		if (tickSpeedMS > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(tickSpeedMS));
		}
	}
}

void CPU::tick() {
	if (!VALID_R_MEM_ADDR(PC)) { m_Running = false; CPPOutErr("PC out of bounds: " << PC); return; }

	OpCode opcode = static_cast<OpCode>(memory.Read8(PC));

	opcodeHandler->handleOpCode(opcode);
}
