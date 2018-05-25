#pragma once
#include <vector>

class DelayBlock {
private:
	int delay_samples;
	std::vector<double> *buffer;
    
public:
    DelayBlock();
	DelayBlock(const int&);
	~DelayBlock();
	double process(const double&);
    
    double previous_output; // will be used for loops
};
