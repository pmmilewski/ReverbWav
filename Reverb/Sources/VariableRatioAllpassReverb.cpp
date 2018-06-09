#include <cmath>
#include "VariableRatioAllpassReverb.h"
#include "DelayBlock.h"

VariableRatioAllpassReverb::VariableRatioAllpassReverb()
{
}

VariableRatioAllpassReverb::~VariableRatioAllpassReverb()
{
}

VariableRatioAllpassReverb::VariableRatioAllpassReverb(const int& pdelay, const int& initial_delay, const double& gain)
{
    predelay = new DelayBlock(pdelay);
    allpass_reverb = new AllpassReverbSeries(initial_delay, 0.7, 5);
    gain_ratio = gain;
}
double VariableRatioAllpassReverb::process(const double& input_sample)
{
    double loop_output{0}, loop_input{0}, output{0};
    
    loop_input = input_sample + allpass_reverb->previous_output*gain_ratio;
    loop_output = allpass_reverb->process(predelay->process(loop_input));
    output = input_sample*(-gain_ratio) + (1-pow(gain_ratio,2))*loop_output;
    
    return output;
}
