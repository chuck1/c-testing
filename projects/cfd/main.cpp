#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define NX 20
#define NY 10

double u[NX+1][NY];
double v[NX][NY+1];
double p[NX][NY];

double nu = 0.01;
double dx = 0.001;

/*
double F_n, F_s, F_e, F_w, D_n, D_s, D_e, D_w, a, a_n, a_s, a_e, a_w, A, b;
double u_N, u_S, u_E, u_W;
double v_N, v_S, v_E, v_W;
double u_n, u_s, u_e, u_w;
double v_n, v_s, v_e, v_w;

double p_n, p_s, p_e, p_w;

double R_u, R_v, R_p;
double u_old, v_old, p_old;

int dump() {
	printf("a   %e\n", a);
	printf("a_n %e a_s %e a_e %e a_w %e\n", a_n, a_s, a_e, a_w);
	printf("F_n %e F_s %e F_e %e F_w %e\n", F_n, F_s, F_e, F_w);
	printf("v_n %e v_s %e u_e %e u_w %e\n", v_n, v_s, u_e, u_w);

	printf("D_n %e D_s %e D_e %e D_W %e\n", D_n, D_s, D_e, D_w);
	printf("u_N %e u_S %e u_E %e u_W %e\n", u_N, u_S, u_E, u_W);
	return 0;
}
int load_x(int i, int j) {
	u_N = u[i][j+1];
	u_S = u[i][j-1];
	u_E = u[i+1][j];
	u_W = u[i-1][j];

	p_e = p[i][j];
	p_w = p[i-1][j];

	v_n = 0.5 * (v[i-1][j+1] + v[i][j+1]);
	v_s = 0.5 * (v[i-1][j]   + v[i][j]);
	u_e = 0.5 * (u[i][j]     + u[i+1][j]);
	u_w = 0.5 * (u[i-1][j]   + u[i][j]);

	F_n = fmax(-v_n,0);
	F_s = fmax(v_s,0);
	F_e = fmax(-u_e,0);
	F_w = fmax(u_w,0);

	D_n = nu / dx;
	D_s = nu / dx;
	D_e = nu / dx;
	D_w = nu / dx;


	a_n = D_n + F_n;
	a_s = D_s + F_s;
	a_e = D_e + F_e;
	a_w = D_w + F_w;

	a = a_w + a_e + a_n + a_s + (u_e - u_w) + (v_n - v_s);


	return 0;
}
int load_y(int i, int j) {

	v_N = v[i][j+1];
	v_S = v[i][j-1];
	v_E = v[i+1][j];
	v_W = v[i-1][j];

	p_n = p[i][j];
	p_s = p[i][j-1];

	v_n = 0.5 * (v[i][j]   + v[i][j+1]);
	v_s = 0.5 * (v[i][j-1] + v[i][j]);
	u_e = 0.5 * (u[i][j]   + u[i][j-1]);
	u_w = 0.5 * (u[i+1][j] + u[i+1][j]);

	F_n = fmax(-v_n,0);
	F_s = fmax(v_s,0);
	F_e = fmax(-u_e,0);
	F_w = fmax(u_w,0);

	D_n = nu / dx;
	D_s = nu / dx;
	D_e = nu / dx;
	D_w = nu / dx;

	a_n = D_n + F_n;
	a_s = D_s + F_s;
	a_e = D_e + F_e;
	a_w = D_w + F_w;

	a = a_w + a_e + a_n + a_s + (u_e - u_w) + (v_n - v_s);

	return 0;
}
int x_mom() {
	int i, j;


	R_u = 0;


	// boundary
	for(j = 0; j < NY; ++j) {
		u[0][j] = 1;
		u[NX][j] = u[NX-1][j];
	}

	// u
	for(i = 1; i < NX; ++i) {
		for(j = 0; j < NY; ++j) {

			load_x(i,j);

			if(a==0.0) {
				printf("a==0\n");
				dump();
				abort();
			}

			A = 1;
			b = 0;


			u_old = u[i][j];
			u[i][j] = (a_n * u_N + a_s * u_S + a_e * u_E + a_w * u_W + (p_w - p_e) * A + b) / a;

			if(u[i][j] > 1000) {
				printf("u_p %e\n", u[i][j]);
				dump();
				abort();
			}
			if(isinf(u[i][j])) {
				printf("inf\n");
				abort();
			}

			//printf("%e %e\n", u_old, u[i][j]);

			R_u += fabs(u[i][j] - u_old);

			if(isnan(R_u)) {
				dump();
				abort();
			}
		}
	}


	return 0;
}

int y_mom() {
	int i, j;

	R_v = 0;

	// boundary
	for(i = 0; i < NX; ++i) {
		v[i][0] = 0;
		v[i][NY] = 0;
	}

	// v
	for(i = 0; i < NX; ++i) {
		for(j = 1; j < NY; ++j) {

			load_y(i,j);

			A = 1;
			b = 0;

			v_old = v[i][j];
			v[i][j] = (a_n * v_N + a_s * v_S + a_e * v_E + a_w * v_W + (p_w - p_e) * A + b) / a;


			if(isinf(v[i][j])) {
				printf("inf v\n");
				dump();
				abort();

			}

			R_v += fabs(v[i][j] - v_old);

			if(isnan(R_v)) abort();
		}
	}


	return 0;
}
int print_u() {
	int i, j;

	for(i = 0; i < NX+1; ++i) {
		for(j = 0; j < NY; ++j) {
			printf("%e ",u[i][j]);
		}
		printf("\n");
	}
	return 0;
}
int print_p() {
	int i, j;
	
	for(i = 0; i < NX; ++i) {
		for(j = 0; j < NY; ++j) {
			printf("%e ",p[i][j]);
		}
		printf("\n");
	}
	return 0;
}
int mom() {
	int m;
	for(m = 0; m < 1e6; ++m) {
		x_mom();
		y_mom();

		printf("%8i %e %e\n", m, R_u, R_v);

		if((R_u + R_v) < 1e-10) break;
	}



	return 0;
}
int pres() {

	int i, j, m;

	for(m = 0; m < 1e6; ++m) {
		R_p = 0;

		for(i = 0; i < NX; ++i) {
			for(j = 0; j < NY; ++j) {
				v_n = v[i][j+1];
				v_s = v[i][j];
				u_e = u[i+1][j];
				u_w = u[i][j];

				b = u_w - u_e + v_s - v_n;

				p_old = p[i][j];

				p[i][j] = (p[i-1][j] + p[i+1][j] + p[i][j-1] + p[i][j+1] + b) / 4.0;

				R_p += fabs(p[i][j] - p_old);
			}
		}

		printf("%8i %e\n", m, R_p);

		if(R_p<1e-10) break;
	}

	return 0;
}
int correct_vel() {
	int i, j;

	R_u = 0;
	R_v = 0;
	
	double up, vp;
	
	for(i = 1; i < NX; ++i) {
		for(j = 0; j < NY; ++j) {
			load_x(i,j);
			
			up = (p_w - p_e) / a;
			
			R_u += up;
			
			u[i][j] += up;
		}
	}

	for(i = 0; i < NX; ++i) {
		for(j = 1; j < NY; ++j) {
			load_y(i,j);
			
			vp = (p_w - p_e) / a;
			
			R_v += vp;
			
			v[i][j] += vp;

		}
	}

	return 0;
}
*/

void zero() {
	for(i = 0; i < NX+1; ++i) {
		for(j = 0; j < NY; ++j) {
			u[i][j] = 0;
		}
	}
	for(i = 0; i < NX; ++i) {
		for(j = 0; j < NY+1; ++j) {
			v[i][j] = 0;
		}
	}
	for(i = 0; i < NX; ++i) {
		for(j = 0; j < NY; ++j) {
			p[i][j] = 0;
		}
	}
}





int main() {
	int i, j, m;

	printf("main\n");

	zero();
	
	for(m = 0; m < 1e6; ++m) {
		mom();
		pres();
		correct_vel();

		print_p();

		print_u();

		//break;
	}
	
	
	
	return 0;
}



