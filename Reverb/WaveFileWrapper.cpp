#include "WaveFileWrapper.h"

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
                auto* data = (std::vector<uint8_t>*)wave->data;
                delete data;
                data = new std::vector<uint8_t>(sdata.left_channel.begin(), sdata.left_channel.end());
            }
            if(bps == 16)
            {
                auto* data = (std::vector<int16_t>*)wave->data;
                delete data;
                data = new std::vector<int16_t>(sdata.left_channel.begin(), sdata.left_channel.end());
                //sdata->left_channel = std::vector<double>(data->begin(), data->end());
            }
            if(bps == 24)
            {
                //TODO
            }
            if(bps == 32)
            {
                auto* data = (std::vector<int32_t>*)wave->data;
                delete data;
                data = new std::vector<int32_t>(sdata.left_channel.begin(), sdata.left_channel.end());
                //sdata->left_channel = std::vector<double>(data->begin(), data->end());
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

