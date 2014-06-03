#include <iostream>
#include <vector>
using namespace std;

struct index {
	
	index(int i) {
		vec_.push_back(i);
	}
	
	index&		operator,(int i) {
		vec_.push_back(i);
		return *this;
	}

	vector<int> vec_;
	
	void print() {
		for(int i : vec_) cout << i << endl;
	}
};

struct foo {
	void operator[](index ind) {
		ind.print();
	}
};


int main() {
	index ind(1);
	
	ind,2;

	foo f;

	f[(1,2)];

	//ind.print();
}


