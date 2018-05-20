#pragma once
#include <vector>

template<typename T>
class DelayBlock {
private:
	int delay_samples;
	std::vector<T> *buffer;
public:
	DelayBlock(const int&);
	~DelayBlock();
	T process(const T&);
};

template<typename T>
DelayBlock<T>::DelayBlock(const int &number_of_samples)
{	
	delay_samples = number_of_samples;
	buffer = new std::vector<T>(number_of_samples, static_cast<T>(0));
}

template<typename T>
DelayBlock<T>::~DelayBlock()
{
	delete buffer;
}

template<typename T>
T DelayBlock<T>::process(const T &sample) 
{
	T output{(*buffer)[delay_samples-1]};
	buffer->pop_back();
	buffer->insert(buffer->begin(), sample);
	return output;
}
