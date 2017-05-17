#include <fstream>
#include <iostream>



using namespace std;



class Mat3D
{
public:
	Mat3D(): m_a(0), m_b(0), m_c(0), pppD(NULL) {}
	~Mat3D()
	{
		for ( int a = 0; a < m_a; a++ )
		{
			for ( int b = 0; b < m_b; b++ )
			{
				delete[] pppD[a][b];
			}
			delete[] pppD[a];
		}
		delete[] pppD;
	}
	
	void Init( int _a, int _b, int _c )
	{
		m_a = _a;
		m_b = _b;
		m_c = _c;
		
		pppD = new double**[m_a];
		for ( int a = 0; a < m_a; a++ )
		{
			pppD[a] = new double*[m_b];
			for ( int b = 0; b < m_b; b++ )
			{
				pppD[a][b] = new double[m_c];
			}
		}
		
	}
	
	double Get( int _a, int _b, int _c )
	{
		if (pppD)
		{
			return pppD[_a][_b][_c];
		}
		return 0;
	}
	
	bool Load3DBinary( const char* filename )
	{
		ifstream ifs;
		ifs.open(filename, std::ifstream::in);
		
		if (!pppD)
		{
			cout << "Matrix not initialized!\n";
			return false;
		}
		
		if (ifs.is_open())
		{
			cout << "File " << filename << " open\n";
		}
		else
		{
			cout << "File " << filename << " failed to open\n";
			return false;
		}
		
		int sz = 8;
		char buf[sz+1];
		double* d = NULL;
		
		for ( int a = 0; a < m_a; a++ )
		{
			for ( int b = 0; b < m_b; b++ )
			{
				for ( int c = 0; c < m_c; c++ )
				{
					ifs.get(buf,sz+1);
					
					d = (double*)buf;
					
					pppD[a][b][c] = *d;
				}
			}
		}
		
		cout << "File loaded\n";
		
		ifs.close();
		
		cout << "File " << filename << " closed\n";
		
		return true;
	}

	
private:
	int m_a, m_b, m_c;
	double*** pppD;
};


int main()
{
	
	Mat3D u1,u2,u3;
	u1.Init(96,49,96);
	//double u1[NK][NJ][NI]; // k,j,i
	
	
	if ( !u1.Load3DBinary( "u1.bin" ) )
		return 0;
	
	
	
	return 0;
}
