#include <iostream>
#include <cstdarg>

#include <cmath>
#include <string>
#include <memory>

#include "Functions.h"
#include "Branch.h"
#include "IVariable.h"
#include "HW5.h"

using namespace std;




/*
bool Ensure_uLES()
{
	if (m_uLES.isEmpty())
	{
		m_uLES.Init( m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
		
		if (!m_uLES.Load("calc_data/uLES.bin"))
		{
			if (!Ensure_uLES())
				return false;
			
			
			
			if (!m_uLES.Save("calc_data/uLES.bin"))
				return false;
		}
	}
	return true;
}
bool Ensure_uuLES()
{
	if (m_uuLES.isEmpty())
	{
		m_uuLES.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
		
		if (!m_uuLES.Load("calc_data/uuLES.bin"))
		{
			if (!Ensure_uLES())
				return false;
			
			pointCorr( m_uuLES, m_uLES, m_uLES );
			cout << "uuLES calculated\n";
			
			if (!m_uuLES.Save("calc_data/uuLES.bin"))
				return false;
		}
	}
	return true;
}
bool Ensure_uufLES()
{
	if (m_uufLES.isEmpty())
	{
		m_uufLES.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
		
		if (!m_uufLES.Load("calc_data/uufLES.bin"))
		{
			if (!Ensure_uuLES())
				return false;
			
			topHat( m_uuLES, m_uufLES );
			cout << "uufLES calculated\n";
			
			if (!m_uufLES.Save("calc_data/uufLES.bin"))
				return false;
		}
	}
	return true;
}
bool Ensure_ufufLES()
{
	
}
bool Ensure_tauRDNS()
{
	if ( m_tauRDNS.isEmpty() )
	{
		m_tauRDNS.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
		
		if (!m_tauRDNS.Load("calc_data/tauRDNS.bin"))
		{
			if (!Ensure_uufLES())
				return false;
			if (!Ensure_ufufLES())
				return false;
			
			m_tauRDNS.ElementwiseOperation( m_uufLES, m_ufufLES, subtract );
			cout << "tauRDNS calculated\n";
			
			if (!m_tauRDNS.Save( "calc_data/tauRDNS.bin" ))
				return false;
		}
	}
	return true;
}
bool Ensure_tauRSMAG()
{

}
bool Ensure_tauRSFS()
{

}
bool Ensure_tauRDSM()
{

}
void Ensure_filenames()
{
	if (m_filenames.isEmpty())
	{
		m_filenames.Init(3,3);
		
		Load_filenames();
	}
}


void Calculate_DynamicSmag()
{
	// Initialize
	cout << "Initializing\n";
	
	m_tauRDSM.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	
	m_ufuftLES.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	
	m_uftLES.Init( m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	m_uftuftLES.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	
	m_L.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	m_M.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	
	m_S.Init( m_ntime, m_nkLES, m_nj, m_niLES );
	m_St.Init( m_ntime, m_nkLES, m_nj, m_niLES );
	
	m_Sft.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	
	m_SSf.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	m_SSft.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	
	m_ML.Init( m_ntime, m_nkLES, m_nj, m_niLES );
	m_MM.Init( m_ntime, m_nkLES, m_nj, m_niLES );
	m_MLmean.Init( m_nj );
	m_MMmean.Init( m_nj );
	
	m_Cd.Init( m_nj );
	
	// Calculate
	cout << "Calculating\n";
	topHat2( m_ufLES, m_uftLES );
	cout << "Calculating\n";
	pointCorr( m_uftuftLES, m_uftLES, m_uftLES );
	cout << "Calculating\n";
	topHat2( m_ufufLES, m_ufuftLES );
	cout << "Calculating\n";
	m_L.ElementwiseOperation( m_ufuftLES, m_uftuftLES, subtract );
	
	cout << "Calculating\n";
	Calc_S();
	cout << "S calculated\n";
	
	topHat2( m_S, m_St );
	topHat2( m_Sf, m_Sft );
	
	Calc_SSf();
	
	topHat2( m_SSf, m_SSft );
	
	Calc_M();
	cout << "M calculated\n";
	
	Calc_ML();
	cout << "ML calculated\n";
	Calc_MM();
	cout << "MM calculated\n";
	
	mean( m_ML, m_MLmean );
	cout << "MLmean calculated\n";
	mean( m_MM, m_MMmean );
	cout << "MMmean calculated\n";
	
	m_Cd.ElementwiseOperation( m_MLmean, m_MMmean, divide );
	cout << "Cd calculated\n";
	
	Calc_tauRDSM();
	cout << "tauRDSM calculated\n";
}

bool Load_y()
{
	if (m_y.isEmpty())
	{
		m_y.Init( m_nj );
		
		if ( !Load1DBinary( m_y, "raw_data/y.bin" ) )
			return false;
	}
	
	return true;
}


//void diff( Mat5D<double>& orig, Mat6D<double>& der );


void Calc_nuSMAGSGS()
{
	double cs = 0.1;
	
	for ( int a = 0; a < m_Sf.GetDim(0); a++ )
	{
		for ( int b = 0; b < m_Sf.GetDim(1); b++ )
		{
			for ( int c = 0; c < m_Sf.GetDim(2); c++ )
			{
				for ( int d = 0; d < m_Sf.GetDim(3); d++ )
				{
					for ( int e = 0; e < m_Sf.GetDim(4); e++ )
					{
						for ( int f = 0; f < m_Sf.GetDim(5); f++ )
						{
							double yplus = m_y.Get(e) * m_Retau;
							double fmu = 1.0 - exp( -yplus/26.0 );
							
							m_nuSMAGSGS.Get(a,b,c,d,e,f) = pow( cs * fmu * m_dfilter ,2.0 )
								* sqrt( 2.0 * m_Sf.Get(a,b,c,d,e,f) * m_Sf.Get(a,b,c,d,e,f) );
						}
					}
				}
			}
		}
	}
}

void Calc_ufufLES()
{
	for ( int a = 0; a < m_ufufLES.GetDim(0); a++ )
	{
		for ( int b = 0; b < m_ufufLES.GetDim(1); b++ )
		{
			for ( int c = 0; c < m_ufufLES.GetDim(2); c++ )
			{
				for ( int d = 0; d < m_ufufLES.GetDim(3); d++ )
				{
					for ( int e = 0; e < m_ufufLES.GetDim(4); e++ )
					{
						for ( int f = 0; f < m_ufufLES.GetDim(5); f++ )
						{
							m_ufufLES.Get(a,b,c,d,e,f) = m_ufLES.Get(a,c,d,e,f) * m_ufLES.Get(b,c,d,e,f);
						}
					}
				}
			}
		}
	}
}

void Calc_tauRSFS()
{
	for ( int a = 0; a < m_tauRSFS.GetDim(0); a++ )
	{
		for ( int b = 0; b < m_tauRSFS.GetDim(1); b++ )
		{
			for ( int c = 0; c < m_tauRSFS.GetDim(2); c++ )
			{
				for ( int d = 0; d < m_tauRSFS.GetDim(3); d++ )
				{
					for ( int e = 0; e < m_tauRSFS.GetDim(4); e++ )
					{
						for ( int f = 0; f < m_tauRSFS.GetDim(5); f++ )
						{
							m_tauRSFS.Get(a,b,c,d,e,f) = m_ufuffLES.Get(a,b,c,d,e,f) - m_uffLES.Get(a,c,d,e,f) * m_uffLES.Get(b,c,d,e,f);
						}
					}
				}
			}
		}
	}
}

void Calc_S()
{
	for ( int c = 0; c < m_Sf.GetDim(2); c++ )
	{
		for ( int d = 0; d < m_Sf.GetDim(3); d++ )
		{
			for ( int e = 0; e < m_Sf.GetDim(4); e++ )
			{
				for ( int f = 0; f < m_Sf.GetDim(5); f++ )
				{
					m_S.Get(c,d,e,f) = 0.0;
					
					for ( int a = 0; a < m_Sf.GetDim(0); a++ )
					{
						for ( int b = 0; b < m_Sf.GetDim(1); b++ )
						{
							m_S.Get(c,d,e,f) += 
								sqrt( 2.0 * m_Sf.Get(a,b,c,d,e,f) * m_Sf.Get(a,b,c,d,e,f) );
						}
					}
				}
			}
		}
	}
}

void Calc_SSf()
{
	for ( int a = 0; a < m_Sf.GetDim(0); a++ )
	{
		for ( int b = 0; b < m_Sf.GetDim(1); b++ )
		{
			for ( int c = 0; c < m_Sf.GetDim(2); c++ )
			{
				for ( int d = 0; d < m_Sf.GetDim(3); d++ )
				{
					for ( int e = 0; e < m_Sf.GetDim(4); e++ )
					{
						for ( int f = 0; f < m_Sf.GetDim(5); f++ )
						{
							m_SSf.Get(a,b,c,d,e,f) = m_S.Get(c,d,e,f) * m_Sf.Get(a,b,c,d,e,f);
						}
					}
				}
			}
		}
	}
}

void Calc_M()
{
	for ( int a = 0; a < m_Sf.GetDim(0); a++ )
	{
		for ( int b = 0; b < m_Sf.GetDim(1); b++ )
		{
			for ( int c = 0; c < m_Sf.GetDim(2); c++ )
			{
				for ( int d = 0; d < m_Sf.GetDim(3); d++ )
				{
					for ( int e = 0; e < m_Sf.GetDim(4); e++ )
					{
						for ( int f = 0; f < m_Sf.GetDim(5); f++ )
						{
							m_M.Get(a,b,c,d,e,f) = 
								2.0 * m_dfilter * m_dfilter * 
								m_SSft.Get(a,b,c,d,e,f) -
								2.0 * m_dfiltert * m_dfiltert *
								m_St.Get(c,d,e,f) * m_Sft.Get(a,b,c,d,e,f);
						}
					}
				}
			}
		}
	}
}

void Calc_ML()
{
	for ( int c = 0; c < m_Sf.GetDim(2); c++ )
	{
		for ( int d = 0; d < m_Sf.GetDim(3); d++ )
		{
			for ( int e = 0; e < m_Sf.GetDim(4); e++ )
			{
				for ( int f = 0; f < m_Sf.GetDim(5); f++ )
				{
					m_ML.Get(c,d,e,f) = 0.0;
					
					for ( int a = 0; a < m_Sf.GetDim(0); a++ )
					{
						for ( int b = 0; b < m_Sf.GetDim(1); b++ )
						{
							m_ML.Get(c,d,e,f) += m_M.Get(a,b,c,d,e,f) * m_L.Get(a,b,c,d,e,f);
						}
					}
				}
			}
		}
	}
}

void Calc_MM()
{
	for ( int c = 0; c < m_Sf.GetDim(2); c++ )
	{
		for ( int d = 0; d < m_Sf.GetDim(3); d++ )
		{
			for ( int e = 0; e < m_Sf.GetDim(4); e++ )
			{
				for ( int f = 0; f < m_Sf.GetDim(5); f++ )
				{
					m_MM.Get(c,d,e,f) = 0.0;
					
					for ( int a = 0; a < m_Sf.GetDim(0); a++ )
					{
						for ( int b = 0; b < m_Sf.GetDim(1); b++ )
						{
							m_MM.Get(c,d,e,f) += m_M.Get(a,b,c,d,e,f) * m_M.Get(a,b,c,d,e,f);
						}
					}
				}
			}
		}
	}
}

void Calc_tauRDSM()
{
	for ( int a = 0; a < m_tauRDSM.GetDim(0); a++ )
	{
		for ( int b = 0; b < m_tauRDSM.GetDim(1); b++ )
		{
			for ( int c = 0; c < m_tauRDSM.GetDim(2); c++ )
			{
				for ( int d = 0; d < m_tauRDSM.GetDim(3); d++ )
				{
					for ( int e = 0; e < m_tauRDSM.GetDim(4); e++ )
					{
						for ( int f = 0; f < m_tauRDSM.GetDim(5); f++ )
						{
							m_tauRDSM.Get(a,b,c,d,e,f) =
								-2.0 * m_Cd.Get(e) * m_dfilter * m_dfilter *
								m_S.Get(c,d,e,f) * m_Sf.Get(a,b,c,d,e,f);
						}
					}
				}
			}
		}
	}
}



//Mat1D<double>		m_y;

//Mat5D<double>		m_u;

Mat5D<double>		m_up;
Mat6D<double>		m_upup;

Mat3D<double>		m_upupmean;
Mat2D<double>		m_umean;

Mat5D<double>		m_uLES;
Mat5D<double>		m_ufLES;
Mat5D<double>		m_uffLES;
Mat6D<double>		m_uuLES;
Mat6D<double>		m_uufLES;
Mat6D<double>		m_ufufLES;
Mat6D<double>		m_ufuffLES;

Mat6D<double>		m_tauRDNS;

Mat6D<double>		m_dufLESdx;
Mat6D<double>		m_Sf;
Mat6D<double>		m_nuSMAGSGS;
Mat6D<double>		m_tauRSMAG;

Mat6D<double>		m_tauRSFS;

// Dynamic Smag
Mat6D<double>		m_tauRDSM;

Mat6D<double>		m_ufuftLES;

Mat5D<double>		m_uftLES;
Mat6D<double>		m_uftuftLES;


Mat6D<double>		m_L;
Mat6D<double>		m_M;

Mat4D<double>		m_ML;
Mat4D<double>		m_MM;
Mat1D<double>		m_MLmean;
Mat1D<double>		m_MMmean;

Mat6D<double>		m_Sft;

Mat6D<double>		m_SSf;
Mat6D<double>		m_SSft;

Mat4D<double>		m_S;
Mat4D<double>		m_St;

Mat1D<double>		m_Cd;




//Mat2D<char*>		m_filenames;

// Objects
	

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


bool HW5::Process()
{
	m_ni = 96;
	m_nj = 49;
	m_nk = 96;
	
	m_niLES = 24;
	m_nkLES = 24;
	
	m_ndim = 3;
	m_ntime = 3;
	
	m_dx = 0.1;
	m_dz = 0.1;
	m_dxLES = m_dx*4.0;
	m_dzLES = m_dz*4.0;
	
	m_Retau = 500.0;
	
	m_dfilter = 2.0 * sqrt( m_dxLES * m_dzLES );
	m_dfiltert = 2.0 * m_dfilter;
	
	
	sptr_IVarD pumean = GetVarD("umean");
	assert(pumean);
	
	pumean->Ensure();
	
	// Ensure_u();
	
	
	/*
	if (!Load_y())
		return false;
	*/
	
	
	
	/*
	
	m_upup.Init( m_ndim, m_ndim, m_ntime, m_nk, m_nj, m_ni );
	pointCorr( m_upup, m_up, m_up );
	cout << "upup == tau calculated\n";
	
	m_uLES.Init( m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	sample( m_u, m_uLES );
	cout << "uLES calculated\n";
	
	
	
	m_ufLES.Init( m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	topHat( m_uLES, m_ufLES );
	cout << "ufLES calculated\n";
	
	
	
	m_ufufLES.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	Calc_ufufLES();
	cout << "ufufLES calculated\n";
	
	m_ufuffLES.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	topHat( m_ufufLES, m_ufuffLES );
	cout << "ufuffLES calculated\n";
	
	m_uffLES.Init( m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	topHat( m_ufLES, m_uffLES );
	cout << "uffLES calculated\n";
	
	m_dufLESdx.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	diff( m_ufLES, m_dufLESdx );
	cout << "dufLESdx calculated\n";
	
	m_Sf.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	thisHasAName1( m_dufLESdx, m_Sf );
	cout << "Sf calculated\n";
	
	m_nuSMAGSGS.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	Calc_nuSMAGSGS();
	cout << "nuSMAGSGS calculated\n";
	
	
	
	
	
	
	
	m_tauRSMAG.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	m_tauRSMAG.ElementwiseOperation( m_nuSMAGSGS, m_Sf, func_tauRSMAG );
	cout << "tauRSMAG calculated\n";
	
	
	
	m_tauRSFS.Init( m_ndim, m_ndim, m_ntime, m_nkLES, m_nj, m_niLES );
	Calc_tauRSFS();
	cout << "tauRSFS calculated\n";
	
	Calculate_DynamicSmag();
	
	
	
	
	
	Ensure_tauRDNS();
	Ensure_tauRSMAG();
	Ensure_tauRSFS();
	Ensure_tauRDSM();
	
	*/
	
	return true;
}



