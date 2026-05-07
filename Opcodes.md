# Opcodes

## Info
* RIndex -> Register Index from 0 - 5 representing registers A - D, Stack Pointer and Base Pointer
* MAddr -> Memory Address
* Value -> Immediate value known at assembly
* RLocation -> Location in which the "output" of a opcode ends up. Can reference the type of an argument, a register or the opcode has no "output"

| Name | Arg1 | Arg2 | Mnemonic | RLocation | Description
| ------|------|------| -- |-|-
| ADD | RIndex | RIndex | ADD | A
| DIVIDE | RIndex | RIndex | DIV | A
| INPUT | MAddr | - | INP | Arg1
| JUMP EQUALS ZERO | MAddr | - | JEZ | -
| JUMP NOT ZERO | MAddr | - | JNZ | -
| LOAD | RIndex | Value | LD | Arg1
| LOAD MEMORY | RIndex | MAddr | LDMEM| Arg1
| MULTIPLY | RIndex| RIndex | MUL | A
| OUTPUT | MAddr | - | OUT | -
| STORE | RIndex | MAddr | STORE | Arg2
| SUBSTRACT | RIndex | RIndex | SUB| A
| JUMP | MAddr | - | JMP | -
| LOAD FROM POINTER | RIndex | RIndex | LDPTR | Arg1
| STORE TO POINTER | MAddr | RIndex | STPTR | Arg2
| MOVE | RIndex | RIndex | MOV | Arg1
| PUSH | RIndex | - | PUSH | Stack
| POP | RIndex | - | POP | Arg1
| INCREMENT | RIndex | - | INC | Arg1
| DECREMENT | RIndex | - | DEC | Arg1
| HALT| - | - | HLT | -
