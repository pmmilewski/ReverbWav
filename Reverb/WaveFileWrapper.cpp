#include "WaveFileWrapper.h"

void WaveFileWrapper::readFile(const char* filename)
{
	std::ifstream fs;
	wave = new WaveFile;
	fs.open(filename, std::ios_base::binary);
	fs.get(reinterpret_cast<char*>(&wave->header), sizeof(WaveHeader));
    int bps = static_cast<int>(wave->header.BitsPerSample);
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
    
    int bps = static_cast<int>(wave->header.BitsPerSample);
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
}
WaveFileWrapper::finishWork(const char* filename)
{
    writeFile(filename);
}
