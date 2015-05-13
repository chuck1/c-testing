#ifndef _ARRAY_H
#define _ARRAY_H

#include <iostream>
#include <fstream>
#include <cstdarg>
#include <assert.h>
#include <memory>
#include <string>
#include <vector>

using namespace std;

template <class T>
class array
{
public:
	array();
	~array();
	
public:
	bool isEmpty();
	
	int GetDim(int i);
	
	void Init( int nbDim, ... );
	void Init( array<T>* parent, int currentDim );
	
	shared_ptr<T> 	GetLeaf();
	
	shared_ptr<T> 	Get( int nbDim, ... );
	shared_ptr<T> 	Get( vector<int>* dim );
	
	array<T>* 		GetArray( int i );
	array<T>* 		GetArray( int nbDim, ... );
	array<T>* 		GetArray( vector<int>* dim );
	
	int GetNumberOfElements();
	int GetNumberOfElements( int n );
	
	// non-essential
	
	bool Save( string filename );
	void Save( ofstream &ofs );
	
	bool Load( string filename );
	void Load( ifstream &ifs );
	
private:
	array<T>* 		m_arrays;
	array<T>* 		m_root;
	int 			m_nbArrays;
	int				m_currentDim;
	vector<int>*	m_dim;
	shared_ptr<T>	m_leaf;
	bool			m_isRoot;
};

#include "array.cpp"

#endif
