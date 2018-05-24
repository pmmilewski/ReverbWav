#pragma once
#include <vector>

class DelayBlock {
private:
	int delay_samples;
	std::vector<double> *buffer;
    double previous_output; // will be used for loops
public:
	DelayBlock(const int&);
	~DelayBlock();
	double process(const double&);
};
