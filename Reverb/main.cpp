// Building reverb project from scratch. Will be working on .wav files for now.

#include <iostream>
#include <chrono>
#include <cstdint>
#include "WaveFileWrapper.h"
#include "CombReverbBlock.h"
#include "DelayBlock.h"
#include "AllpassReverbBlock.h"
#include "AllpassReverbSeries.h"
#include "VariableRatioAllpassReverb.h"

int main()
{
    
    WaveFileWrapper wav = WaveFileWrapper("singing.wav");
	///	
	
	auto start = std::chrono::system_clock::now();
    SoundData *samples = wav.getSoundData();
    VariableRatioAllpassReverb VAP(samples->sample_rate/2, samples->sample_rate/4, 0.1);
    
    for(auto& sample: samples->left_channel)
    {
        sample += VAP.process(sample);
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