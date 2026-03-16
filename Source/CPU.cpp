#include "CPU.h"

void CPU::Step() {
	OpCode code = FetchNextInstruction();
	uint16_t arg1 = memory.Read16Bit(PC); PC += 2;
	uint16_t arg2 = memory.Read16Bit(PC); PC += 2;

	switch (code) {

	//Adds two registers and stores in A
	//[register index][register index]
	case ADD: {
		uint16_t reg1 = GetRegister(arg1);
		uint16_t reg2 = GetRegister(arg2);
		A = reg1 + reg2;

		flags.zero = (A == 0);
		flags.negative = (A & 0x8000);
		flags.carry = (A < reg1);

		break;
	}
	//Divides two registers and stores in A
	//[register index][register index]
	case DIV: {
		if (GetRegister(arg2) == 0) {
			CSEWARN("Division by zero!");
			flags.zero = true;
			break;
		}
		A = GetRegister(arg1) / GetRegister(arg2);

		setAFlags();
		break;
	}
	//Takes input using std::cin and stores in mem address
	//[mem address][unused]
	case INP: {
		char value;
		std::cin >> value;

		memory.Write16Bit(static_cast<uint16_t>(value), arg1);

		break;
	}
	//Jumps to a memory address when zero flag is true
	//[mem address][unused]
	case JEZ: {
		if (flags.zero) {
			PC = arg1;
		}
		break;
	}
	//Jumps to a memory address when zero flag is false
	//[mem address][unused]
	case JNZ: {
		if (!flags.zero) {
			PC = arg1;
		}
		break;
	}
	//Loads register with value
	//[register index][immediate value]
	case LD: {
		GetRegister(arg1) = arg2;
		break;
	}
	//Loads register with value from a mem address
	//[register index][memory address]
	case LDMEM: {
		GetRegister(arg1) = memory.Read16Bit(arg2);
		break;
	}
	//Multiplies two registers and stores in A
	//[register index][register index]
	case MUL: {
		uint32_t result = GetRegister(arg1) * GetRegister(arg2);

		flags.carry = (result > 0xFFFF);

		A = static_cast<uint16_t>(result);

		setAFlags();

		break;
	}
	//Outputs a memory addresses value in the console interpreted as a ASCII char
	//[mem address][unused]
	case OUT: {

		std::cout << static_cast<char>(memory.Read8Bit(arg1));

		break;
	}
	//Writes a register value into a memory address
	//[register index][memory address]
	case STORE: {
		memory.Write16Bit(GetRegister(arg1), arg2);
		break;
	}
	//Subtracts register1 - register2
	//[register index][register index]
	case SUB: {
		uint16_t reg1 = GetRegister(arg1);
		uint16_t reg2 = GetRegister(arg2);
		A = reg1 - reg2;

		flags.carry = (reg2 > reg1);

		setAFlags();

		break;
	}
	//Stops processing
	//[unused][unused]
	case HLT: {
		halted = true;
		break;
	}
	default:
		CSEWARN("Received unsupported opcode: 0x" << std::hex << static_cast<int>(code) << "!");
	}
}

OpCode CPU::FetchNextInstruction() {
	return static_cast<OpCode>(memory.Read8Bit(PC++));
}

uint16_t& CPU::GetRegister(uint16_t index) {
	switch (index) {
	case 0: return A;
	case 1: return B;
	case 2: return C;
	case 3: return D;
	default:
		CSEWARN("Invalid register index: " << index);
		CSEWARN("Using A as fallback, this might cause unexpected behaviour!");
		return A;
	}
}

void CPU::setAFlags() {
	flags.zero = (A == 0);
	flags.negative = (A & 0x8000);
}
