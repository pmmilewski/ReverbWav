#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

struct WaveHeader
{
	uint8_t ChunkID[4]; //big
	int32_t ChunkSize; //little
	uint8_t Format[4]; //big
	uint8_t Subchunk1ID[4]; //big
	int32_t Subchunk1Size; //little
	int16_t AudioFormat; //little
	int16_t NumChannels; //little
	int32_t SampleRate; //little
	int32_t ByteRate; //little
	int16_t BlockAlign; //little
	int16_t BitsPerSample; //little
	uint8_t Subchunk2ID[4]; //big
	int32_t Subchunk2Size; //little
};

struct WaveFile 
{
	WaveHeader header;
	void* data;
};

int16_t readS16(std::ifstream&);
void writeS16(std::ofstream&, int16_t);
WaveFile* readFile(const char*);
void writeFile(const char*, WaveFile*);

// Sample number manipulation
template <typename T>
void addSamples(WaveFile &wave, const int &n)
{
    auto new_size = wave.header.Subchunk2Size += n*sizeof(T);
    std::vector<T> *data = static_cast<std::vector<T>*>(wave.data);
    data->resize(new_size);
}
