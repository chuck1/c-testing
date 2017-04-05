#include "matharray.h"

using namespace std;

template <class T>
double array<T>::Sum( int nbDim, ... )
{
	assert(nbDim == m_dim->size());
	
	//cout << "nbDim = " << nbDim << endl;
	
	shr_vec_int i(new vector<int>);
	
	va_list args;
	
	va_start( args, nbDim );
	
	for ( int a = 0; a < nbDim; a++ )
	{
		i->push_back(va_arg( args, int ));
	}
	
	va_end( args );
	
	double s = Sum(i);
	
	delete[] i;
	
	return s;
}

template <class T>
double array<T>::Sum( shr_vec_int i )
{
	assert( i->size() == m_dim->size() );
	
	int firstSummingDim = -1;
	int nbSummingDims = 0;
	
	for ( int a = 0; a < i->size(); a++ )
	{
		//cout << m_dim[a] << " ";
		if ( i->at(a) == -1 )
		{
			nbSummingDims++;
			
			if ( firstSummingDim == -1 )
			{
				firstSummingDim = a;
			}
		}
	}
	//cout << "\n";
	
	double s = 0;
	
	if ( nbSummingDims == 1 )
	{
		for ( int a = 0; a < m_dim->at(firstSummingDim); a++ )
		{
			i->at(firstSummingDim) = a;
			
			for ( int b = 0; b < m_dim->size(); b++ )
			{
				//cout << i->at(b) << " ";
				assert(( i->at(b) >=0 ) && ( i->at(b) < m_dim->at(b) ));
			}
			//cout << "\n";
			
			s += Get(i);
		}
	}
	else if (nbSummingDims > 1)
	{
		for ( int a = 0; a < m_dim->at(firstSummingDim); a++ )
		{
			i->at(firstSummingDim) = a;
			/*
			for ( int b = 0; b < m_dim->size(); b++ )
			{
				cout << i[b];
			}
			cout << "\n";
			*/
			s += Sum(i);
		}
	}
	
	return s;
}

template <class T>
double array<T>::Mean( int nbDim, ... )
{
	assert(nbDim == m_dim->size());
	
	//cout << "nbDim = " << nbDim << endl;
	
	shr_vec_int i(new vector<int>);
	
	va_list args;
	
	va_start( args, nbDim );
	
	for ( int a = 0; a < nbDim; a++ )
	{
		i->push_back(va_arg( args, int ));
	}
	
	va_end( args );
	
	double m = Mean(i);
	
	return m;
}

template <class T>
double array<T>::Mean( shr_vec_int i )
{
	double s = Sum(i);
	
	int N = 1;
	
	for ( int a = 0; a < m_dim->size(); a++ )
	{
		N *= m_dim->at(a);
	}
	
	return s / (double)N;
}

template <class T>
void array<T>::Mean( array<T>* array, int nbDim, ... )
{
	assert(nbDim == m_dim->size());
	assert(array);
	//cout << "nbDim = " << nbDim << endl;
	
	shr_vec_int dim(new vector<int>(array->m_dim->size(),-1));
	
	shr_vec_int i(new vector<int>);
	
	va_list args;
	
	va_start( args, nbDim );
	
	for ( int a = 0; a < nbDim; a++ )
	{
		i->push_back(va_arg( args, int ));
	}
	
	va_end( args );
	
	cout << "_Mean descending\n";
	_Mean(array,dim,i);
}

template <class T>
void array<T>::Mean( array<T>* arr, shr_vec_int dim, shr_vec_int i )
{
	assert(m_dim);
	assert(dim);
	assert(i);
	
	if ( m_currentDim == 0 )
	{
		// initial checks
		assert( i->size() == m_dim->size() );
		assert( dim->size() == arr->m_dim->size() );
	}
	
	if ( m_currentDim < m_dim->size() )
	{
		for ( int a = 0; a < m_dim->at(m_currentDim); a++ )
		{
			dim->at(i->at(m_currentDim)) = a;
			
			array<T>* nextarray = GetArray(a);
			
			nextarray->_Mean( arr, dim, i );
		}
	}
	else
	{
		assert(m_leaf);
		(*m_leaf) = arr->_Mean(dim);
	}
}

template <class T>
void array<T>::ElementwiseOperation( T(*operation)(vector<T*>), int n, ... )
{
	vector<array<T>* > arrs;
	
	va_list args;
	
	va_start( args, n );
	
	for ( int a = 0; a < n; a++ )
	{
		arrs.push_back(va_arg( args, array<T>* ));
	}
	
	va_end( args );
	
	ElementwiseOperation( operation, arrs );
}

template <class T>
void array<T>::ElementwiseOperation( T(*operation)(vector<T*>), vector<array<T>* > Arrays )
{
	if ( m_currentDim < m_dim->size() )
	{
		vector<array<T> > nextArrays = Arrays;
		
		for ( int a = 0; a < m_dim->at(m_currentDim); a++ )
		{
			for ( int b = 0; b < nextArrays->size(); b++ )
			{
				nextArrays.at(b) = nextArrays.at(b)->_GetArray(a);
			}
			
			m_arrays[a].ElementwiseOperation( operation, nextArrays );
		}
	}
	else
	{
		assert(m_leaf);
		
		vector<T*> t;
		
		for ( int a = 0; a < Arrays->size(); a++ )
		{
			T* leaf = Arrays->at(a)->_GetLeaf();
			assert(leaf);
			t.push_back( leaf );
		}
		
		(*m_leaf) = (*operation)( t );
	}
}
