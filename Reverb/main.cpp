// Building reverb project from scratch. Will be working on .wav files for now.

#include <iostream>
#include <chrono>
#include <cstdint>
#include "WaveFileWrapper.h"
#include "AllpassReverbSeries.h"
#include "CombReverbParallel.h"
#include "DelayBlock.h"

#include "TestUtilities.h"

int main()
{
    
    WaveFileWrapper wav = WaveFileWrapper("singing.wav");
	///	
	
	auto start = std::chrono::system_clock::now();
    SoundData *samples = wav.getSoundData();  

    ///
     AllpassReverbSeries blocks = AllpassReverbSeries();
    int second = samples->sample_rate;
    blocks.addBlock(second/2, 0.9);
    blocks.addBlock(second/4, 0.7);
    blocks.addBlock(second/8, 0.5);
    blocks.addBlock(second/16, 0.3); 
    
     for(auto& sample: samples->left_channel)
    {
        sample = blocks.process(sample);
    } 

    ///
    wav.loadSoudData(*samples);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	///
	wav.finishWork("out.wav");
	std::cout << "Finished! Time elapsed: " << elapsed_seconds.count() << std::endl;
	std::getchar();

	return 0;
}
