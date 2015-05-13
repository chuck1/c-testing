#include <iostream>
#include <cstdarg>

#include <cmath>
#include <string>
#include <memory>

#include "Branch.h"
#include "IVariable.h"

using namespace std;


/*
bool Load3DBinary( Mat5D<double>& mat, const char* filename, int a, int b )
{
	ifstream ifs;
	ifs.open(filename, std::ifstream::in);
	
	if (mat.isEmpty())
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
	double* dub = NULL;
	
	for ( int c = 0; c < mat.GetDim(2); c++ )
	{
		for ( int d = 0; d < mat.GetDim(3); d++ )
		{
			for ( int e = 0; e < mat.GetDim(4); e++ )
			{
				ifs.get(buf,sz+1);
				
				dub = (double*)buf;
				
				mat.Get(a,b,c,d,e) = *dub;
			}
		}
	}
	
	cout << "File " << filename << " loaded\n";
	
	ifs.close();
	
	cout << "File " << filename << " closed\n";
	
	return true;
};

bool Load1DBinary( Mat1D<double>& mat, const char* filename )
{
	ifstream ifs;
	ifs.open(filename, std::ifstream::in);
	
	if (mat.isEmpty())
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
	double* dub = NULL;
	
	for ( int a = 0; a < mat.GetDim(0); a++ )
	{
		ifs.get(buf,sz+1);
				
		dub = (double*)buf;
				
		mat.Get(a) = *dub;
	}
	
	cout << "File " << filename << " loaded\n";
	
	ifs.close();
	
	cout << "File " << filename << " closed\n";
	
	return true;
};

void mean( Mat4D<double>& mat4, Mat1D<double>& mat1 )
{
	int n = mat4.GetDim(0) * mat4.GetDim(1) * mat4.GetDim(3);
	
	for ( int d = 0; d < mat4.GetDim(2); d++ )
	{
		//cout << "mean 4\n";
		mat1.Get(d) = mat4.Sum(-1,-1,d,-1) / (double)n;
	}
};

void mean( Mat5D<double>& mat5, Mat2D<double>& mat2 )
{
	int n = mat5.GetDim(1) * mat5.GetDim(2) * mat5.GetDim(4);
	
	for ( int a = 0; a < mat5.GetDim(0); a++ )
	{
		for ( int d = 0; d < mat5.GetDim(3); d++ )
		{
			mat2.Get(a,d) = mat5.Sum(a,-1,-1,d,-1) / (double)n;
		}
	}
};

void mean( Mat6D<double>& mat6, Mat3D<double>& mat3 )
{
	int n = mat6.GetDim(2) * mat6.GetDim(3) * mat6.GetDim(5);
	
	for ( int a = 0; a < mat6.GetDim(0); a++ )
	{
		for ( int b = 0; b < mat6.GetDim(1); b++ )
		{
			for ( int e = 0; e < mat6.GetDim(4); e++ )
			{
				mat3.Get(a,b,e) = mat6.Sum(a,b,-1,-1,e,-1) / (double)n;
			}
		}
	}
};


void subtract( Mat5D<double>& diff, Mat5D<double>& mat5, Mat2D<double>& mat2 )
{
	for ( int a = 0; a < mat5.GetDim(0); a++ )
	{
		for ( int b = 0; b < mat5.GetDim(1); b++ )
		{
			for ( int c = 0; c < mat5.GetDim(2); c++ )
			{
				for ( int d = 0; d < mat5.GetDim(3); d++ )
				{
					for ( int e = 0; e < mat5.GetDim(4); e++ )
					{
						diff.Get(a,b,c,d,e) = mat5.Get(a,b,c,d,e) - mat2.Get(a,d);
					}
				}
			}
		}
	}
}

void pointCorr( Mat6D<double>& mat6, Mat5D<double>& mat5_1, Mat5D<double>& mat5_2 )
{
	for ( int a = 0; a < mat6.GetDim(0); a++ )
	{
		for ( int b = 0; b < mat6.GetDim(1); b++ )
		{
			for ( int c = 0; c < mat6.GetDim(2); c++ )
			{
				for ( int d = 0; d < mat6.GetDim(3); d++ )
				{
					for ( int e = 0; e < mat6.GetDim(4); e++ )
					{
						for ( int f = 0; f < mat6.GetDim(5); f++ )
						{
							mat6.Get(a,b,c,d,e,f) = mat5_1.Get(a,c,d,e,f) * mat5_2.Get(b,c,d,e,f);
						}
					}
				}
			}
		}
	}
}

void sample( Mat5D<double>& dns, Mat5D<double>& les )
{
	for ( int a = 0; a < les.GetDim(0); a++ )
	{
		for ( int b = 0; b < les.GetDim(1); b++ )
		{
			for ( int c = 0; c < les.GetDim(2); c++ )
			{
				for ( int d = 0; d < les.GetDim(3); d++ )
				{
					for ( int e = 0; e < les.GetDim(4); e++ )
					{
						les.Get(a,b,c,d,e) = dns.Get(a,b,c*4,d,e*4);
					}
				}
			}
		}
	}
}

void topHat( Mat5D<double>& orig, Mat5D<double>& filt )
{
	int dSz = orig.GetDim(2);
	int eSz = orig.GetDim(3);
	int fSz = orig.GetDim(4);
	
	for ( int a = 0; a < orig.GetDim(0); a++ )
	{
		for ( int b = 0; b < orig.GetDim(1); b++ )
		{
			for ( int d = 0; d < dSz; d++ )
			{
				for ( int e = 0; e < eSz; e++ )
				{
					for ( int f = 0; f < fSz; f++ )
					{
						double temp = 0;
						
						temp += orig.Get(a,b,PerInd(d-1,dSz),e,PerInd(f+1,fSz))/16.0;
						temp += orig.Get(a,b,PerInd(d+1,dSz),e,PerInd(f+1,fSz))/16.0;
						temp += orig.Get(a,b,PerInd(d-1,dSz),e,PerInd(f-1,fSz))/16.0;
						temp += orig.Get(a,b,PerInd(d+1,dSz),e,PerInd(f-1,fSz))/16.0;

						temp += orig.Get(a,b,PerInd(d-1,dSz),e,f)/8.0;
						temp += orig.Get(a,b,PerInd(d+1,dSz),e,f)/8.0;
						temp += orig.Get(a,b,d,e,PerInd(f-1,fSz))/8.0;
						temp += orig.Get(a,b,d,e,PerInd(f+1,fSz))/8.0;

						temp += orig.Get(a,b,d,e,f)/4.0;
						
						filt.Get(a,b,d,e,f) = temp;
					}
				}
			}
		}
	}
}

void topHat( Mat6D<double>& orig, Mat6D<double>& filt )
{
	int dSz = orig.GetDim(3);
	int eSz = orig.GetDim(4);
	int fSz = orig.GetDim(5);
	
	for ( int a = 0; a < orig.GetDim(0); a++ )
	{
		for ( int b = 0; b < orig.GetDim(1); b++ )
		{
			for ( int c = 0; c < orig.GetDim(2); c++ )
			{
				for ( int d = 0; d < dSz; d++ )
				{
					for ( int e = 0; e < eSz; e++ )
					{
						for ( int f = 0; f < fSz; f++ )
						{
							double temp = 0;
							
							temp += orig.Get(a,b,c,PerInd(d-1,dSz),e,PerInd(f+1,fSz))/16.0;
							temp += orig.Get(a,b,c,PerInd(d+1,dSz),e,PerInd(f+1,fSz))/16.0;
							temp += orig.Get(a,b,c,PerInd(d-1,dSz),e,PerInd(f-1,fSz))/16.0;
							temp += orig.Get(a,b,c,PerInd(d+1,dSz),e,PerInd(f-1,fSz))/16.0;

							temp += orig.Get(a,b,c,PerInd(d-1,dSz),e,f)/8.0;
							temp += orig.Get(a,b,c,PerInd(d+1,dSz),e,f)/8.0;
							temp += orig.Get(a,b,c,d,e,PerInd(f-1,fSz))/8.0;
							temp += orig.Get(a,b,c,d,e,PerInd(f+1,fSz))/8.0;

							temp += orig.Get(a,b,c,d,e,f)/4.0;
							
							filt.Get(a,b,c,d,e,f) = temp;
						}
					}
				}
			}
		}
	}
}

void topHat2( Mat4D<double>& orig, Mat4D<double>& filt )
{
	int dSz = orig.GetDim(1);
	int eSz = orig.GetDim(2);
	int fSz = orig.GetDim(3);
	
	for ( int a = 0; a < orig.GetDim(0); a++ )
	{
		for ( int d = 0; d < dSz; d++ )
		{
			for ( int e = 0; e < eSz; e++ )
			{
				for ( int f = 0; f < fSz; f++ )
				{
					double temp = 0;
					
					temp += orig.Get(a,PerInd(d-1,dSz),e,PerInd(f+1,fSz))/16.0;
					temp += orig.Get(a,PerInd(d+1,dSz),e,PerInd(f+1,fSz))/16.0;
					temp += orig.Get(a,PerInd(d-1,dSz),e,PerInd(f-1,fSz))/16.0;
					temp += orig.Get(a,PerInd(d+1,dSz),e,PerInd(f-1,fSz))/16.0;

					temp += orig.Get(a,PerInd(d-1,dSz),e,f)/8.0;
					temp += orig.Get(a,PerInd(d+1,dSz),e,f)/8.0;
					temp += orig.Get(a,d,e,PerInd(f-1,fSz))/8.0;
					temp += orig.Get(a,d,e,PerInd(f+1,fSz))/8.0;

					temp += orig.Get(a,d,e,f)/4.0;
					
					filt.Get(a,d,e,f) = temp;
				}
			}
		}
	}
}

void topHat2( Mat5D<double>& orig, Mat5D<double>& filt )
{
	int dSz = orig.GetDim(2);
	int eSz = orig.GetDim(3);
	int fSz = orig.GetDim(4);
	
	for ( int a = 0; a < orig.GetDim(0); a++ )
	{
		for ( int b = 0; b < orig.GetDim(1); b++ )
		{
			for ( int d = 0; d < dSz; d++ )
			{
				for ( int e = 0; e < eSz; e++ )
				{
					for ( int f = 0; f < fSz; f++ )
					{
						double temp = 0;
						
						temp += orig.Get(a,b,PerInd(d-1,dSz),e,PerInd(f+1,fSz))/16.0;
						temp += orig.Get(a,b,PerInd(d+1,dSz),e,PerInd(f+1,fSz))/16.0;
						temp += orig.Get(a,b,PerInd(d-1,dSz),e,PerInd(f-1,fSz))/16.0;
						temp += orig.Get(a,b,PerInd(d+1,dSz),e,PerInd(f-1,fSz))/16.0;

						temp += orig.Get(a,b,PerInd(d-1,dSz),e,f)/8.0;
						temp += orig.Get(a,b,PerInd(d+1,dSz),e,f)/8.0;
						temp += orig.Get(a,b,d,e,PerInd(f-1,fSz))/8.0;
						temp += orig.Get(a,b,d,e,PerInd(f+1,fSz))/8.0;

						temp += orig.Get(a,b,d,e,f)/4.0;
						
						filt.Get(a,b,d,e,f) = temp;
					}
				}
			}
		}
	}
}

void topHat2( Mat6D<double>& orig, Mat6D<double>& filt )
{
	int dSz = orig.GetDim(3);
	int eSz = orig.GetDim(4);
	int fSz = orig.GetDim(5);
	
	for ( int a = 0; a < orig.GetDim(0); a++ )
	{
		for ( int b = 0; b < orig.GetDim(1); b++ )
		{
			for ( int c = 0; c < orig.GetDim(2); c++ )
			{
				for ( int d = 0; d < dSz; d++ )
				{
					for ( int e = 0; e < eSz; e++ )
					{
						for ( int f = 0; f < fSz; f++ )
						{
							double temp = 0;
							
							temp += orig.Get(a,b,c,PerInd(d-1,dSz),e,PerInd(f+1,fSz))/16.0;
							temp += orig.Get(a,b,c,PerInd(d+1,dSz),e,PerInd(f+1,fSz))/16.0;
							temp += orig.Get(a,b,c,PerInd(d-1,dSz),e,PerInd(f-1,fSz))/16.0;
							temp += orig.Get(a,b,c,PerInd(d+1,dSz),e,PerInd(f-1,fSz))/16.0;

							temp += orig.Get(a,b,c,PerInd(d-1,dSz),e,f)/8.0;
							temp += orig.Get(a,b,c,PerInd(d+1,dSz),e,f)/8.0;
							temp += orig.Get(a,b,c,d,e,PerInd(f-1,fSz))/8.0;
							temp += orig.Get(a,b,c,d,e,PerInd(f+1,fSz))/8.0;

							temp += orig.Get(a,b,c,d,e,f)/4.0;
							
							filt.Get(a,b,c,d,e,f) = temp;
						}
					}
				}
			}
		}
	}
}

void thisHasAName1( Mat6D<double>& orig, Mat6D<double>& res )
{
	for ( int a = 0; a < res.GetDim(0); a++ )
	{
		for ( int b = 0; b < res.GetDim(1); b++ )
		{
			for ( int c = 0; c < res.GetDim(2); c++ )
			{
				for ( int d = 0; d < res.GetDim(3); d++ )
				{
					for ( int e = 0; e < res.GetDim(4); e++ )
					{
						for ( int f = 0; f < res.GetDim(5); f++ )
						{
							res.Get(a,b,c,d,e,f) = 0.5*( orig.Get(a,b,c,d,e,f) + orig.Get(b,a,c,d,e,f) );
						}
					}
				}
			}
		}
	}
}

void HW5::diff( Mat5D<double>& orig, Mat6D<double>& der )
{
	int dSz = der.GetDim(3);
	int eSz = der.GetDim(4);
	int fSz = der.GetDim(5);
	
	for ( int a = 0; a < der.GetDim(0); a++ )
	{
		for ( int b = 0; b < der.GetDim(1); b++ )
		{
			for ( int c = 0; c < der.GetDim(2); c++ )
			{
				for ( int d = 0; d < dSz; d++ )
				{
					for ( int e = 0; e < eSz; e++ )
					{
						for ( int f = 0; f < fSz; f++ )
						{
							double dx = 1;
							
							if ( b == 1 )
							{
								if ( e == ( eSz - 1 ) )
								{
									der.Get(a,b,c,d,e,f) = 0;
									continue;
								}
								dx = m_y.Get(e+1) - m_y.Get(e);
							}
							else if ( b == 0 )
							{
								dx = m_dx;
							}
							else if ( b == 2 )
							{
								dx = m_dz;
							}
							
							int o[3] = {0,0,0};
							o[b] = 1;
							
							der.Get(a,b,c,d,e,f) = 
							( orig.Get(a,c,PerInd(d+o[0],dSz),
							e+o[1],
							PerInd(f+o[2],fSz)) 
							- orig.Get(a,c,d,e,f) )
							/dx;
                        
						}
					}
				}
			}
		}
	}
}

*/



template <class T>
void mean( Branch<T>* b1, Branch<T>* b2, shr_vec_int dim )
{
	
}



template <class T>
void subtract( Branch<T>* b1, Branch<T>* b2, Branch<T>* b3, shr_vec_int dim )
{
	
}


int PerInd( int i, int sz )
{
	if ( i < 0 )
	{
		return ( i + sz );
	}
	else if ( i >= sz )
	{
		return ( i - sz );
	}
	
	return i;
}


double subtract( double& d1, double& d2 )
{
	return ( d1 - d2 );
}


double divide( double& d1, double& d2 )
{
	return ( d1 / d2 );
}


double func_tauRSMAG( double& d1, double& d2 )
{
	return ( -2.0 * d1 * d2 );
}


