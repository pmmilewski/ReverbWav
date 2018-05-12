// Building reverb project from scratch. Will be working on .wav files for now.

#pragma pack(1)

#include <fstream>
#include <iostream>
#include <vector>

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

struct WaveFile 
{
	WaveHeader header;
	void* data;
};

int16_t ReadS16(std::istream& file)
{
	int16_t value;
	char bytes[2];

	file.read((char*)bytes, 2);
	value = bytes[0] | (bytes[1] << 8);
	return value;
}

void WriteS16(std::ostream& file, int16_t value)
{
	char bytes[2];

	// extracting the individual bytes from value
	bytes[1] = (value) & 0xFF; //high
	bytes[0] = (value >> 8) & 0xFF; // low

	file.write((char*)bytes, 2);
}

WaveFile* ReadFile(const char* filename)
{
	std::fstream fs;
	auto* wave = new WaveFile;
	fs.open(filename, std::fstream::binary | std::fstream::in);
	fs.get((char*)&wave->header, sizeof(WaveHeader));
	std::vector<char> data{0};
	switch (wave->header.BitsPerSample/8)
	{
	case 1:
	{
		char byte;
		auto *data = new std::vector<uint8_t>(0);
		while (fs >> byte)
		{
			data->push_back(byte);
		}
		wave->data = data;
		break;
	}
	case 2:
	{
		auto *data = new std::vector<int16_t>(0);
		auto sample{0};
		while (sample < wave->header.Subchunk2Size/2)
		{
			data->push_back(ReadS16(fs));
			sample++;
		}
		wave->data = data;
		break;
	}
	default:
	{
		std::cout << "Something is wrong with header.";
		break;
	}
	}
	fs.close();
	return wave;
}

void WriteFile(const char* filename, WaveFile* wave)
{
	std::fstream fs;
	fs.open(filename, std::fstream::binary | std::fstream::out);
	fs.write((char*)wave, sizeof(WaveHeader));
	
	
	auto sample{ 0 };
	auto* data = (std::vector<int16_t>*)wave->data;
	while (sample < wave->header.Subchunk2Size / 2)
	{
		WriteS16(fs, (*data)[sample]);
		sample++;
	}
	//fs.write((char*)wave->data, wave->header.Subchunk2Size);
	fs.close();
}

int main()
{
	std::cout << sizeof(WaveHeader) << std::endl;
	WaveFile *wave = ReadFile("singing.wav");	
	WriteFile("out.wav", wave);

	std::cout << wave->header.Subchunk2Size << std::endl;
	std::getchar();

	return 0;
}