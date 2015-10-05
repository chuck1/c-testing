#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

using namespace std;

mutex m0;
mutex m1;


void foo()
{
	cout << "foo" << endl;

	lock_guard<mutex> lg0(m0);
	cout << "foo mutex 0 locked" << endl;

	sleep(1);

	lock_guard<mutex> lg1(m1);
	cout << "foo mutex 1 locked" << endl;

}
void bar()
{
	cout << "bar" << endl;

	lock_guard<mutex> lg0(m1);
	cout << "bar mutex 1 locked" << endl;

	sleep(1);

	lock_guard<mutex> lg1(m0);
	cout << "bar mutex 0 locked" << endl;

}

int main()
{

	foo();

	thread t0(&foo);
	thread t1(&bar);

	t0.join();
	t1.join();

}





