#include "OpCodeHandler.h"

#include "CPU.h"

OpCodeHandler::OpCodeHandler(CPU* cpu) : cpu(cpu) {

}

void OpCodeHandler::handleOpCode(OpCode opcode) {

	auto& PC = cpu->getPC();
	auto& memory = cpu->memory;
	auto& Flags = cpu->getFlags();

	switch (opcode) {
	case LDA: {
		uint16_t value = memory.Read16(PC + 1);
		cpu->setA(value);
		PC += 3;
		break;
	}
	case LDB: {
		uint16_t value = memory.Read16(PC + 1);
		cpu->setB(value);
		
		PC += 3;
		break;
	}
	case ADD: {
		uint32_t value = cpu->getA() + cpu->getB();
		uint16_t newValue = value & 0xFFFF;

		bool carry = value > 0xFFFF;

		cpu->setA(newValue);

		if(cpu->getA() == 0) {
			Flags |= 0b00000010;
		}
		else {
			Flags &= ~0b00000010;
		}

		if (carry) {
			Flags |= 0b00000100;
		}
		else {
			Flags &= ~0b00000100;
		}

		PC += 1;
		break;
	} 
	case SUB: {

		bool underflow = cpu->getA() < cpu->getB();

		uint16_t value = cpu->getA() - cpu->getB();

		cpu->setA(value);

		if (cpu->getA() == 0) {
			Flags |= 0b00000010;
		}
		else {
			Flags &= ~0b00000010;
		}

		if (underflow) {
			Flags |= 0b00000100;
		}
		else {
			Flags &= ~0b00000100;
		}

		PC += 1;
		break;
	}
	case OUTV: {
		uint16_t memAddr = memory.Read16(PC + 1);
		uint16_t value = memory.Read16(memAddr);

		std::cout << static_cast<char>(value) << std::flush;

		PC += 3;
		break;
	}
	case STA: {
		uint16_t memAdd = memory.Read16(PC + 1);

		cpu->memory.Write16(memAdd, cpu->getA());

		PC += 3;
		break;
	}
	case LDM: {
		uint16_t memAdd = memory.Read16(PC + 1);

		cpu->setA(memory.Read16(memAdd));

		PC += 3;
		break;
	} 
	case JEZ: {
		uint16_t addr = memory.Read16(PC + 1);

		if (Flags & (1 << 1)) {
			PC = addr;
		}
		else {
			PC += 3;
		}

		break;
	}
	case JNZ: {
		uint16_t addr = memory.Read16(PC + 1);

		if (!(Flags & (1 << 1))) {
			PC = addr;
		}
		else {
			PC += 3;
		}
		break;
	} 
	case MUL: {
		uint32_t result = cpu->getA() * cpu->getB();
		cpu->setA(result & 0xFFFF);

		if (cpu->getA() == 0) Flags |= 0b00000010;
		else Flags &= ~0b00000010;

		if (result > 0xFFFF) Flags |= 0b00000100;
		else Flags &= ~0b00000100;

		PC += 1;
		break;
	}
	case DIV: {
		if (cpu->getB() == 0) {
			Flags |= 0b00001000;
		}
		else {
			Flags &= ~0b00001000;
			uint16_t result = cpu->getA() / cpu->getB();

			if (result == 0) {
				Flags |= 0b00000010;
			}
			else {
				Flags &= ~0b00000010;
			}

			cpu->setA(result);
		}

		PC += 1;
		break;
	}
	case INP: {
		uint16_t addr = memory.Read16(PC + 1);
		uint16_t value;
		std::cin >> value;

		memory.Write16(addr, static_cast<uint16_t>(value));

		PC += 3;
		break;
	} 
	case LD: {
		uint8_t reg = memory.Read8(PC + 1);
		uint16_t addr = memory.Read16(PC + 2);

		if (reg == 1) {
			cpu->setA(memory.Read16(addr));
		}
		else if (reg == 2) {
			cpu->setB(memory.Read16(addr));
		}
		else if (reg == 3) {
			cpu->setC(memory.Read16(addr));
		}
		else if (reg == 4) {
			cpu->setD(memory.Read16(addr));
		}
		else {
			std::cerr << "Invalid register provided for LD " << std::hex << addr << std::endl;
		}

		PC += 4;
		break;
	}
	case HLT:
		cpu->m_Running = false;
		break;
	default:
		std::cout << "ERROR invalid opcode " << opcode << std::endl;
		cpu->m_Running = false;
	}
}
