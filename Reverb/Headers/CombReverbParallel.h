#pragma once
#include "CombReverbBlock.h"
#include <vector>

class CombReverbParallel
{
private:
    std::vector<CombReverbBlock>* blocks;
    
public:
    CombReverbParallel();
    ~CombReverbParallel();
    
    void addBlock(const int&, const double&);
    
    double process(const double&);
};