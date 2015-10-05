// Z:\cfs\code\cpp\engr_comp\Engr\TF\Flow\Internal\test.cpp

#include <chrono>

extern "C"
{
#include <pthread.h>
#include <unistd.h>
}

#include "../../mylib/mylib.h"
#include "design.h"


struct ThreadData {
	ThreadData(){}
	ThreadData(int _id,int _a,int _b,shared_ptr<matrix<Design> > _d):
		id(_id),
		a(_a),
		b(_b),
		d(_d)
	{}
	int a;
	int b;
	int id;
	shared_ptr<matrix<Design> > d;
};
class Monitor {
public:
	Monitor()
	{
		pthread_mutex_init(&m_monitorMutex,NULL);
	}
	void update(ThreadData* td,int a)
	{
		pthread_mutex_lock( &m_monitorMutex );
		
		cout << "pthread " << td->id << " is at " << ((double)(a-td->a))/((double)(td->b-td->a))*100.0 << "%\n";
		
		pthread_mutex_unlock( &m_monitorMutex );
	}
	pthread_mutex_t m_monitorMutex;
} mon;
void* f1(void* pArg) {
	assert (pArg);
	
	ThreadData* td = reinterpret_cast<ThreadData*>(pArg);
	
	assert (td->d);
	
	chrono::high_resolution_clock::time_point t1,t2;
	chrono::duration<double> time_span;
	
	//matrix<Design>* d = d;
	
	int n = td->b - td->a;
	
	
	
	t1 = chrono::high_resolution_clock::now();
	for ( int a = td->a; a < td->b; a++ )
	{
		td->d->Get(a).Calc();
		t2 = chrono::high_resolution_clock::now();
		time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
		if ( time_span.count() > 1 )
		{
			t1 = chrono::high_resolution_clock::now();
			mon.update(td,a);
		}
	}
}
void ParCalc(shared_ptr<matrix<Design> > d,int nTh) {
	int n = d->NbEl() / nTh;
	
	ThreadData* td = new ThreadData[nTh];
	pthread_t*	th = new pthread_t[nTh];
	
	for ( int a = 0; a < nTh; a++ )
	{
		if ( a == ( nTh-1 ) )
		{
			td[a] = ThreadData( a,n*a, d->NbEl(), d );
		}
		else
		{
			td[a] = ThreadData( a,n*a, n*(a+1), d );
		}
	}
	
	chrono::high_resolution_clock::time_point t1,t2;
	chrono::duration<double> time_span;
	
	
	
	t1 = chrono::high_resolution_clock::now();
	
	
	
	
	for ( int a = 0; a < nTh; a++ )
	{
		assert( th+a );
		assert( td+a );
		pthread_create( th+a, NULL, f1, reinterpret_cast<void*>(td+a));
    }
	
	for ( int a = 0; a < nTh; a++ )
	{
		assert( th+a );
		pthread_join(th[a],NULL);
	}
	
	t2 = chrono::high_resolution_clock::now();
	
	time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	cout << "Duration " << time_span.count() << " seconds for " << d->NbEl() << " points\n";

	
	delete[] td;
	delete[] th;
}
int usage() {
	printf ("-x <file> specify xml file\n");
}
int main(int argc, char **argv) {
	unitmanager::Init();
	//unitmanager::ListUnits();
	
	char *xmlfile = 0;
	
	mygetopt go;
	go.get(argc,argv,"x:");
	
	for ( int a = 0; a < go.optc; a++ )
	{
		switch (go.opt[a].c) {
		case 'x':
			xmlfile = go.opt[a].arg;
			break;
		}
	}
	if (!xmlfile) {
		usage();
		return 0;
	}
	
	
	
	shared_ptr<constants> con(new constants);
	con->parse(xmlfile);
	
	
	int n[] = {10, 10, 10};
	
	matrixD x_c, x_w, z_c, X_c, X_w, Z_c, theta;
	
	
	/*
	X_c.LogSpace(-4,-3,n[0]);
	X_w.LogSpace(-4,-3,n[1]);
	Z_c.LogSpace(-3.5,-2.5,n[2]);
	*/
	
	
	x_c.LogSpace(-4,-3,n[0]);
	x_w.LogSpace(-4,-3,n[1]);
	z_c.LogSpace(-4,-4,n[2]);
	
	grid( x_c, x_w, z_c, X_c, X_w, Z_c );
	
	
	
	
	shared_ptr<matrix<Design> > d( new matrix<Design> );
	d->init(X_c);
	
	theta.init(X_c);
	
	//, 1e-2, m
	for ( int a = 0; a < d->NbEl(); a++ )
	{
		d->Get(a).Set( X_c[a], X_w[a], Z_c[a], con );
	}
	
	ParCalc(d,6);
	
	// post-process
	for ( int a = 0; a < d->NbEl(); a++ )
	{
		theta.Get(a) = d->Get(a).m_theta;
	}
	
	int b = 0;
	double thetaMin = theta.Min(b);
	cout << "theta.Min()=theta.at(" << b << ")=" << thetaMin << "\n";
	printf ("w.at(%i) = %e\n", b, X_c.Get(b));
	printf ("ww.at(%i)= %e\n", b, X_w.Get(b));
	printf ("H.at(%i) = %e\n", b, Z_c.Get(b));
	printf ("dp.at(%i)= %e\n", b, d->Get(b).m_p.m_dp);
	printf ("M.at(%i) = %e\n", b, d->Get(b).m_p.m_M);
	
	
	plot2D(X_c,theta);
	plot2D(X_w,theta);
	plot2D(Z_c,theta);
	
	return 0;
}






