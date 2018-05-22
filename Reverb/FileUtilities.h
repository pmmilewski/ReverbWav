#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

int16_t readS16(std::ifstream&);
void writeS16(std::ofstream&, int16_t);
    
//int32_t readS24(std::ifstream&);
//void writeS24(std::ofstream&, int32_t);

int32_t readS32(std::ifstream&);
void writeS32(std::ofstream&, int32_t);

