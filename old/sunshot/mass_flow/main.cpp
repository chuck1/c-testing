#include "../../mylib/mylib.h"

int main() {
	double T0 = 300+273.15;
	double T1 = 550+273.15;
	double p0 = 100000;
	double A = 1e-4;
	double q = 4e6;
	
	
	double dh = 0;
	double M = 0;
	
	
	
	
	Engr::TF::Material* m = new Engr::TF::Material("ms1");
	
	dh = m->EnthalpyChange( T0, T1, p0 );
	
	M = q * A / dh;
	
	printf("M=%f\n",M);
}
