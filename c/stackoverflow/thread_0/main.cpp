#include <iostream>
#include <thread>
#include <functional>



class Threaded_Class {
	public:
		Threaded_Class();
		void init();
};

Threaded_Class::Threaded_Class() {
	std::thread t1(std::bind(&Threaded_Class::init,this));

	t1.join();
}

void Threaded_Class::init() {
	std::cout << "Hello, world" << std::endl;
}

int main() {
	Threaded_Class a;
	return 0;
}
