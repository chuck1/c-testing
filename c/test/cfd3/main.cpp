#include "../../mylib/mylib.h"
#include <algorithm>

//#define MYDEBUG

matrixD u,v,p,pp,xu,yv,x,y;
int nx, ny;
double mu, rho;
double dx, dy;

namespace u_ {

	double _a( int i, int J );
	double _a_w( int i, int J );
	double _a_e( int i, int J );
	double _a_s( int i, int J );
	double _a_n( int i, int J );
	
	double _D_w( int i, int J ) {
		return ( mu / ( xu.at(i) - xu.at(i-1) ) );
	}
	double _D_e( int i, int J ) {
		return ( mu / ( xu.at(i+1) - xu.at(i) ) );
	}
	double _D_s( int i, int J ) {
		int j = J;
		if ( J == ( 0 ) ) {
			return ( mu / ( y.at(J) - yv.at(j) ) );
		}
		else {
			return ( mu / ( y.at(J) - y.at(J-1) ) );
		}
	}
	double _D_n( int i, int J ) {
		int j = J;
		if ( J == ( ny - 1 ) ) {
			return ( mu / ( yv.at(j+1) - y.at(J) ) );
		}
		else {
			return ( mu / ( y.at(J+1) - y.at(J) ) );
		}
	}
	
	double _F_w( int i, int J ) {
		return ( rho * ( u.at(i,J) + u.at(i-1,J) ) / 2 );
	}
	double _F_e( int i, int J ) {
		return ( rho * ( u.at(i,J) + u.at(i+1,J) ) / 2 );
	}
	double _F_s( int i, int J ) {
		int I = i;
		int j = J;
		return ( rho * ( v.at(I-1,j+0) + v.at(I,j+0) ) / 2 );
	}
	double _F_n( int i, int J ) {
		int I = i;
		int j = J;
		return ( rho * ( v.at(I-1,j+1) + v.at(I,j+1) ) / 2 );
	}
	
	double _a( int i, int J ) {
		return ( 
			_a_n(i,J) + 
			_a_s(i,J) + 
			_a_e(i,J) + 
			_a_w(i,J) + 
			( _F_e(i,J) - _F_w(i,J) ) + 
			( _F_n(i,J) - _F_s(i,J) ) );
	}
	double _a_w( int i, int J ) {
		
		return ( _D_w(i,J) + _F_w(i,J) / 2 );
		//return ( _D_w(i,J) + max( _F_w(i,J), 0.0 ) );
	}
	double _a_e( int i, int J ) {
		return ( _D_e(i,J) - _F_e(i,J) / 2 );
		//return ( _D_e(i,J) + max( 0.0, -_F_e(i,J) ) );
	}
	double _a_s( int i, int J ) {
		return ( _D_s(i,J) + _F_s(i,J) / 2 );
		//return ( _D_s(i,J) + max( _F_s(i,J), 0.0 ) );
	}
	double _a_n( int i, int J ) {
		return ( _D_n(i,J) - _F_n(i,J) / 2 );
		//return ( _D_n(i,J) + max( 0.0, -_F_n(i,J) ) );
	}
	
	double _u_w( int i, int J ) {
		return ( u.at(i-1,J) );
	}
	double _u_e( int i, int J ) {
		return ( u.at(i+1,J) );
	}
	double _u_s( int i, int J ) {
		if ( J == ( 0 ) ) {
			return 0.0;
		}
		else {
			return ( u.at(i,J-1) );
		}
	}
	double _u_n( int i, int J ) {
		if ( J == ( ny - 1 ) ) {
			return 0.0;
		}
		else {
			return ( u.at(i,J+1) );
		}
	}
	
	double _A( int i, int J ) {
		return ( dy );
	}
	double _b( int i, int J ) {
		return ( 0 );
	}
	double _d( int i, int J ) {
		return ( _A(i,J) / _a(i,J) );
	}
	
	double step_1() {
		double r = 0;
		double u_old = 0;
		
		for ( int i = 1; i < nx; i++ ) {
			for ( int J = 0; J < ny; J++ ) {
				int I = i;
				
				u_old = u.at(i,J);
				
				#ifdef MYDEBUG
				printf("       F_w       F_e       F_s       F_n\n");
				printf("%10.3e%10.3e%10.3e%10.3e\n",
					_F_w(i,J), _F_e(i,J), _F_s(i,J), _F_n(i,J) );
				printf("       a_w       u_w       a_e       u_e       a_s       u_s       a_n       u_n\n");
				printf("%10.3e%10.3e%10.3e%10.3e%10.3e%10.3e%10.3e%10.3e\n",
					_a_w(i,J), _u_w(i,J),
					_a_e(i,J), _u_e(i,J), 
					_a_s(i,J), _u_s(i,J), 
					_a_n(i,J), _u_n(i,J) ); 
				printf("       p_w       p_e         A         b         a       a/a\n");
				printf("%10.3e%10.3e%10.3e%10.3e%10.3e%10.3e\n",
					p.at(I-1,J), p.at(I,J), _A(i,J), _b(i,J), _a(i,J),
					((_a_w(i,J)+_a_e(i,J)+_a_s(i,J)+_a_n(i,J))/_a(i,J)) );
				#endif
				
				u.at(i,J) = ( 
					_a_w(i,J) * _u_w(i,J) +
					_a_e(i,J) * _u_e(i,J) + 
					_a_s(i,J) * _u_s(i,J) + 
					_a_n(i,J) * _u_n(i,J) + 
					( p.at(I-1,J) - p.at(I,J) ) * _A(i,J) + 
					_b(i,J) ) / _a(i,J);
				
				#ifdef MYDEBUG
				printf("         u\n");
				printf("%10.3e\n", u.at(i,J) );
				#endif
				
				if (  u.at(i,J) != 0 ) {
					r += abs( ( u_old - u.at(i,J) ) / u.at(i,J) );
				}
			}
		}
		
		// outlet
		{
			int i = nx;
			for ( int J = 0; J < ny; J++ ) {
				u.at(i,J) = u.at(i-1,J);
			}
		}
		
		return sqrt(r);
	}
	void step_3() {
		for ( int i = 1; i < nx; i++ ) {
			for ( int J = 0; J < ny; J++ ) {
				int I = i;
				
				u.at(i,J) = u.at(i,J) + _d(i,J) * ( pp.at(I-1,J) - pp.at(I,J) );
			}
		}
	}
	
}
namespace v_ {
	double _a( int I, int j );
	double _a_w( int I, int j );
	double _a_e( int I, int j );
	double _a_s( int I, int j );
	double _a_n( int I, int j );
	
	double _D_w( int I, int j ) {
		int i = I;
		if ( I == 0 ) {
			return ( mu / ( x.at(I) - xu.at(i) ) );
		}
		else {
			return ( mu / ( x.at(I) - x.at(I-1) ) );
		}
	}
	double _D_e( int I, int j ) {
		int i = I;
		if ( I == ( nx - 1 ) ) {
			return ( mu / ( xu.at(i+1) - x.at(I) ) );
		}
		else {
			return ( mu / ( x.at(I+1) - x.at(I) ) );
		}
	}
	double _D_s( int I, int j ) {
		return ( mu / ( yv.at(j+0) - yv.at(j-1) ) );
	}
	double _D_n( int I, int j ) {
		return ( mu / ( yv.at(j+1) - yv.at(j) ) );
	}
	
	double _F_w( int I, int j ) {
		int i = I;
		int J = j;
		
		return ( rho * ( u.at(i+0,J-1) + u.at(i+0,J) ) / 2 );
	}
	double _F_e( int I, int j ) {
		int i = I;
		int J = j;
		
		return ( rho * ( u.at(i+1,J-1) + u.at(i+1,J) ) / 2 );
	}
	double _F_s( int I, int j ) {
		return ( rho * ( v.at(I,j) + v.at(I,j-1) ) / 2 );
	}
	double _F_n( int I, int j ) {
		return ( rho * ( v.at(I,j) + v.at(I,j+1) ) / 2 );
	}
	
	double _a( int I, int j ) {
		return ( 
			_a_n(I,j) + 
			_a_s(I,j) + 
			_a_e(I,j) + 
			_a_w(I,j) + 
			( _F_e(I,j) - _F_w(I,j) ) + 
			( _F_n(I,j) - _F_s(I,j) ) );
	}
	double _a_w( int I, int j ) {
		return ( _D_w(I,j) + _F_w(I,j) / 2.0 );
		//return ( _D_w(I,j) + max( _F_w(I,j), 0.0 ) );
	}
	double _a_e( int I, int j ) {
		return ( _D_e(I,j) - _F_e(I,j) / 2.0 );
		//return ( _D_e(I,j) + max( 0.0, -_F_e(I,j) ) );
	}
	double _a_s( int I, int j ) {
		return ( _D_s(I,j) + _F_s(I,j) / 2.0 );
		//return ( _D_s(I,j) + max( _F_s(I,j), 0.0 ) );
	}
	double _a_n( int I, int j ) {
		return ( _D_n(I,j) - _F_n(I,j) / 2.0 );
		//return ( _D_n(I,j) + max( 0.0, -_F_n(I,j) ) );
	}
	
	double _v_w( int I, int j ) {
		if ( I == ( 0 ) ) {
			return 0.0;
		}
		else {
			return ( v.at(I-1,j) );
		}
	}
	double _v_e( int I, int j ) {
		if ( I == ( nx - 1 ) ) {
			return 0.0;
		}
		else {
			return ( v.at(I+1,j) );
		}
	}
	double _v_s( int I, int j ) {
		return ( v.at(I,j-1) );
	}
	double _v_n( int I, int j ) {
		return ( v.at(I,j+1) );
	}

	double _A( int i, int J ) {
		return ( dx );
	}
	double _b( int i, int J ) {
		return ( 0 );
	}
	double _d( int I, int j ) {
		return ( _A(I,j) / _a(I,j) );
	}
	
	double step_1() {
		double r = 0;
		double v_old = 0;
		
		for ( int I = 0; I < nx; I++ ) {
			for ( int j = 1; j < ny; j++ ) {
				int J = j;
				
				v_old = v.at(I,j);
				
				v.at(I,j) = ( 
					_a_n(I,j) * _v_n(I,j) + 
					_a_s(I,j) * _v_s(I,j) + 
					_a_e(I,j) * _v_e(I,j) + 
					_a_w(I,j) * _v_w(I,j) +
					( p.at(I,J-1) - p.at(I,J) ) * _A(I,j) + 
					_b(I,j) ) / _a(I,j);
				
				if ( v.at(I,j) != 0 ) {
					r += abs( ( v_old - v.at(I,j) ) / v.at(I,j) );
				}
			}
		}
		
		
		
		return sqrt(r);
	}
	void step_3() {
		for ( int I = 0; I < nx; I++ ) {
			for ( int j = 1; j < ny; j++ ) {
				int J = j;
				
				v.at(I,j) = v.at(I,j) + _d(I,j) * ( pp.at(I,J-1) - pp.at(I,J) );
			}
		}
	}
	
}
namespace p_ {

	double _a_w( int I, int J ) {
		return ( rho * dy );
	}
	double _a_e( int I, int J ) {
		return ( rho * dy );
	}
	double _a_s( int I, int J ) {
		return ( rho * dx );
	}
	double _a_n( int I, int J ) {
		return ( rho * dx );
	}
	double _a( int I, int J ) {
		return ( _a_w(I,J) + _a_e(I,J) + _a_s(I,J) + _a_n(I,J) );
	}
	double _b( int I, int J ) {
		int i = I;
		int j = J;
		
		return ( 
			_a_w(I,J) * u.at(i,J) -
			_a_e(I,J) * u.at(i+1,J) +
			_a_s(I,J) * v.at(I,j) -
			_a_n(I,J) * v.at(I,j+1) );
	}

	double _pp_w( int I, int J ) {
		if ( I == 0 ) {
			return 0.0;
		}
		else {
			return ( pp.at(I-1,J) );
		}
	}
	double _pp_e( int I, int J ) {
		if ( I == ( nx - 1 ) ) {
			return 0.0;
		}
		else {
			return ( pp.at(I+1,J) );
		}
	}
	double _pp_s( int I, int J ) {
		if ( J == 0 ) {
			return 0.0;
		}
		else {
			return ( pp.at(I,J-1) );
		}
	}
	double _pp_n( int I, int J ) {
		if ( J == ( ny - 1 ) ) {
			return 0.0;
		}
		else {
			return ( pp.at(I,J+1) );
		}
	}

	double step_2() {
		double r = 0;
		double pp_old;
		
		for ( int I = 0; I < nx; I++ ) {
			for ( int J = 0; J < ny; J++ ) {
				pp_old = pp.at(I,J);
				
				pp.at(I,J) = (
					_a_w(I-1,J) * _pp_w(I,J) +
					_a_e(I+1,J) * _pp_e(I,J) +
					_a_s(I,J-1) * _pp_s(I,J) +
					_a_n(I,J+1) * _pp_n(I,J) +
					_b(I,J) ) / _a(I,J);
				
				r += abs( ( pp_old - pp.at(I,J) ) / pp.at(I,J) );
			}
		}
		
		return sqrt(r);
	}
	
}



void step_1() {
	double r_u = 0;
	double r_v = 0;
	
	for ( int a = 0; a < 1000; a++ ) {
		r_u = u_::step_1();
		r_v = v_::step_1();
		
		printf("momentum%10.3e%10.3e\n",r_u,r_v);
		
		if ( ( r_u + r_v ) < 1e-4 ) {
			printf("momentum converged\n");
			break;
		}
	}
}
void step_2() {
	double res = 0;
	for ( int a = 0; a < 1000; a++ ) {
		
		res = p_::step_2();
		printf("pressure%10.3e\n",res);
		
		if ( res < 1e-4 ) {
			printf("pressure converged\n");
			break;
		}
	}
}
void step_3() {
	for ( int I = 0; I < nx; I++ ) {
		for ( int J = 0; J < ny; J++ ) {
			p.at(I,J) = p.at(I,J) + pp.at(I,J);
		}
	}
	
	u_::step_3();
	v_::step_3();
	
}

int iter() {
	step_1();
	step_2();
	step_3();
}

int setup() {
	nx = 100;
	ny = 20;
	
	dx = 0.1;
	dy = 0.1;
	
	mu = 1;
	rho = 1;
	
	u.init(2,nx+1,ny+0);
	v.init(2,nx+0,ny+1);
	
	p.init( 2,nx,ny);
	pp.init(2,nx,ny);
	
	xu.init(1,nx+1);
	yv.init(1,ny+1);
	
	x.init(1,nx);
	y.init(1,ny);
	
	for ( int i = 0; i < (nx+1); i++ ) {
		xu.at(i) = i*dx;
		printf("%10.3e",xu.at(i));
	}
	printf("\n");
	for ( int I = 0; I < nx; I++ ) {
		x.at(I) = (I+0.5)*dx;
		printf("%10.3e",x.at(I));
	}
	printf("\n");
	
	for ( int j = 0; j < (ny+1); j++ ) {
		yv.at(j) = j*dy;
		printf("%10.3e",yv.at(j));
	}
	printf("\n");
	for ( int J = 0; J < ny; J++ ) {
		y.at(J) = (J+0.5)*dy;
		printf("%10.3e",y.at(J));
	}
	printf("\n");
	
	
	
}

int main() {
	
	setup();
	
	// inlet condition
	{
		int i = 0;
		for ( int J = 0; J < ny; J++ ) {
			u.at(i,J) = 1;
		}
	}
	
	//u.fill(1);
	
	// iterate
	for ( int a = 0; a < 1; a++ ) {
		iter();
	}
	
	printf("u\n");
	for ( int i = 0; i < (nx+1); i++ ) {
		for ( int J = 0; J < ny; J++ ) {
			printf("%10.3e",u.at(i,J));
		}
		printf("\n");
	}
	
	printf("v\n");
	for ( int I = 0; I < nx; I++ ) {
		for ( int j = 0; j < (ny+1); j++ ) {
			printf("%10.3e",v.at(I,j));
		}
		printf("\n");
	}
	
	printf("p\n");
	for ( int I = 0; I < nx; I++ ) {
		for ( int J = 0; J < ny; J++ ) {
			printf("%10.3e",p.at(I,J));
		}
		printf("\n");
	}
	
	u.write("u");
	v.write("v");
	
	return 0;
}







