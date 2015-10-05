#include "../../mylib/mylib.h"

matrixD u,v,P;
int nx;
int ny;
double nu;
//double nx;
//double ny;
double dx;
double dy;

/*
double v_N;
double v_S;
double v_E;
double v_W;

double u_N;
double u_S;
double u_E;
double u_W;
*/

double a_uP( int i,int J ) {
	int I = i;
	int j = J;
	
	double u_P = u.at(i,J);
	
	double u_N = 0;
	double u_S = 0;
	double u_E = u.at(i-1,J);
	double u_W = u.at(i+1,J);
	
	if ( J == (ny-1) ) {
		// no-slip wall
		u_N = -u_P;
	}
	else {
		u_N = u.at(i+0,J+1);
	}
	
	if ( J == 0 ) {
		// no-slip wall
		u_S = -u_P;
	}
	else {
		u_S = u.at(i+0,J-1);
	}
	
	
	
	
	double v_ne = v.at(I+0,j+1);
	double v_nw = v.at(I-1,j+1);
	double v_se = v.at(I+0,j);
	double v_sw = v.at(I-1,j);
	
	
	
	double F_s = -0.25 * ( v_se + v_sw ) * dx;
	double F_n =  0.25 * ( v_ne + v_nw ) * dx;
	double F_w = -0.25 * ( u_W + u_P ) * dy;
	double F_e =  0.25 * ( u_E + u_P ) * dy;
	
	double a_n = F_n - nu * dx / dy;
	double a_s = F_s - nu * dx / dy;
	double a_e = F_e - nu * dy / dx;
	double a_w = F_w - nu * dy / dx;
	
	double a_P = a_n + a_s + a_e + a_w + ( F_e - F_w ) + ( F_n - F_s );
	
	//printf("%f %f %f %f %f\n",a_n,a_s,a_e,a_w,a_P);
	
	return a_P;
}
double u_( int i,int J ) {
	int I = i;
	int j = J;
	
	double u_P = u.at(i,J);
	double u_P_old = u_P;
	
	
	
	
	double u_N = 0;
	double u_S = 0;
	double u_E = u.at(i-1,J);
	double u_W = u.at(i+1,J);
	
	if ( J == (ny-1) ) {
		// no-slip wall
		u_N = -u_P;
	}
	else {
		u_N = u.at(i+0,J+1);
	}
	
	if ( J == 0 ) {
		// no-slip wall
		u_S = -u_P;
	}
	else {
		u_S = u.at(i+0,J-1);
	}
	
	
	
	
	double v_ne = v.at(I+0,j+1);
	double v_nw = v.at(I-1,j+1);
	double v_se = v.at(I+0,j);
	double v_sw = v.at(I-1,j);
	
	double P_e = P.at(I+0,J);
	double P_w = P.at(I-1,J);
	
	double a_P = a_uP(i,J);
	
	double F_s = -0.25 * ( v_se + v_sw ) * dx;
	double F_n =  0.25 * ( v_ne + v_nw ) * dx;
	double F_w = -0.25 * ( u_W + u_P ) * dy;
	double F_e =  0.25 * ( u_E + u_P ) * dy;
	
	double a_n = F_n - nu * dx / dy;
	double a_s = F_s - nu * dx / dy;
	double a_e = F_e - nu * dy / dx;
	double a_w = F_w - nu * dy / dx;
	
	
	
	u_P = ( (P_w - P_e) * dy - a_n * u_N - a_s * u_S - a_e * u_E - a_w * u_W ) / a_P;
	
	double r = ( u_P_old - u_P );
	r = r*r;
	
	u.at(i,J) = u_P;
	
	return r;
}
double u_hat( int i,int J ) {
	int I = i;
	int j = J;
	
	double u_P = u.at(i,J);
	
	
	double u_N = u.at(i,J+0);
	double u_S = u.at(i,J-1);
	double u_E = u.at(i-1,J);
	double u_W = u.at(i+1,J);
	
	
	double v_ne = v.at(I+0,j+1);
	double v_nw = v.at(I-1,j+1);
	double v_se = v.at(I+0,j);
	double v_sw = v.at(I-1,j);
	
	double a_P = a_uP(i,J);
	
	double a_n =  0.25 * ( v_ne + v_nw ) * dx - nu * dx / dy;
	double a_s = -0.25 * ( v_se + v_sw ) * dx - nu * dx / dy;
	double a_e =  0.25 * ( u_E + u_P ) * dy   - nu * dy / dx;
	double a_w = -0.25 * ( u_W + u_P ) * dy   - nu * dy / dx;
	
	
	u_P = ( 0 - a_n * u_N - a_s * u_S - a_e * u_E - a_w * u_W ) / a_P;
	
	return u_P;
}

double a_vP( int I,int j ) {
	int i = I;
	int J = j;
	
	double v_P = v.at(I,j);
	
	
	
	double v_N = v.at(I,j+1);
	double v_S = v.at(I,j-1);
	double v_E = 0;
	double v_W = 0;
	
	if ( I == (nx-1) ) {
		v_E = v_P;
	}
	else {
		v_E = v.at(I+1,j);
	}
	
	if ( I == 0 ) {
		v_W = v_P;
	}
	else {
		v_W = v.at(I-1,j);
	}
	
	
	
	double u_ne = u.at(i+1,J);
	double u_nw = u.at(i+0,J);
	double u_se = u.at(i+1,J-1);
	double u_sw = u.at(i+0,J-1);
	
	double F_s = -0.25 * ( v_S + v_P ) * dx;
	double F_n =  0.25 * ( v_N + v_P ) * dx;
	double F_w = -0.25 * ( u_nw + u_sw ) * dy;
	double F_e =  0.25 * ( u_ne + u_se ) * dy;
	
	double a_n = F_n - nu * dx / dy;
	double a_s = F_s - nu * dx / dy;
	double a_e = F_e - nu * dy / dx;
	double a_w = F_w - nu * dy / dx;
	
	double a_P = a_s + a_n + a_e + a_w + ( F_e - F_w ) + ( F_n - F_s );
	
	return a_P;
}
double v_( int I, int j ) {
	int i = I;
	int J = j;
	
	double a_P = a_vP(I,j);
	
	double v_P = v.at(I,j);
	double v_P_old = v_P;
	
	
	double v_N = v.at(I,j+1);
	double v_S = v.at(I,j-1);
	double v_E = 0;
	double v_W = 0;
	
	if ( I == (nx-1) ) {
		v_E = v_P;
	}
	else {
		v_E = v.at(I+1,j);
	}
	
	if ( I == 0 ) {
		v_W = v_P;
	}
	else {
		v_W = v.at(I-1,j);
	}
	
	
	double u_ne = u.at(i+1,J);
	double u_nw = u.at(i+0,J);
	double u_se = u.at(i+1,J-1);
	double u_sw = u.at(i+0,J-1);
	
	double P_n = P.at(I,J+0);
	double P_s = P.at(I,J-1);
	
	double F_s = -0.25 * ( v_S + v_P ) * dx;
	double F_n =  0.25 * ( v_N + v_P ) * dx;
	double F_w = -0.25 * ( u_nw + u_sw ) * dy;
	double F_e =  0.25 * ( u_ne + u_se ) * dy;
	
	double a_N = F_n - nu * dx / dy;
	double a_S = F_s - nu * dx / dy;
	double a_E = F_e - nu * dy / dx;
	double a_W = F_w - nu * dy / dx;
	
	//printf("v_ a_P = %f\n",a_P);
	
	v_P = ( (P_s - P_n) * dy - a_N * v_N - a_S * v_S - a_E * v_E - a_W * v_W ) / a_P;
	
	double r = ( v_P_old - v_P );
	r = r*r;
	
	v.at(I,j) = v_P;
	
	return r;
}
double v_hat( int I, int j ) {
	int i = I;
	int J = j;
	
	double a_P = a_vP(I,j);
	
	double v_P = v.at(I,j);
	double v_N = v.at(I,j+1);
	double v_S = v.at(I,j-1);
	double v_E = v.at(I+1,j);
	double v_W = v.at(I-1,j);
	double u_ne = u.at(i+1,J);
	double u_nw = u.at(i,J);
	double u_se = u.at(i+1,J-1);
	double u_sw = u.at(i,J-1);
	
	double a_N =  0.25 * ( v_N + v_P ) * dx   - nu * dx / dy;
	double a_S = -0.25 * ( v_S + v_P ) * dx   - nu * dx / dy;
	double a_E =  0.25 * ( u_ne + u_se ) * dy - nu * dy / dx;
	double a_W = -0.25 * ( u_nw + u_sw ) * dy - nu * dy / dx;


	v_P = ( 0 - a_N * v_N - a_S * v_S - a_E * v_E - a_W * v_W ) / a_P;
	
	return v_P;
}

double P_( int I, int J ) {
	int i = I;
	int j = J;
	
	double P_N = 0;
	double P_S = 0;
	double P_E = 0;
	double P_W = 0;
	
	double a_N = 0;
	double a_S = 0;
	double a_E = 0;
	double a_W = 0;
	
	if ( J == (ny-1) ) {
	
	}
	else {
		double d_n = a_vP(I,j+1) / dx;
		a_N = d_n * dx;
		
		P_N = P.at(I,J+1);
	}
	
	if ( J == 0 ) {
	
	}
	else {
		double d_s = a_vP(I,j+0) / dx;
		a_S = d_s * dx;
		
		P_S = P.at(I,J-1);
	}
	
	if ( I == (nx-1) ) {
	
	}
	else {
		double d_e = a_uP(i+1,J) / dy;
		a_E = d_e * dy;
		
		P_E = P.at(I+1,J);
	}
	
	if ( I == 0 ) {
	
	}
	else {
		double d_w = a_uP(i+0,J) / dy;
		a_W = d_w * dy;
		
		P_W = P.at(I-1,J);
	}
	
	//printf("1\n");
	
	
	double vh_n = v.at(I+0,j+1);
	double vh_s = v.at(I+0,j+0);
	double uh_e = u.at(i+1,J+0);
	double uh_w = u.at(i+0,J+0);
	
	//printf("2\n");
	
	/*
	double vh_n = v_hat(I+0,j+1);
	double vh_s = v_hat(I+0,j+0);
	double uh_e = u_hat(i+1,J);
	double uh_w = u_hat(i+0,J);
	*/
	
	
	
	double a_P = a_N + a_S + a_E + a_W;
	
	double b = ( uh_w - uh_e ) * dy + ( vh_s - vh_n ) * dx;
	
	double P_P = ( a_N * P_N + a_S * P_S + a_E * P_E + a_W * P_W + b ) / a_P;
	
	//printf("a_P=%f\n",a_P);
	
	
	double r = P_P - P.at(I,j);
	r = r*r;
	
	P.at(I,j) = P_P;
	
	return r;
}

void mom() {
	double r = 0;
	
	// interior
	
	for ( int i = 1; i < nx; i++ ) {
		for ( int J = 0; J < ny; J++ ) {
			r += u_(i,J);
		}
	}
	
	for ( int I = 0; I < nx; I++ ) {
		for ( int j = 1; j < ny; j++ ) {
			r += v_(I,j);
		}
	}
	
	// outlet
	{
		int i = nx;
		for ( int J = 0; J < ny; J++ ) {
			u.at(i,J) = u.at(i-1,J);
		}
	}
	
	
	printf("mom %f\n",r);

}

void pres() {
	double r = 0;
	
	for ( int I = 0; I < nx; I++ ) {
		for ( int J = 0; J < ny; J++ ) {
			r += P_(I,J);
		}
	}
	
	printf("pres %f\n",r);
}


int main() {
	nx = 10;
	ny = 10;
	dx = 0.1;
	dy = 0.1;
	nu = 1e-5;
	
	u.init(2,nx+1,ny);
	v.init(2,nx,ny+1);
	P.init(2,nx,ny);
	
	// initialize
	u.fill(1);
	v.zero();
	P.zero();
	
	// inlet condition
	{
		int i = 0;
		for ( int J = 0; J < ny; J++ ) {
			u.at(i,J) = 1;
		}
	}
	
	for ( int a = 0; a < 100; a++ ) {
		mom();
	}
	for ( int a = 0; a < 10; a++ ) {
		pres();
	}
	
	u.write("u");
	
}





