// Building reverb project from scratch. Will be working on .wav files for now.

#include <iostream>
#include "FileUtilities.h"

int main()
{
	std::cout << sizeof(WaveHeader) << std::endl;
	WaveFile *wave = ReadFile("singing.wav");	
	WriteFile("out.wav", wave);

	std::cout << wave->header.Subchunk2Size << std::endl;
	std::getchar();

	return 0;
}