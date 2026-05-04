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
		CSEDEBUG("OUT reading from address: 0x" << std::hex << arg1);
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
	//Jumps to a memory address and continues execution there
	//[memory address][unused]
	case JMP: {
		PC = arg1;

		break;
	}
	//Loads a registers with a value from a memory address thats stored in another register
	//Example:
	//LD B 0x1000
	//LDPTR A B ; A = memory[0x1000]
	//DESTINATION [register index] SOURCE [register index (mem address)]
	case LDPTR: {
		uint16_t addr = GetRegister(arg2);
		GetRegister(arg1) = memory.Read16Bit(addr);
		break;
	}
	//Stores a value from a register into a memory address thats stored in another register
	//Example:
	//LD B 0x1000
	//LD A 42
	//STPTR B A ; memory[0x1000] = 42
	//DESTINATION [register index (mem address)] VALUE [register index]
	case STPTR: {
		uint16_t addr = GetRegister(arg1);
		memory.Write16Bit(GetRegister(arg2), addr);
		break;
	}
	//Copies a registers value into another
	//DESTINATION [register index] SOURCE [register index]
	case MOV: {
		GetRegister(arg1) = GetRegister(arg2);
		break;
	}
	//Pushes a register to the stack
	//[register index][unused]
	case PUSH: {
		memory.Write16Bit(GetRegister(arg1), SP);
		SP -= 2;
		break;
	}
	//Pops the top value of the stack into a register
	//[register index]
	case POP: {
		SP += 2;
		GetRegister(arg1) = memory.Read16Bit(SP);
		break;
	}
	//Increments the value in the register by one
	//[register index]
	case INC: {
		GetRegister(arg1) += 1;
		break;
	}
	//Decrements the value in the register by one
	//[register index]
	case DEC: {
		GetRegister(arg1) -= 1;
		break;
	}
	//Shifts a register bitwise to the left
	//[register index]
	case SHL: {
		GetRegister(arg1) = GetRegister(arg1) << 1;
		break;
	}
	//Shifts a register bitwise to the right
	//[register index]
	case SHR: {
		GetRegister(arg1) = GetRegister(arg1) >> 1;
		break;
	}
	//Bitwise NOT
	//[register index]
	case NOT: {
		GetRegister(arg1) = ~GetRegister(arg1);
		break;
	}
	//Bitwise XOR, ST in A
	//[register index][register index]
	case XOR: {
		A = GetRegister(arg1) ^ GetRegister(arg2);
		break;
	}
	//Bitwise OR, ST in A
	//[register index][register index]
	case OR: {
		A = GetRegister(arg1) | GetRegister(arg2);
		break;
	}
	//Bitwise AND, ST in A
	//[register index][register index]
	case AND: {
		A = GetRegister(arg1) & GetRegister(arg2);
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

/*
	Returns a reference to the register based on index
	A = 0
	B = 1
	C = 2
	D = 3
	SP = 4
	BP = 5
*/
uint16_t& CPU::GetRegister(uint16_t index) {
	switch (index) {
	case 0: return A;
	case 1: return B;
	case 2: return C;
	case 3: return D;
	case 4: return SP;
	case 5: return BP;
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
