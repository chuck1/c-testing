#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <math.h>
//#include <thread>
#include <chrono>
//#include <functional>
//#include <atomic>
extern "C"
{
#include <pthread.h>
#include <unistd.h>
}

using namespace std;

class C;

class Monitor
{
protected:
	Monitor()
	{
		pthread_mutex_init(&m_monitorMutex,NULL);
	}

	pthread_mutex_t m_monitorMutex;
};

class Mon1: public Monitor
{
public:
	Mon1(C* _parent): Monitor(), parent(_parent) {};
	void DoSomething();
	
	C* parent;
};

class Mon2: public Monitor
{
public:
	Mon2(C* _parent): Monitor(), parent(_parent) {};
	void DoSomething();
	
	C* parent;
};

class Printer: public Monitor
{
public:
	void print(string str)
	{
		pthread_mutex_lock( &m_monitorMutex );
		
		cout << str;
		
		pthread_mutex_unlock( &m_monitorMutex );
	}
};

class C
{
public:
	C()
	{
		m_mon1 = new Mon1(this);
		m_mon2 = new Mon2(this);
	}
	static void* s_Workaround(void* pArg)
	{
		static_cast<C*>(pArg)->printer.print("s_Workaround");
	}
	
	static void* s_Mon1Workaround(void* pArg)
	{
		static_cast<C*>(pArg)->m_mon1->DoSomething();
	}
	
	static void* s_Mon2Workaround(void* pArg)
	{
		static_cast<C*>(pArg)->m_mon2->DoSomething();
	}
	
	
	Mon1* m_mon1;
	Mon2* m_mon2;
	Printer printer;
	
	int m_i;
};

void Mon1::DoSomething()
{
	pthread_mutex_lock( &m_monitorMutex );
	
	double d = 0;
	double t = 0;
	//string s = "Mon1";
	for ( int a = 0; a < 10000000; a++ )
	{
		d = sin(t);
		t += 0.1;
		/*
		char buf[50];
		sprintf(buf,"%s %d\n",s.c_str(),a);
		parent->printer.print(buf);
		*/
	}
	
	pthread_mutex_unlock( &m_monitorMutex );
}

void Mon2::DoSomething()
{
	pthread_mutex_lock( &m_monitorMutex );
	
	double d = 0;
	double t = 0;
	//string s = "Mon2";
	for ( int a = 0; a < 10000000; a++ )
	{
		d = sin(t);
		t += 0.1;
		/*
		char buf[50];
		sprintf(buf,"%s %d\n",s.c_str(),a);
		parent->printer.print(buf);
		*/
	}
	
	pthread_mutex_unlock( &m_monitorMutex );
}


void* f1(void* pArg)
{
	double d = 0;
	double t = 0;
	for (int a = 0; a < 10000000; ++a)
	{
        d = sin(t);
		t += 0.1;
    }
}

int main()
{
	int a = 0;
	int b = 1;
	
	C c;
	
	c.m_i = 0;
	
	chrono::high_resolution_clock::time_point t1;
	chrono::high_resolution_clock::time_point t2;
	
	
	
	
	
	t1 = chrono::high_resolution_clock::now();
	
	pthread_t th1,th2,th3;
    pthread_create( &th1, NULL, f1, NULL);
    pthread_create( &th2, NULL, f1, NULL);
	pthread_create( &th3, NULL, f1, NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);
	
	t2 = chrono::high_resolution_clock::now();

	chrono::duration<double> time_span1 = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	cout << "Duration " << time_span1.count() << " seconds.";
	cout << endl;
	
	
	
	t1 = chrono::high_resolution_clock::now();
	
	f1(NULL);
	f1(NULL);
	f1(NULL);

	t2 = chrono::high_resolution_clock::now();

	chrono::duration<double> time_span2 = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	cout << "Duration " << time_span2.count() << " seconds.";
	cout << endl;
	
	double rat = time_span2/time_span1;
	
	cout << "Ratio " << rat << endl;
	
	
	cout << "Finished\n";
}

