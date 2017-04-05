#ifndef _MATHARRAY_H
#define _MATHARRAY_H

#include "array.cpp"

using namespace std;

typedef shared_ptr<vector<int> > shr_vec_int;

template <class T>
class matharray: public array<T>
{
public:
	
public:
	// non-essential
	double Mean( int nbDim, ... );
	double Mean( shr_vec_int i );
	void Mean( array<T>* branch, int nbDim, ... );
	void Mean( array<T>* branch, shr_vec_int dim, shr_vec_int i );
	
	double Sum( int nbDim, ... );
	double Sum( shr_vec_int i );
	
	void ElementwiseOperation( T(*operation)(vector<T*>), int n, ... );
	void ElementwiseOperation( T(*operation)(vector<T*>), vector<array<T>* > branches );
	
	void ElementwiseOperation( matharray<T> &b1, matharray<T> &b2, array<T> &b3, array<T> &b4, T(*operation)(T&,T&,T&,T&) );
	void ElementwiseOperation( matharray<T> &b1, matharray<T> &b2, T(*operation)(T&,T&) );
	
};

#endif
