#pragma once
#include "AllpassReverbSeries.h"
#include "DelayBlock.h"

class VariableRatioAllpassReverb
{
private:
    DelayBlock* predelay;
    AllpassReverbSeries* allpass_reverb;
    double gain_ratio;
public:
    VariableRatioAllpassReverb();
    VariableRatioAllpassReverb(const int& pre_delay, const int& initial_delay, const double& gain);
    ~VariableRatioAllpassReverb();

    double process(const double&);
};

