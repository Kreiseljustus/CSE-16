#include "CMemory.h"

#include <vector>
#include <fstream>
#include "Debug.h"

uint8_t Memory::Read8Bit(uint16_t address) const {
	return memory[address];
}

uint16_t Memory::Read16Bit(uint16_t address) const {
	return memory[address] | (memory[address + 1] << 8);
}

void Memory::Write8Bit(uint8_t value, uint16_t address) {
	memory[address] = value;
}

void Memory::Write16Bit(uint16_t value, uint16_t address) {
	memory[address] = value & 0xFF;
	memory[address + 1] = (value >> 8) & 0xFF;
}

void Memory::LoadProgram(const uint8_t* program, uint16_t size, uint16_t offset) {
	if (offset + size > MAX_MEM) {
		CSEWARN("Program exceeds available memory!");
		CSEWARN("Failed to load program!");
		return;
	}

	for (uint16_t i = 0; i < size; i++) {
		memory[offset + i] = program[i];
	}
}

bool Memory::LoadProgram(const char* filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        CSEWARN("Could not open file: " << filePath);
        return false;
    }

    // check magic header
    uint8_t magic[2];
    file.read(reinterpret_cast<char*>(magic), 2);
    if (magic[0] != 0xFE || magic[1] != 0x10) {
        CSEWARN("Invalid magic header! Is this a CSE16 binary?");
        return false;
    }

    // read remaining bytes into memory at offset 0
    std::vector<uint8_t> buffer{
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    };

    LoadProgram(buffer.data(), static_cast<uint16_t>(buffer.size()), 0);

    CSEDEBUG("Loaded " << buffer.size() << " bytes from " << filePath);
    return true;
}
