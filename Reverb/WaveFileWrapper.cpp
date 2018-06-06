#include "WaveFileWrapper.h"
#include <bitset>
#include <cmath>


void WaveFileWrapper::readFile(const char* filename)
{
	std::ifstream fs;
	wave = new WaveFile;
	fs.open(filename, std::ios_base::binary);
	fs.get(reinterpret_cast<char*>(&wave->header), sizeof(WaveHeader));
    bps = static_cast<int>(wave->header.BitsPerSample);
    if(bps == 8)
        readSamplesFromFile<8>(fs);
    if(bps == 16)
        readSamplesFromFile<16>(fs);
    if(bps == 24)
        readSamplesFromFile<24>(fs);
    if(bps == 32)
        readSamplesFromFile<32>(fs);
	fs.close();
}

void WaveFileWrapper::writeFile(const char* filename)
{
	std::ofstream fs;
	fs.open(filename, std::ios_base::binary);
	fs.write((char*)wave, sizeof(WaveHeader));
    
    if(bps == 8)
        writeSamplesToFile<8>(fs);
    if(bps == 16)
        writeSamplesToFile<16>(fs);
    if(bps == 24)
        writeSamplesToFile<24>(fs);
    if(bps == 32)
        writeSamplesToFile<32>(fs);
	fs.close();
}
WaveFileWrapper::WaveFileWrapper(const char* filename)
{
    readFile(filename);
    // Need to consider additional init operations
    number_of_channels = static_cast<int>(wave->header.NumChannels);
    block_align = static_cast<int>(wave->header.BlockAlign);
    sample_rate = static_cast<int>(wave->header.SampleRate);
}

void WaveFileWrapper::finishWork(const char* filename)
{
    writeFile(filename);
}

SoundData* WaveFileWrapper::getSoundData()
{
    SoundData *sdata = new SoundData{0};
    sdata->number_of_channels = number_of_channels;
    sdata->sample_rate = sample_rate;
    sdata->bitrate = bps;
    
    switch(number_of_channels)
    {
        case 1:
        {
            if(bps == 8)
            {
                auto* data = (std::vector<uint8_t>*)wave->data;
                sdata->left_channel = std::vector<double>(data->begin(), data->end());
            }
            if(bps == 16)
            {
                auto* data = (std::vector<int16_t>*)wave->data;
                sdata->left_channel = std::vector<double>(data->begin(), data->end());
            }
            if(bps == 24)
            {
                //TODO
            }
            if(bps == 32)
            {
                auto* data = (std::vector<int32_t>*)wave->data;
                sdata->left_channel = std::vector<double>(data->begin(), data->end());
            }
            break;
        }
        case 2:
        {
            //TODO
            std::cout << "Not yet implemented - getSound stereo" << std::endl;
            break;
        }
        default:
        {
            std::cout << "Something is not right with number of channels in getSoundData()" << std::endl;
        }
    }
   
    return sdata;
        
}

void WaveFileWrapper::loadSoudData(const SoundData& sdata)
{
    switch(number_of_channels)
    {
        case 1:
        {
            if(bps == 8)
            {
               delete static_cast<std::vector<uint8_t>*>(wave->data);
               wave->data = new std::vector<uint8_t>(sdata.left_channel.begin(), sdata.left_channel.end());
            }
            if(bps == 16)
            {
                delete static_cast<std::vector<int16_t>*>(wave->data);
                wave->data = new std::vector<int16_t>(sdata.left_channel.begin(), sdata.left_channel.end());
            }
            if(bps == 24)
            {
                //TODO
            }
            if(bps == 32)
            {
                delete static_cast<std::vector<int32_t>*>(wave->data);
                wave->data = new std::vector<int32_t>(sdata.left_channel.begin(), sdata.left_channel.end());
            }
            break;
        }
        case 2:
        {
            //TODO
            std::cout << "Not yet implemented - getSound stereo" << std::endl;
            break;
        }
        default:
        {
            std::cout << "Something is not right with number of channels in getSoundData()" << std::endl;
        }
    }
}
WaveFileWrapper::WaveFileWrapper(const SoundData& sdata)
{
    wave = new WaveFile;
    
    sample_rate = sdata.sample_rate;
    number_of_channels = sdata.number_of_channels;
    bps = sdata.bitrate;
    block_align = number_of_channels * bps/8;
    
    wave->header.ChunkID[0] = 'R';
    wave->header.ChunkID[1] = 'I';
    wave->header.ChunkID[2] = 'F';
    wave->header.ChunkID[3] = 'F';
    wave->header.Format[0] = 'W';
    wave->header.Format[1] = 'A';
    wave->header.Format[2] = 'V';
    wave->header.Format[3] = 'E';
    wave->header.Subchunk1ID[0] = 'f';
    wave->header.Subchunk1ID[1] = 'm';
    wave->header.Subchunk1ID[2] = 't';
    wave->header.Subchunk1ID[3] = ' ';
    wave->header.Subchunk1Size = 16; 
    wave->header.AudioFormat = 1; 
    wave->header.NumChannels = sdata.number_of_channels; 
    wave->header.SampleRate = sdata.sample_rate;
    wave->header.BitsPerSample = sdata.bitrate;
    wave->header.BlockAlign = wave->header.NumChannels * wave->header.BitsPerSample/8;
    wave->header.ByteRate = wave->header.SampleRate * wave->header.NumChannels * wave->header.BitsPerSample/8;
    wave->header.Subchunk2ID[0] = 'd';
    wave->header.Subchunk2ID[1] = 'a';
    wave->header.Subchunk2ID[2] = 't';
    wave->header.Subchunk2ID[3] = 'a';
    wave->header.Subchunk2Size = sdata.left_channel.size()*(sdata.bitrate/8);
    wave->header.ChunkSize = 4 + (8 + wave->header.Subchunk1Size) + (8 + wave->header.Subchunk2Size);
    
    wave->data = new std::vector<int16_t>(sdata.left_channel.begin(), sdata.left_channel.end());
    
}
