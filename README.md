# CSE-16

# General Information

CSE-16 is a 16-Bit version of [CSE1](https://github.com/Kreiseljustus/CSE1) <br>
Basically its a **emulator for a made up little endianness cpu with a made up ISA** to learn about cpus and emulation.

This project contains the **memory and cpu** as well as a debug printer which creates a Memory.bin file in a custom format called [Memory Session](./MemorySessionFormat.md).
This format shows the **registers state** at each cpu cycle as well as all **memory changes** for debugging! <br>

**Memory Session** files can be easily viewed and analyzed using [Memsess Viewer](https://github.com/Kreiseljustus/Memsess-Viewer)

A **very basic assembler** that outputs a program.bin for CSE-16 can be found [here](https://github.com/Kreiseljustus/CSE-16-ASM)! More information about the assembler can be found in its readme<br>

**I highly advise to also clone [Memsess Viewer](https://github.com/Kreiseljustus/Memsess-Viewer) and [the basic Assembler](https://github.com/Kreiseljustus/CSE-16-ASM) and use the [command line arguments](#command-line-arguments) to parse in the assembled programs.**


## Command Line Arguments

| Flag | Argument | Default | Example |
| ---- | ---- | ---- | ---- |
| inputPath | Path to a program.bin | ```%(WorkingDir)program.bin```| ```./CSE-16.exe --inputPath ./Examples/HelloWorld/HelloWorld.bin```

## Config

[Config.h](./Source/Config.h) contains some configuration values for stuff. <br>

While the maximum memory can be changed its basically useless since you cant address more than 2^16 bytes anyway. I might remove that option in the future. <br>
When the enable debug option is disabled the emulator will not generate a Memory Session file and wont write to the console if it receives unsupported opcodes! <br>
The debug and warn macros can be overwritten to log to other locations.

## Registers
There are six **16-Bit** registers. <br>
**Register A is used to store almost all results of mathematical operations like adding, subtracting, dividing etc**

| Register Name | Index | Assembler Mneumonic |
| - | - | - |
A | 0 | A |
B | 1 | B
| C | 2 | C
D | 3 | D
| Stack Pointer | 4 | SP
| Base Pointer | 5 | BP

The **program counter (instruction pointer) is not directly accessible as a register**, it can only be modified through jump and call instructions.
## Opcodes

Opcodes can be viewed in [Opcodes.md](./Opcodes.md)