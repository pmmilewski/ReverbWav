#include "DelayBlock.h"
#include <iostream>

DelayBlock::DelayBlock(const int &number_of_samples)
{	
	delay_samples = number_of_samples;
	buffer = new std::vector<double>(number_of_samples, 0.0);
}

DelayBlock::~DelayBlock()
{
	delete buffer;
}

double DelayBlock::process(const double &input_sample) 
{
	double output{(*buffer)[delay_samples-1]};
	buffer->pop_back();
	buffer->insert(buffer->begin(), input_sample);
    previous_output = output;
	return output;
}
DelayBlock::DelayBlock()
{
    std::cout << "Please don't use DelayBlock default constructor!" << std::endl;
    buffer = new std::vector<double>;
}
