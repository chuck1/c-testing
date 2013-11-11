#include "IVariable.h"
#include "HW5.h"
#include "Functions.h"



typedef shared_ptr<IVariable<double> > sptr_IVarD;
typedef shared_ptr<IVariable<string> > sptr_IVarS;
typedef shared_ptr<vector<int> > shr_vec_int;

using namespace std;

template <class T>
IVariable<T>::IVariable(HW5* parent, const char* filename): m_mat(NULL),m_parent(parent),m_filename(filename)
{
}

template <class T>
bool IVariable<T>::Init()
{
	if (!VInit())
	{
		ERROR("VInit failed");
		return false;
	}
	
	return true;
}

template <class T>
Branch<T>* IVariable<T>::Get()
{
	if (Ensure())
		return m_mat;
		
	return NULL;
}

template <class T>
bool IVariable<T>::Ensure()
{
	if (!m_mat)
	{
		m_mat = new Branch<T>;
	}
	
	assert(m_mat);
	
	if (m_mat->isEmpty())
	{
		if (!Init())
		{
			ERROR("Init failed");
			return false;
		}
		
		if (!m_mat->Load(m_filename))
		{
			cout << m_filename << " load failed. Trying VEnsure...\n";
			return VEnsure();
		}
	}
	return true;
}

// u --------------------------------------------------------------------------------------

u::u(HW5* parent): IVariable<double>(parent,(const char*)"calc_data/u.bin")
{}

bool u::VEnsure()
{
	if (!Load())
	{
		return false;
	}
	
	if (!m_mat->Save(m_filename))
	{
		return false;
	}
	
	return true;
}

bool u::VInit()
{
	m_mat->_Init(5,3,3,96,49,96);
	return true;
}

bool u::Load()
{
	for ( int a = 0; a < m_mat->GetDim(0); a++ )
	{
		for ( int b = 0; b < m_mat->GetDim(1); b++ )
		{
			Branch<double>* branch = m_mat->_GetBranch(2,a,b);
			assert(branch);
			
			sptr_IVarS pfilenames = m_parent->GetVarS("filenames");
			assert(pfilenames);
			
			Branch<string>* strBranch = pfilenames->Get();
			assert(strBranch);
			
			if ( !branch->Load( strBranch->_Get(2,a,b) ) )
				return false;
			
			/*
			if ( !Load3DBinary( m_mat, m_parent->m_filenames->Get()->_Get(2,a,b), a, b ) )
				return false;
			*/
		}
	}
	return true;
}

// umean --------------------------------------------------------------------------------------

umean::umean(HW5* parent): IVariable<double>(parent,(const char*)"calc_data/umean.bin")
{}

bool umean::VEnsure()
{
	assert(m_parent);
	
	sptr_IVarD pu = m_parent->GetVarD("u");
	assert(pu);
	
	cout << "sv initialized\n";
	
	Branch<double>* branch = pu->Get();
	assert(branch);
	
	cout << "calculating umean...\n";
	m_mat->_Mean( branch, 2, 0, 3 );
	
	cout << "umean calculated\n";
	
	if (!m_mat->Save(m_filename))
	{
		ERROR("m_mat->Save failed");
		return false;
	}
	
	return true;
}

bool umean::VInit()
{
	m_mat->_Init(2,3,49);
	return true;
}

// up --------------------------------------------------------------------------------------

up::up(HW5* parent): IVariable<double>(parent,(const char*)"calc_data/up")
{
}

bool up::VEnsure()
{
	shr_vec_int sv = constructShrVecInt( 3, 0, 3 );
	
	sptr_IVarD pu = m_parent->GetVarD("u");
	assert(pu);
	
	sptr_IVarD pumean = m_parent->GetVarD("umean");
	
	assert(pumean);
	
	subtract( m_mat, pu->Get(), pumean->Get(), sv );
	cout << "up calculated\n";
	
	if (!m_mat->Save(m_filename))
		return false;
	
	return true;
}

bool up::VInit()
{
	m_mat->_Init(5,3,3,96,49,96);
	return true;
}

// filename --------------------------------------------------------------------------------------

bool filenames::VEnsure()
{
	if (!Load())
		return false;
	
	if (!m_mat->Save(m_filename))
		return false;
	
	return true;
}

bool filenames::VInit()
{
	m_mat->_Init(2,3,3);
	return true;
}

bool filenames::Load()
{
	cout << "Loading filenames...\n";
	// cout << "1\n";
	// cout << &m_filenames._GetBranch(0)._GetBranch(0)._GetLeaf() << "\n";
	m_mat->_Get(2,0,0) = "raw_data/u1.bin";
	// cout << "2\n";
	m_mat->_Get(2,0,1) = "raw_data/u2.bin";
	m_mat->_Get(2,0,2) = "raw_data/u3.bin";
	m_mat->_Get(2,1,0) = "raw_data/v1.bin";
	m_mat->_Get(2,1,1) = "raw_data/v2.bin";
	m_mat->_Get(2,1,2) = "raw_data/v3.bin";
	m_mat->_Get(2,2,0) = "raw_data/w1.bin";
	m_mat->_Get(2,2,1) = "raw_data/w2.bin";
	m_mat->_Get(2,2,2) = "raw_data/w3.bin";
	cout << "Filenames loaded\n";
}