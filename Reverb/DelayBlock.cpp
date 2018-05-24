#include "DelayBlock.h"

DelayBlock::DelayBlock(const int &number_of_samples)
{	
	delay_samples = number_of_samples;
	buffer = new std::vector<double>(number_of_samples, 0.0);
}

DelayBlock::~DelayBlock()
{
	delete buffer;
}

double DelayBlock::process(const double &sample) 
{
	double output{(*buffer)[delay_samples-1]};
	buffer->pop_back();
	buffer->insert(buffer->begin(), sample);
	return output;
}
