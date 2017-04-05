#include <iostream>
#include <memory>

using namespace std;

template<typename T> class greedy_ptr {
	public:
		greedy_ptr(T* t = NULL): ptr_(t) {}
		
		operator weak_ptr<T>() {
			return std::weak_ptr<T>(ptr_);
		}
	private:
		shared_ptr<T>	ptr_;

};

//template<typename T> shared_ptr<T> & operator=(shared_ptr<T> & s, greedy_ptr<T> & g) {}

int main() {

	weak_ptr<int> w;
	shared_ptr<int> s;

	{
		greedy_ptr<int> g(new int);


		w = g;
		//s = g; error
		
		cout << w.expired() << endl;
		
	}

	cout << w.expired() << endl;
}



