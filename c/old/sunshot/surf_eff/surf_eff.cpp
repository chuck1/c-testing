#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main ()
{
	double T = 0;
	double q = 0;
	
	printf( "Temperature in Kelvin:" );
	
	scanf( "%lf", &T );
	
	printf( "Heat Flux:" );
	
	scanf( "%lf", &q );
	
	
	printf( "T=%f\n", T );
	printf( "q=%e\n", q );
	
	
	double T_amb = 298.15;
	double emiss = 0.95;
	double sb = 5.67 * pow(10,-8);
	
	double eff = emiss * q / ( q + 15*(T-T_amb) + emiss * sb * ( pow(T,4)-pow(T_amb,4) ) );
	
	
	printf( "efficiency=%f\n", eff );
	return 0;
}

