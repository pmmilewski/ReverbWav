// Building reverb project from scratch. Will be working on .wav files for now.

#include <iostream>
#include <chrono>
#include <cstdint>
#include "WaveFileWrapper.h"
#include "BasicAudioBlocks.h"

int main()
{
    
    WaveFileWrapper wav = WaveFileWrapper("singing.wav");
	///	
	
	auto start = std::chrono::system_clock::now();
    SoundData *samples = wav.getSoundData();
    
    for(auto& sample: samples->left_channel)
    {
        sample = sample * 0.1;
    }
    
    wav.loadSoudData(*samples);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	///
	wav.finishWork("out.wav");
	std::cout << "Finished! Time elapsed: " << elapsed_seconds.count() << std::endl;
	std::getchar();

	return 0;
}