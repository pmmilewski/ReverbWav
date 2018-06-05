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
    previous_output = output;
    return output;
}

AllpassReverbSeries::AllpassReverbSeries(const int& initial_delay, const double& gain, const int& number_of_blocks)
{
    blocks = new std::vector<AllpassReverbBlock>;
    previous_output = 0;
    int current_delay{initial_delay};
    int divider{1}, addition{3}; 
    for(size_t i=0; i < number_of_blocks; i++)
    {
        current_delay = initial_delay/divider;
        blocks->push_back(AllpassReverbBlock(current_delay, gain));
       /* switch(addition)
        {
            case 0:
                addition = 2; 
                break;
            case 2:
                addition = 4;
                break;
            case 4:
                addition = 0;
                break;
        }
        divider *= (3+addition);*/
        divider *= 3;
    }
}

