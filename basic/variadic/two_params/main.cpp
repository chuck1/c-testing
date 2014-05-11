#include <tuple>
#include <iostream>

using namespace std;


template<class... A, class... B>
void foo(tuple<A...> a, tuple<B...> b) {
	
	cout << sizeof...(A) << " " << sizeof...(B) << endl;
}

template<class... A>
struct group {
	group(A&&... a): a_(a...) {};
	
	std::tuple<A&...> a_;
};

template<class... A, class... B>
void foo(group<A...> a, group<B...> b) {
	
	cout << sizeof...(A) << " " << sizeof...(B) << endl;
}



int main () {

	foo(make_tuple(0,0), make_tuple(1,2,3));

	foo(group<int,int>(0,0),group<int,int>(0,0));

}

