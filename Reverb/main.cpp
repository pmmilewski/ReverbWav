// Building reverb project from scratch. Will be working on .wav files for now.

#include <iostream>
#include <chrono>
#include <cstdint>
#include "WaveFileWrapper.h"
#include "DelayBlock.h"

int main()
{
    
    WaveFileWrapper wav = WaveFileWrapper("tone.wav");
	///	
	
	auto start = std::chrono::system_clock::now();
    SoundData *samples = wav.getSoundData();
    DelayBlock DL(40000);
    
    for(auto& sample: samples->left_channel)
    {
        sample += DL.process(sample);
        sample /= 2.0;
    }
    
    wav.loadSoudData(*samples);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	///
	wav.finishWork("out2.wav");
	std::cout << "Finished! Time elapsed: " << elapsed_seconds.count() << std::endl;
	std::getchar();

	return 0;
}