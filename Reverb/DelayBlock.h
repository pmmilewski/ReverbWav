#pragma once
#include <vector>

class DelayBlock {
private:
	int delay_samples;
	std::vector<double> *buffer;
public:
	DelayBlock(const int&);
	~DelayBlock();
	double process(const double&);
};
