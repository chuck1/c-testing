#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <cstdarg>
#include <assert.h>
#include <memory>
#include <cmath>
#include <limits>
#include <boost/regex.hpp>

using namespace std;

template <typename T> class matrix {
public:
			matrix();
			~matrix();
	
							void 			init(int nbDim,...);
							void 			init(shared_ptr<int> sz,int nbDim);
	template <typename U> 	void			init(const matrix<U>& m);
	
	void	clear();
	
							T& 				operator[](int a);
							T& 				at(int a);
							T& 				at(int,int);
							T& 				at(int,int,int);
							T& 				at(int*,int);
	
							int				Dim()		const	{ return m_nbDim; }
							int				NbEl()		const	{ return m_nbEl; }
							shared_ptr<int>	Sz()		const	{ return m_sz; }
							int				Sz(int a)	{ return m_sz.get()[a]; }
	
	
	
protected:
	int 				m_nbDim;
	shared_ptr<int> 	m_sz;
	T* 					m_data;
	int 				m_nbEl;
};

template <typename T>								matrix<T>::matrix() {
	m_nbDim = 0;
	m_data = NULL;
	m_nbEl = 0;
}
template <typename T>								matrix<T>::~matrix() {
	clear();
}
template <typename T>						void 	matrix<T>::clear() {
	/*
	if ( m_nbEl < 2 )
	{
		cout << "m_nbEl=" << m_nbEl << "\n";
		cout << "m_data=" << m_data << "\n";
		cout << "m_data?1:0=" << ( m_data?1:0 ) << "\n";
		
	}
	*/
	//assert(m_nbEl > 1);
	
	if ( m_data )
	{
		delete[] m_data;
	}
	
	m_nbDim = 0;
	m_nbEl = 0;
}
template <typename T> 						void	matrix<T>::init(int nbDim,...) {
	shared_ptr<int> sz( new int[nbDim], arraydeleter<int>() );
	
	va_list args;
	
	va_start( args, nbDim );
	
	for ( int a = 0; a < nbDim; a++ )
	{
		sz.get()[a] = va_arg( args, int );
	}
	
	va_end( args );
	
	init( sz, nbDim );
}
template <typename T> template <typename U> void	matrix<T>::init(const matrix<U>& m) {
	init( m.Sz(), m.Dim() );
}
template <typename T>						void	matrix<T>::init(shared_ptr<int> sz,int nbDim) {
	clear();
	
	for ( int a = 0; a < nbDim; a++ )
	{
		if ( m_nbEl )
		{
			m_nbEl *= sz.get()[a];
		}
		else
		{
			m_nbEl = sz.get()[a];
		}
	}
	
	m_nbDim = nbDim;
	m_sz = sz;
	
	assert ( m_nbEl > 1 );
	//cout << "new T[" << m_nbEl << "\n";
	m_data = new T[m_nbEl];
}
template <typename T> 						T& 		matrix<T>::operator[](int a) {
	assert( m_nbDim > 0 );
	
	assert( a < m_nbEl );
	
	return m_data[a];
}
template <typename T> 						T& 		matrix<T>::at(int a) {
	assert( m_nbDim > 0 );
	
	if ( a < 0 ) {
		print_stacktrace();
	}
	assert( a >= 0 );
	
	if ( a >= m_nbEl ) {
		print_stacktrace();
	}
	assert( a < m_nbEl );
	
	return m_data[a];
}
template <typename T> 						T& 		matrix<T>::at(int a,int b) {
	int* i = new int[2];
	i[0] = a;
	i[1] = b;
	
	T& ret = at(i,2);
	
	delete[] i;
	
	return ret;
}
template <typename T> 						T& 		matrix<T>::at(int a,int b,int c) {
	int* i = new int[3];
	i[0] = a;
	i[1] = b;
	i[2] = c;
	
	T& ret = at(i,3);
	
	delete[] i;
	
	return ret;
}
template <typename T> 						T& 		matrix<T>::at(int* i,int dim) {
	//cout << "matrix<T>::Get(int* i,int dim)\n";
	if ( dim > m_nbDim ) {
		print_stacktrace();
	}
	assert( dim <= m_nbDim );
	
	if ( dim == 1 )
	{
		//cout << "\ti={ " << *i << " }\n";
		return at(*i);
	}
	
	int remEl = m_nbEl;
	int* isz = new int[dim-1];
	int b = 0;
	
	//cout << "\ti={ ";
	
	for ( int a = 0; a < (dim-1); a++ )
	{
		//cout << i[a] << ", ";
		
		if ( i[a] >= m_sz.get()[a] ) {
			print_stacktrace();
		}
		assert( i[a] < m_sz.get()[a] );
		
		remEl /= m_sz.get()[a];
		
		isz[a] = remEl;
		
		b += isz[a] * i[a];
	}
	
	//cout << i[dim-1] << " }\n";
	if ( i[dim-1] >= remEl ) {
		printf("%i < %i\n",i[dim-1],remEl);
		print_stacktrace();
	}
	assert( i[dim-1] < remEl );
	
	b += i[dim-1];
	
	//cout << "\tGet(" << b << ")\n";
	
	//cout << "\tdelete[] isz B\n";
	delete[] isz;
	//cout << "\tdelete[] isz A\n";
	
	
	return at(b);
}



bool						NextI(int* sz,int* SZ,int n) {
	sz[n-1]++;
	
	for ( int a = (n-1); a > -1; a-- )
	{
		if ( sz[a] >= SZ[a] )
		{
			if ( a > 0 )
			{
				sz[a] = 0;
				sz[a-1]++;
			}
			else
			{
				return false;
			}
		}
	}
	
	return true;
}
template <typename T> void	grid(matrix<T>& m0,matrix<T>& m1,matrix<T>& M0,matrix<T>& M1) {
	int dim = m0.Dim() + m1.Dim();
	
	shared_ptr<int> sz(new int[dim], arraydeleter<int>());
	
	
	int b = 0;
	for ( int a = 0; a < m0.Dim(); a++, b++ )
	{
		sz.get()[b] = m0.Sz(a);
	}
	for ( int a = 0; a < m1.Dim(); a++, b++ )
	{
		sz.get()[b] = m1.Sz(a);
	}
	
	M0.init(sz,dim);
	M1.init(sz,dim);
	
	int *i = new int[dim];
	for ( int a = 0; a < dim; a++ )
	{
		i[a] = 0;
	}
	
	do
	{
		M0.Get(i,dim) = m0.Get(i,				m0.Dim());
		M1.Get(i,dim) = m1.Get(i + m0.Dim(),	m1.Dim());
	}
	while ( NextI( i, sz.get(), dim ) );
	
	delete[] i;
}
template <typename T> void	grid(matrix<T>& m0,matrix<T>& m1,matrix<T>& m2,matrix<T>& M0,matrix<T>& M1,matrix<T>& M2) {
	int dim = m0.Dim() + m1.Dim() + m2.Dim();
	
	shared_ptr<int> sz(new int[dim], arraydeleter<int>());
	
	int b = 0;
	for ( int a = 0; a < m0.Dim(); a++, b++ )
	{
		sz.get()[b] = m0.Sz(a);
	}
	for ( int a = 0; a < m1.Dim(); a++, b++ )
	{
		sz.get()[b] = m1.Sz(a);
	}
	for ( int a = 0; a < m2.Dim(); a++, b++ )
	{
		sz.get()[b] = m2.Sz(a);
	}
	
	M0.init(sz,dim);
	M1.init(sz,dim);
	M2.init(sz,dim);
	
	int *i = new int[dim];
	for ( int a = 0; a < dim; a++ )
	{
		i[a] = 0;
	}
	
	do
	{
		M0.Get(i,dim) = m0.Get(i,					m0.Dim());
		M1.Get(i,dim) = m1.Get(i+m0.Dim(),			m1.Dim());
		M2.Get(i,dim) = m2.Get(i+m0.Dim()+m1.Dim(),	m2.Dim());
	}
	while ( NextI( i, sz.get(), dim ) );
}





#include "matrixD.h"

#endif

