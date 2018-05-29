#include "AllpassReverbSeries.h"
#include <iostream>

AllpassReverbSeries::AllpassReverbSeries()
{
    std::cout << "Don't use AllpassReverbSeries constructor! Set parameters" << std::endl;
}

AllpassReverbSeries::~AllpassReverbSeries()
{
    
}

double AllpassReverbSeries::process(const double& input_sample)
{
    double output{input_sample};
    for(auto& block: *blocks)
    {
        output = block.process(output);
    }
    return output;
}

AllpassReverbSeries::AllpassReverbSeries(const int& initial_delay, const double& gain, const int& number_of_blocks)
{
    blocks = new std::vector<AllpassReverbBlock>;
    int current_delay{initial_delay};
    int divider{1};
    for(size_t i=0; i < number_of_blocks; i++)
    {
        current_delay = initial_delay/divider;
        blocks->push_back(AllpassReverbBlock(current_delay, gain));
        divider *= 3;
    }
}

