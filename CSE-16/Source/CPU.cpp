#include "CPU.h"

#include <chrono>
#include <thread>

void CPU::run(int tickSpeedMS = 0) {
	using namespace std::chrono_literals;

	while (m_Running) {
		tick();

		if (tickSpeedMS > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(tickSpeedMS));
		}
	}
}

void CPU::tick() {

}
