// Building reverb project from scratch. Will be working on .wav files for now.

#include <fstream>
#include <iostream>
#include <bitset>

struct WaveHeader
{
	unsigned char ChunkID[4]; //big
	int32_t ChunkSize; //little
	unsigned char Format[4]; //big
	unsigned char Subchunk1ID[4]; //big
	int32_t Subchunk1Size; //little
	int16_t AudioFormat; //little
	int16_t NumChannels; //little
	int32_t SampleRate; //little
	int32_t ByteRate; //little
	int16_t BlockAlign; //little
	int16_t BitsPerSample; //little
	unsigned char Subchunk2ID[4]; //big
	int32_t Subchunk2Size; //little
};

int main() 
{
	std::cout << sizeof(WaveHeader) << std::endl;
	std::fstream fs;
	WaveHeader header;
	fs.open("singing.wav", std::fstream::binary | std::fstream::in);

	fs.get((char*)&header, sizeof(WaveHeader));
	fs.close();
	std::cout << header.ChunkID << std::endl;
	std::getchar();

	return 0;
}