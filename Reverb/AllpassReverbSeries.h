#pragma once
#include "AllpassReverbBlock.h"
#include <vector>

class AllpassReverbSeries
{
private:
    std::vector<AllpassReverbBlock>* blocks;
    
    
public:
    AllpassReverbSeries();
    AllpassReverbSeries(const int&, const double&, const int&);
    ~AllpassReverbSeries();
    
    double process(const double&);
};

