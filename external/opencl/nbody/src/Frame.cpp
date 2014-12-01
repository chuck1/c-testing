#include <cstring>

#include "universe.h"

void		Frame::copy(Body* b, int n)
{
	bodies_.resize(n);
	memcpy(&bodies_[0], b, n * sizeof(Body));
}
void		Frame::reduce()
{
	auto it = bodies_.begin();

	while(1)
	{
		if(it->alive)
		{
			it++;
		}
		else
		{
			it = bodies_.erase(it);
		}
	}
}

