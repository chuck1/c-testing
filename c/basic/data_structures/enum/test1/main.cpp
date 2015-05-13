#include <stdint.h>
#include <stdio.h>

#include <map>
#include <algorithm>

enum E: uint32_t
{
	zero =  1 << 0,
	one  =  1 << 1,
	two  =  1 << 2,
	three = 1 << 3
};

enum Eder: uint32_t
{
	four = 1 << 4,
	five = 1 << 5
};

int printmap( std::pair<E,char const *> p )
{
	printf( "%i=%s\n", p.first, p.second );
}

int main()
{
	std::map<E,char const *> m;
	
	E e = E( E::zero | E::one );
	
	m[E::zero] = "hello";
	m[E::one] = "world";
	m[e] = "hello, world";

	e = E(Eder::four);
	
	m[e] = "goodbye";
	
	for_each( m.begin(), m.end(), printmap );
	
	
}

