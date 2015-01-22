#include <iostream>
#include <cstdarg>

using namespace std;

int main()
{
	Mat3D<double> mat;
	mat.Init(4,4,4);
	
	Mat3D< Mat3D<double> > mat2;
	mat2.Init(3,3,3);
	
	/*
	Branch<double> branch;
	branch.Init(3,5,5,5);
	
	for ( int a = 0; a < 5; a++ )
	{
		for ( int b = 0; b < 5; b++ )
		{
			for ( int c = 0; c < 5; c++ )
			{
				cout << ( branch.Get(3,a,b,c)= a*b*c ) << endl;
			}
		}
	}
	*/
	
	
	return 0;
 }