#include "FileUtilities.h"
#include <vector>
#include <iostream>

int16_t readS16(std::ifstream& file)
{
	int16_t value{0};
	uint8_t bytes[2]{0};
	file.read(reinterpret_cast<char*>(bytes), 2);
	value = bytes[0] | (bytes[1] << 8);
	return value;
}

void writeS16(std::ofstream& file, int16_t value)
{
	uint8_t bytes[2]{0};

	// extracting the individual bytes from value
	bytes[0] = (value) & 0xFF; //low
	bytes[1] = (value >> 8) & 0xFF; // high

	file.write(reinterpret_cast<char*>(bytes), 2);
}

int32_t readS32(std::ifstream& file)
{
	int32_t value{0};
	uint8_t bytes[4]{0};
	file.read(reinterpret_cast<char*>(bytes), 4);
	value = bytes[3] | (bytes[2] << 8) | (bytes[1] << 16) | (bytes[0] << 24);
	return value;
}

void writeS32(std::ofstream& file, int32_t value)
{
	uint8_t bytes[4]{0};

	// extracting the individual bytes from value
    bytes[3] = (value) & 0xFF; //low
    bytes[2] = (value >> 8) & 0xFF; //low
	bytes[1] = (value >> 16) & 0xFF; //low
	bytes[0] = (value >> 24) & 0xFF; // high

	file.write(reinterpret_cast<char*>(bytes), 4);
}
