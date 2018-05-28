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
    int fib1{1}, fib2{1}, fib3{fib1+fib2};
    int current_delay{initial_delay};
    
    for(size_t i=0; i < number_of_blocks; i++)
    {
        current_delay = initial_delay/fib3;
        blocks->push_back(AllpassReverbBlock(current_delay, gain));
        fib1 = fib2;
        fib2 = fib3;
        fib3 = fib1 + fib2;
    }
}

