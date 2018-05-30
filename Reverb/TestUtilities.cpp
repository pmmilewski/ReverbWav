#include "TestUtilities.h"
#include <cstdint>
// For test purposes, no parameters
SoundData* createImpulseSD()
{
    SoundData* signal = new SoundData;
    
    signal->number_of_channels = 1;
    signal->sample_rate = 44100;
    signal->bitrate = 16;
    
    signal->left_channel.push_back(INT16_MAX);
    signal->left_channel.resize(signal->sample_rate*5, 0);
    
    return signal;
}
