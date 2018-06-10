#include <iostream>
#include <chrono>
#include <filesystem>
#include <string>
#include "WaveFileWrapper.h"
#include "DelayBlock.h"

namespace fs = std::filesystem;

void runFileTest()
{
    auto start = std::chrono::system_clock::now();

    std::string path = "TestInputFiles/";
    for (auto & p : fs::directory_iterator(path))
    {
        std::cout << "Processing file: " << p << std::endl;;
        WaveFileWrapper wav = WaveFileWrapper(p.path().string().c_str());
        SoundData *samples = wav.getSoundData();
        wav.loadSoudData(*samples);
        delete samples;
        std::string output_path = std::string("TestOutputFiles/") + p.path().filename().string();
        wav.finishWork(output_path.c_str());
        std::cout << "============================" << std::endl; 
    }
        

    auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Finished! Time elapsed: " << elapsed_seconds.count() << std::endl;
	std::getchar();
}

void runDelayTest()
{
    auto start = std::chrono::system_clock::now();

    std::string path = "TestInputFiles/";
    for (auto & p : fs::directory_iterator(path))
    {
        std::cout << "Processing file: " << p << std::endl;;
        WaveFileWrapper wav = WaveFileWrapper(p.path().string().c_str());
        SoundData *samples = wav.getSoundData();
        int second = samples->sample_rate;
        DelayBlock blocks(second);

        for (auto &sample : samples->left_channel)
        {
            sample += blocks.process(sample);
        }
        for (auto &sample : samples->right_channel)
        {
            sample += blocks.process(sample);
        }

        wav.loadSoudData(*samples);
        delete samples;
        std::string output_path = std::string("TestOutputFiles/") + std::string("Delay") + p.path().filename().string();
        wav.finishWork(output_path.c_str());
        std::cout << "============================" << std::endl; 
    }
        

    auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Finished! Time elapsed: " << elapsed_seconds.count() << std::endl;
	std::getchar();
}

