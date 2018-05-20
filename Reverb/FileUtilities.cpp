#include "FileUtilities.h"
#include <vector>
#include <iostream>

int16_t ReadS16(std::ifstream& file)
{
	int16_t value{0};
	uint8_t bytes[2]{0};
	file.read(reinterpret_cast<char*>(bytes), 2);
	value = bytes[1] | (bytes[0] << 8);
	return value;
}

void WriteS16(std::ofstream& file, int16_t value)
{
	uint8_t bytes[2]{0};

	// extracting the individual bytes from value
	bytes[1] = (value) & 0xFF; //low
	bytes[0] = (value >> 8) & 0xFF; // high

	file.write(reinterpret_cast<char*>(bytes), 2);
}

WaveFile* ReadFile(const char* filename)
{
	std::ifstream fs;
	auto* wave = new WaveFile;
	fs.open(filename, std::ios_base::binary);
	fs.get(reinterpret_cast<char*>(&wave->header), sizeof(WaveHeader));
	switch (wave->header.BitsPerSample/8)
	{
	case 1:
	{
		uint8_t byte;
		auto *data = new std::vector<uint8_t>(0);
		auto sample{0};
		while (sample < wave->header.Subchunk2Size)
		{
			fs.seekg(sizeof(WaveHeader)+sample);
			fs.read(reinterpret_cast<char*>(&byte), 1);
			data->push_back(byte);
			sample++;
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
			fs.seekg(sizeof(WaveHeader)+(sample*2));
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
	std::ofstream fs;
	fs.open(filename, std::ios_base::binary);
	fs.write((char*)wave, sizeof(WaveHeader));
	
	
	auto sample{ 0 };
	switch (wave->header.BitsPerSample/8)
	{
		case 1:
		{
			auto* data = (std::vector<uint8_t>*)wave->data;
			while (sample < wave->header.Subchunk2Size)
			{
				fs.write(reinterpret_cast<char*>(&(*data)[sample]), 1);
				sample++;
			}
			break;
		}
		case 2:
		{
			auto* data = (std::vector<int16_t>*)wave->data;
			while (sample < wave->header.Subchunk2Size / 2)
			{
				WriteS16(fs, (*data)[sample]);
				sample++;
			}
			break;
		}
		default:
			break;
	}

	
	fs.close();
}