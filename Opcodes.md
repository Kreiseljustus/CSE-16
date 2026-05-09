# Opcodes

## Info
* RIndex -> Register Index from 0 - 5 representing registers A - D, Stack Pointer and Base Pointer
* MAddr -> Memory Address
* Value -> Immediate value known at assembly
* RLocation -> Location in which the "output" of a opcode ends up. Can reference the type of an argument, a register or the opcode has no "output"
* (D) -> Destination
* (S) -> Source

| Mnemonic | Name | Arg1 | Arg2 | RLocation | Description |
|----------|------|------|------|-----------|-------------|
| ADD | ADD | RIndex | RIndex | A | Adds two registers and stores result in A |
| DIV | DIVIDE | RIndex | RIndex | A | Divides two registers and stores result in A |
| INP | INPUT | MAddr | - | Arg1 | Takes input using std::cin and stores result in memory address. This is a blocking operation! |
| JEZ | JUMP EQUALS ZERO | MAddr | - | - | Sets the program counter (instruction pointer) to the memory address when zero flag is set |
| JNZ | JUMP NOT ZERO | MAddr | - | - | Sets the program counter (instruction pointer) to the memory address when zero flag is NOT set |
| LD | LOAD | RIndex | Value | Arg1 | Loads an immediate value into the register |
| LDMEM | LOAD MEMORY | RIndex(D) | MAddr(S) | Arg1 | Loads a value into register from memory address |
| MUL | MULTIPLY | RIndex | RIndex | A | Multiplies two registers and stores result in A |
| OUT | OUTPUT | MAddr | - | - | Prints value at memory address using std::cout |
| STORE | STORE | RIndex(S) | MAddr(D) | Arg2 | Stores a registers value at a memory address |
| SUB | SUBTRACT | RIndex | RIndex | A | Subtracts two registers and stores in A |
| JMP | JUMP | MAddr | - | - | Sets the program counter (instruction pointer) to the memory address |
| LDPTR | LOAD FROM POINTER | RIndex(D) | RIndex(S) | Arg1 | Loads the register with a value retrieved from a memory address thats inside another register |
| STPTR | STORE TO POINTER | RIndex(D) | RIndex(S) | Arg2 | Stores a value from a register into a memory address thats stores in another register| 
| MOV | MOVE | RIndex(D) | RIndex(S) | Arg1 | Moves the value from register two into register one |
| PUSH | PUSH | RIndex | - | Stack | Pushes a register onto the stack |
| POP | POP | RIndex | - | Arg1 | Pops from the stack and stores in register |
| INC | INCREMENT | RIndex | - | Arg1 | Increments a register by 1 |
| DEC | DECREMENT | RIndex | - | Arg1 | Decrements a registers value by 1 |
| HLT | HALT | - | - | - | Halts the CPU |