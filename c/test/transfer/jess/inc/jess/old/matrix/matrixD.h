#ifndef _MATRIX_D_H
#define _MATRIX_D_H


class matrixD: public matrix<double> {
public:
	void 	LinSpace(double d0,double d1,int n) {
		init(1,n);
		
		for ( int a = 0; a < n; a++ )
		{
			at(a) = d0 + ( d1-d0 ) / ( n-1 ) * a;
		}
	}
	void 	LogSpace(double d0,double d1,int n) {
		init(1,n);
		
		for ( int a = 0; a < n; a++ )
		{
			at(a) = pow( 10, d0 + ( d1-d0 ) / ( n-1 ) * a );
		}
	}
	void	zero() {
		for ( int a = 0; a < m_nbEl; a++ )
		{
			at(a) = 0;
		}
	}
	void	fill(double d) {
		for ( int a = 0; a < m_nbEl; a++ )
		{
			at(a) = d;
		}
	}
	double 	Sum() {
		double ret = 0;
		for ( int a = 0; a < m_nbEl; a++ )
		{
			ret += at(a);
		}
		return ret;
	}
	double 	Min() {
		double ret = numeric_limits<double>::infinity();
		
		for ( int a = 0; a < m_nbEl; a++ )
		{
			if ( at(a) < ret )
			{
				ret = at(a);
			}
		}
		return ret;
	}
	double 	Min(int& b) {
		double ret = numeric_limits<double>::infinity();
		b = -1;
		for ( int a = 0; a < m_nbEl; a++ )
		{
			if ( at(a) < ret )
			{
				b = a;
				ret = at(a);
			}
		}
		return ret;
	}
	void 	write(string filename) {
		filename += ".bin";
		
		ofstream ofs;
		ofs.open(filename, ios::out | ios::binary );
		
		
		int size = m_nbEl*sizeof(double);
		
		char buffer[size];
		
		memcpy(&buffer,m_data,size);
		
		ofs.write(buffer,size);
		
		ofs.close();
	}
};

void plot2D(matrixD x,matrixD y) {
	assert( x.NbEl() == y.NbEl() );
	
	x.write("x");
	y.write("y");
	
	string file = __FILE__;
	
	boost::regex e ("(.*/)(\\w+\\.h)");
	boost::smatch sm;
	
	boost::regex_match (file,sm,e);
	
	string pypath = "python ";
	pypath += sm[1];
	pypath += "../../../python/mypy/plot/plot_2D_from_bin.py -x x.bin -y y.bin";
	
	system(pypath.c_str());
}

#endif

