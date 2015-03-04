
Score	test(Network n, Input i)
{
	Output o = n.eval(i);

	Score s;

	return s;
}


int main()
{

	Input i;

	Score * s0;
	Score * s1;
	
	// two networks
	Network* n0 = new Network();
	Network* n1 = new Network();

	// test 0
	*s0 = test(n0, i);

	while(1) {
		n1->operator=(n0);
		n1->mutate();

		// test

		*s1 = test(n1, i);

		// copy the best to n0
		if(s1 > s0) {
			std::swap(n0, n1);
			std::swap(s0, s1);
		}
	}
}

