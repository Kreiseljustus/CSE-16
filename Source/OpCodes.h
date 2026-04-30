#pragma once

#include <stdint.h>

enum OpCode : uint8_t {
	LD = 0x01,
	ADD,
	SUB,
	MUL,
	DIV,
	JEZ,
	JNZ,
	INP,
	OUT,
	STORE,
	LDMEM,
	JMP,
	LDPTR,
	STPTR,
	MOV,
	PUSH,
	POP,
	INC,
	DEC,

	HLT = 0xFF
};