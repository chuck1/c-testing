
#include "Input.hpp"
#include "Output.hpp"
#include "Network.hpp"



int main()
{

	Input i;

	int * s0;
	int * s1;
	
	// two networks
	Network* n0 = new Network();
	Network* n1 = new Network();

	// test 0
	*s0 = n0->test(i);

	while(1) {
		n1->operator=(n0);
		n1->mutate();

		*s1 = n1->test(i);

		// copy the best to n0
		if(*s1 > *s0) {
			std::swap(n0, n1);
			std::swap(s0, s1);
		}
	}
}

