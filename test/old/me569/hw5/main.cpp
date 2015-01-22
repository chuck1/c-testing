#include <vector>
#include <memory>
#include <iostream>
#include <cstdarg>
#include <cmath>
#include <string>

using namespace std;

typedef shared_ptr<vector<int> > shr_vec_int;

void error(const char* cstr,const char* file,int line)
{
	cout << file << ":" << line << ": error: " << cstr << endl;
}

shr_vec_int constructShrVecInt( int n, ... )
{
	vector<int>* v = new vector<int>;
	
	va_list args;
	
	va_start( args, n );
	
	for ( int a = 0; a < n; a++ )
	{
		v->push_back(va_arg( args, int ));
	}
	
	va_end( args );
	
	shr_vec_int sv;
	
	sv.reset(v);
	
	return sv;
}


#define ERROR(cstr) error(cstr,__FILE__,__LINE__)

#include "Branch.cpp"
#include "IVariable.cpp"
#include "HW5.cpp"
#include "Functions.cpp"





int main()
{
	HW5 hw5;
	hw5.Init();
	hw5.Process();
	
	return 0;
}

