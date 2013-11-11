#ifndef __NETWORK__
#define __NETWORK__

class neuron;

class network
{
public:
	network();
	~network();
	void construct(int,int);	
	void calc_s(int,int);
	void step();
	
	/// current time
	int	t_;	

	/// number of neurons
	int	num_neu_;
	/// number of time steps
	int	num_step_;	

	/// neurons
	neuron* neu_;
	/// weights
	float* w_;
	/// inputs
	float* x_;
};


#endif


