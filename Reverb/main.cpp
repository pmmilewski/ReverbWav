// Building reverb project from scratch. Will be working on .wav files for now.

#include <iostream>
#include <chrono>
#include <cstdint>
#include "WaveFileWrapper.h"
#include "BasicAudioBlocks.h"

int main()
{
    
	//WaveFile *wave = readFile("singing.wav");
    WaveFileWrapper wav = WaveFileWrapper("tone.wav");
	///	
	
	auto start = std::chrono::system_clock::now();
	/*switch (wave->header.BitsPerSample/8)
	{
		case 1:
		{
			DelayBlock<uint8_t> Delay(static_cast<int>(wave->header.SampleRate/5));
			break;
		}
		case 2:
		{
            addSamples<int16_t>(*wave, 2*static_cast<int>(wave->header.SampleRate));
			DelayBlock<int16_t> Delay(static_cast<int>(wave->header.SampleRate));
			std::vector<int16_t> *data = static_cast<std::vector<int16_t>*>(wave->data);
			for (auto &sample: (*data))
			{
				sample += Delay.process(sample);
			}
			break;
		}
		default:
			break;
	}*/
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	///
	wav.finishWork("out.wav");
	std::cout << "Finished! Time elapsed: " << elapsed_seconds.count() << std::endl;
	std::getchar();

	return 0;
}