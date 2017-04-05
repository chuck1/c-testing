#include <fstream>
#include <assert.h>

#include "array.h"

using namespace std;

template <class T>
array<T>::array(): m_arrays(NULL), m_nbArrays(0), m_root(NULL), m_isRoot(false), m_dim(NULL) {
	//cout << "array created\n";
}
template <class T>
			array<T>::~array() {
	if ( m_arrays )
	{
		delete[] m_arrays;
	}
	else if ( m_leaf )
	{
		//cout << "leaf deleted\n";
		// delete m_leaf; not necessary if m_leaf is a shared_ptr; when array object is destroyed, the shared_ptr will be destroyed automatrically, having its use count decreased and the object will be destroyed if necessary
	}
	//cout << "array deleted\n";
}
template <class T> bool 			array<T>::isEmpty() {
	return ( !m_arrays && !m_leaf );
}
template <class T> int 				array<T>::GetDim( int i ) {
	vector<int>* dim = m_root->m_dim;
	
	if ( dim )
	{
		assert(i < dim->size());
		return dim->at(i);
	}
	
	return 0;
}
template <class T> int		 		array<T>::GetNumberOfElements(){
	int n = 0;
	
	//return nbArrays
	return 0;
}
template <class T> int				array<T>::GetNumberOfElements( int n ) {
	/*
	//cout << "Get m_currentDim " << m_currentDim << endl;
	assert( dim );
	assert( m_root );
	assert( m_root->m_dim );
	
	if ( dim->size() != m_root->m_dim->size() )
		cout << dim->size() << " " << m_root->m_dim->size() << endl;
	
	assert( dim->size() == m_root->m_dim->size() );
	
	
	if ( m_currentDim < m_root->m_dim->size() )
	{
		assert(m_arrays);
		// cout << "Getting " << m_currentDim << "\n";
		
		if ( dim->at(m_currentDim) >= m_root->m_dim->at(m_currentDim) )
			cout << dim->at(m_currentDim) << " " << m_root->m_dim->at(m_currentDim) << endl;
		
		assert( dim->at(m_currentDim) < m_root->m_dim->at(m_currentDim) );
		assert( dim->at(m_currentDim) < m_nbArrays );
		
		return m_arrays[dim->at(m_currentDim)].Get( dim );
	}
	else
	{
		// cout << "Getting leaf\n";
		assert(m_leaf);
		return m_leaf;
	}
	*/
	return 0;
}
template <class T> array<T>* 		array<T>::GetArray( int i ) {
	if ( m_arrays )
	{
		if ( i < m_nbArrays )
		{
			return &(m_arrays[i]);
		}
	}
	return NULL;
}
template <class T> shared_ptr<T>	array<T>::GetLeaf() {
	assert(m_leaf);
	
	return m_leaf;
}
template <class T> void 			array<T>::Init( int nbDim, ... ) {
	//cout << "Init nbDim " << nbDim << endl;
	assert(!m_dim);
	assert(isEmpty());
	m_dim = new vector<int>;
	m_dim->clear();
	
	m_isRoot = true;
	
	va_list args;
	
	va_start( args, nbDim );
	for ( int a = 0; a < nbDim; a++ )
	{
		m_dim->push_back(va_arg( args, int ));
		//cout << "m_dim->front() " << m_dim->front() << endl;
	}
	
	va_end( args );
	
	Init(this,0);
}
template <class T> void 			array<T>::Init( array<T>* root, int currentDim ) {
	//cout << "Init m_currentDim " << m_currentDim << endl;
	
	m_root = root;
	m_currentDim = currentDim;
	
	vector<int>* dim = NULL;
	
	dim = m_root->m_dim;
	
	//cout << "Init: dim.get() " << dim.get() << endl;
	
	//cout << "Init: m_dim.get() " << m_dim.get() << endl;
	
	//cout << "this = " << this << " root = " << root << endl;
	
	//assert( m_dim );
	//assert( m_dim.get() == dim.get() );
	
	//cout << "dim " << dim << endl;
	//cout << "dim->size() " << dim->size() << endl;
	//cout << "dim->at(0) " << dim->at(0) << endl;
	
	if ( m_currentDim < dim->size() )
	{
		m_nbArrays = dim->at(m_currentDim);
		
		//cout << "m_nbArrays " << m_nbArrays << "\n";
		
		m_arrays = new array<T>[m_nbArrays];
		
		for ( int a = 0; a < m_nbArrays; a++ )
		{
			m_arrays[a].Init( root, m_currentDim + 1 );
		}
	}
	else
	{
		// cout << "Initializing leaf\n";
		m_leaf.reset(new T);
	}
}
template <class T> array<T>* 		array<T>::GetArray( int nbDim, ... ) {
	assert(nbDim < m_root->m_dim->size());
	
	vector<int>* i = new vector<int>;
	
	va_list args;
	
	va_start( args, nbDim );
	for ( int a = 0; a < nbDim; a++ )
	{
		i->push_back(va_arg( args, int ));
	}
	
	va_end( args );
	
	array<T>* ret = GetArray(i);
	
	delete i;
	
	return ret;
}
template <class T> shared_ptr<T>	array<T>::Get( int nbDim, ... ) {
	assert(nbDim == m_root->m_dim->size());
	
	vector<int>* i = new vector<int>;
	
	va_list args;
	
	va_start( args, nbDim );
	for ( int a = 0; a < nbDim; a++ )
	{
		i->push_back(va_arg( args, int ));
		//cout << "i->back() " << i->back() << endl;
	}
	
	va_end( args );
	
	shared_ptr<T> ret = Get(i);
	
	assert(ret);
	
	delete i;
	
	return ret;
}
template <class T> shared_ptr<T>	array<T>::Get( vector<int>* dim ) {
	//cout << "Get m_currentDim " << m_currentDim << endl;
	assert( dim );
	assert( m_root );
	assert( m_root->m_dim );
	
	if ( dim->size() != m_root->m_dim->size() )
	{
		cout << dim->size() << " " << m_root->m_dim->size() << endl;
	}
	assert( dim->size() == m_root->m_dim->size() );
	
	
	if ( m_currentDim < m_root->m_dim->size() )
	{
		assert(m_arrays);
		// cout << "Getting " << m_currentDim << "\n";
		
		if ( dim->at(m_currentDim) >= m_root->m_dim->at(m_currentDim) )
		{
			cout << dim->at(m_currentDim) << " " << m_root->m_dim->at(m_currentDim) << endl;
		}
		
		assert( dim->at(m_currentDim) < m_root->m_dim->at(m_currentDim) );
		assert( dim->at(m_currentDim) < m_nbArrays );
		
		return m_arrays[dim->at(m_currentDim)].Get( dim );
	}
	else
	{
		// cout << "Getting leaf\n";
		assert(m_leaf);
		return m_leaf;
	}
}
template <class T> array<T>* 		array<T>::GetArray( vector<int>* dim ) {
	if ( m_currentDim < dim->size() )
	{
		// cout << "Getting " << m_currentDim << "\n";
		return m_arrays[dim->at(m_currentDim)]._GetArray( dim );
	}
	else
	{
		return this;
	}
}
template <class T> bool 			array<T>::Save( string filename ) {
	ofstream ofs;
	ofs.open(filename, ofstream::out);
	
	if (isEmpty())
	{
		cout << "Matrix not initialized!\n";
		return false;
	}
	
	if (ofs.is_open())
	{
		cout << "File " << filename << " open\n";
	}
	else
	{
		cout << "File " << filename << " failed to open\n";
		return false;
	}
	
	Save( ofs );
	
	cout << "File " << filename << " saved\n";
	
	ofs.close();
	
	cout << "File " << filename << " closed\n";
	
	return true;
}
template <class T> void 			array<T>::Save( ofstream &ofs ) {
	if ( m_currentDim < m_dim->size() )
	{
		for ( int a = 0; a < m_dim->at(m_currentDim); a++ )
		{
			assert(m_arrays);
			m_arrays[a].Save( ofs );
		}
	}
	else
	{
		assert(m_leaf);
		ofs << (*m_leaf);
	}
}
template <class T> bool 			array<T>::Load( string filename ) {
	ifstream ifs;
	
	if (isEmpty())
	{
		cout << "Matrix not initialized!\n";
		return false;
	}
	
	ifs.open(filename, ofstream::out);
	
	if (ifs.is_open())
	{
		cout << "File " << filename << " open\n";
	}
	else
	{
		cout << "File " << filename << " failed to open\n";
		return false;
	}
	
	Load( ifs );
	
	cout << "File " << filename << " loaded\n";
	
	ifs.close();
	
	cout << "File " << filename << " closed\n";
	
	return true;
}
template <class T> void 			array<T>::Load( ifstream &ifs ) {
	if ( m_currentDim < m_dim->size() )
	{
		for ( int a = 0; a < m_dim->at(m_currentDim); a++ )
		{
			assert(m_arrays);
			m_arrays[a].Load( ifs );
		}
	}
	else
	{
		assert(m_leaf);
		
		int sz = sizeof(T);
		char buf[sz+1];
		T* dub = NULL;
		
		ifs.get(buf,sz+1);
		
		dub = (T*)buf;
		
		(*m_leaf) = (*dub);
	}
}



