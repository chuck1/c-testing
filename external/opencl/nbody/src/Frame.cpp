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
void			Frame::random(float m, float w, float v)
{
	for(Body & b : bodies_)
	{
		b.x[0] = (float)(rand() % (int)w) - w * 0.5;
		b.x[1] = (float)(rand() % (int)w) - w * 0.5;
		b.x[2] = (float)(rand() % (int)w) - w * 0.5;

		::print(b.x);

		if(v > 0.0)
		{
			b.v[0] = (float)(rand() % (int)v) - v * 0.5;
			b.v[1] = (float)(rand() % (int)v) - v * 0.5;
			b.v[2] = (float)(rand() % (int)v) - v * 0.5;
		}

		b.mass = m;
		b.radius = radius(b.mass);
	}
}
void			Frame::spin(float m, float w)
{
	// give bodies xz velocity orbiting mass_center

	// universe mass
	float umass = size() * m;

	for(Body & b : bodies_)
	{
		b.x[0] = (float)(rand() % (int)w) - w * 0.5;
		b.x[1] = (float)(rand() % (int)w) - w * 0.5;
		b.x[2] = (float)(rand() % (int)w) - w * 0.5;

		float r = sqrt(b.x[0] * b.x[0] + b.x[1] * b.x[1] + b.x[2] * b.x[2]);

		float rxz = sqrt(b.x[0] * b.x[0] + b.x[2] * b.x[2]);

		float v = sqrt(6.67384E-11 * umass / r) * 0.5;

		b.v[0] = -b.x[2] / rxz * v;
		b.v[1] = 0;
		b.v[2] = b.x[0] / rxz * v;

		b.mass = m;
		b.radius = radius(b.mass);
	}
}

float	distance(float * x0, float * x1)
{
	float r[3];
	r[0] = x0[0] - x1[0];
	r[1] = x0[1] - x1[1];
	r[2] = x0[2] - x1[2];
	float d = sqrt(r[0]*r[0] + r[1]*r[1] + r[2]*r[2]);
	return d;
}
/*
float	func1(float a)
{
	return (float)(rand() % (int)a) - a * 0.5;
}
float	func2(float a)
{
	return a;
}
*/
int			Frame::try_insert(
		float * x,
		float a0,
		float a1,
		float a2,
		float (*f0)(float),
		float (*f1)(float),
		float (*f2)(float),
		float radius,
		unsigned int idx)
{
	bool fail = true;

	for(int i = 0; i < 10; i ++)
	{
		x[0] = f0(a0);
		x[1] = f1(a1);
		x[2] = f2(a2);

		fail = false;

		for(int i = 0; i < idx; i++)
		{
			Body & b = bodies_[i];

			assert(b.radius);

			if(distance(b.x, x) < (b.radius + radius))
			{
				//printf("retry insert\n");
				fail = true;
				break;
			}
		}

		if(!fail) return 0;
	}

	//printf("failed clean insert\n");

	return 1;
}
void			Frame::rings(float m, float w)
{
	// give bodies xz velocity orbiting mass_center

	float r = radius(m);

	printf("radius = %f w = %f\n", r, w);
	printf("num bodies = %i\n", size());

	// universe mass
	float umass = size() * m;

	float x[3];

	int n = 0;


	//for(unsigned int i = 0; i < bodies_.size(); i++)
	for(Body & b : bodies_)
	{
		//Body & b = bodies_[i];

		/*
		if(try_insert(x, w, 0.0, w, func1, func2, func1, r, i)) n++;

		b.x[0] = x[0];
		b.x[1] = x[1];
		b.x[2] = x[2];
		*/

		b.x[0] = (float)(rand() % (int)w) - w * 0.5;
		b.x[1] = 0.0;
		b.x[2] = (float)(rand() % (int)w) - w * 0.5;
		
		::print(b.x);

		float r = sqrt(b.x[0] * b.x[0] + b.x[1] * b.x[1] + b.x[2] * b.x[2]);

		float rxz = sqrt(b.x[0] * b.x[0] + b.x[2] * b.x[2]);

		float v = sqrt(6.67384E-11 * umass / r) * 0.2;

		b.v[0] = -b.x[2] / rxz * v;
		b.v[1] = 0;
		b.v[2] = b.x[0] / rxz * v;

		b.mass = m;
		b.radius = r;
	}

	printf("%i failed inserts\n", n);
}

