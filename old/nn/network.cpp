#include "neuron.hpp"
#include "network.hpp"
#include <iostream>

network::network(): neu_(0), w_(0)
{
	std::cout << "network ctor" << std::endl;
}

network::~network()
{
	std::cout << "network dtor" << std::endl;

	if (neu_) delete[] neu_;
	if (w_) delete[] w_;
}

void network::construct(int num_neu,int num_step)
{
	num_neu_ = num_neu;
	
	num_step_ = num_step;

	t_ = 0;

	if (neu_)
	{
		delete[] neu_;
	}

	neu_ = new neuron[num_neu_];
	
	w_ = new float[ num_neu_ * num_neu_ ];
	
	x_ = new float[ num_neu * num_step_ ];
}

float network::calc_s(int t,int k)
{
	float s = 0;
	
	for ( int i = 0; i < num_neu_; i++ )
	{
		s += w_[ k*num_neu_ + i ] * neu_[i].y_[t];
	}

	s += x_[ k*num_step_ + t ];
}

void update_w(int t,int k)
{
	float a = 0;

	for 

	float dw = alpha_ * 
}


