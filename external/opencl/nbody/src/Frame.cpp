#include <cstring>

#include "universe.h"

void		Frame::copy(Body* b, int n)
{
	bodies_.resize(n);
	memcpy(&bodies_[0], b, n * sizeof(Body));
}
unsigned int		Frame::reduce()
{
	unsigned int n;

	auto it = bodies_.begin();

	while(it != bodies_.end())
	{
		if(it->alive == 1)
		{
			it++;
		}
		else
		{
			it = bodies_.erase(it);
			n++;
		}
	}
	return n;
}

