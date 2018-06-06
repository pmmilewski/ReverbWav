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

#include "TestUtilities.h"

int main()
{
    
    WaveFileWrapper wav = WaveFileWrapper("singing.wav");
	///	
	
	auto start = std::chrono::system_clock::now();
    SoundData *samples = wav.getSoundData();
    
    //wav.loadSoudData(*samples);
    //SoundData* samples = createImpulseSD();
    int initial_size = samples->left_channel.size();
    int closest_2power = static_cast<int>(std::log2(samples->left_channel.size()))+1;
    samples->left_channel.resize(static_cast<int>(pow(2,closest_2power)), 0);

    CArray *fft_result = getCArrayFromSoundDataChannel(samples, 0);
    fft(*fft_result);

    for (size_t i = 0; i < 15; i++)
    {
        std::cout << (*fft_result)[i] << std::endl;
    }

    ifft(*fft_result);
    for (size_t i = 0; i < 15; i++)
    {
        std::cout << (*fft_result)[i] << std::endl;
    } 
    setChannelFromCArray(samples, fft_result, 0);
    samples->left_channel.resize(static_cast<int>(initial_size));
    /*
    AllpassReverbSeries APS(samples->sample_rate/10, 0.7, 5);
    
    for(auto& sample: samples->left_channel)
    {
        sample += APS.process(sample);
    }
    WaveFileWrapper wav = WaveFileWrapper(*samples);
    */
    wav.loadSoudData(*samples);
     for(size_t i = 0; i < 10; i++)
    {
        std::cout << samples->left_channel[i] << std::endl;
        std::cout << (*(std::vector<int16_t>*)(wav.wave->data))[i] << std::endl;
    } 
    wav.finishWork("fft_out.wav");
    ///
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	///
	//wav.finishWork("out.wav");
	std::cout << "Finished! Time elapsed: " << elapsed_seconds.count() << std::endl;
	std::getchar();

	return 0;
}
