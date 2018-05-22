#include "FileUtilities.h"
#include <iostream>

class WaveFileWrapper
{
public:
    WaveFileWrapper(const char* filename);
    finishWork(const char*);
    
private:
    struct WaveHeader
    {
        uint8_t ChunkID[4]; //big
        int32_t ChunkSize; //little
        uint8_t Format[4]; //big
        uint8_t Subchunk1ID[4]; //big
        int32_t Subchunk1Size; //little
        int16_t AudioFormat; //little
        int16_t NumChannels; //little
        int32_t SampleRate; //little
        int32_t ByteRate; //little
        int16_t BlockAlign; //little
        int16_t BitsPerSample; //little
        uint8_t Subchunk2ID[4]; //big
        int32_t Subchunk2Size; //little
    };

    struct WaveFile 
    {
        WaveHeader header;
        void* data;
    };
    
    WaveFile* wave;
    int block_align;
    int number_of_channels;
    int bps;
    
    void writeFile(const char*);
    void readFile(const char*);

    #include "WaveFileWrapper.inl"
    
};