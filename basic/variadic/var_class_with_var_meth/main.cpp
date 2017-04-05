#include <tuple>
#include <iostream>

using namespace std;


template<int ...>
struct seq { };

template<int N, int ...S>
struct gens : gens<N-1, N-1, S...> { };

template<int ...S>
struct gens<0, S...> {
	  typedef seq<S...> type;
};

template<typename T> int print(T const & t) {
	cout << t << " ";
	return 0;
}

template<class... T>
void dumby(T... t) {}


template<class... A>
void sub(A&... a) {
	//cout << sizeof...(B) << endl;
	dumby(print(a)...);
	cout << endl;
}

template<class... A, class... B>
void func(tuple<A...>&& a, tuple<B...>&& b) {
	//cout << sizeof...(A) << " " << sizeof...(B) << endl;

	callFunc(a, b, typename gens<sizeof...(A)>::type(), typename gens<sizeof...(B)>::type());
}




template<class... A, class... B, int... SA, int... SB>
void callFunc(
		tuple<A...>&& a,
		tuple<B...>&& b, seq<SA...>, seq<SB...>) {

	sub<A...>(get<SA>(a)...);

	sub<B...>(get<SB>(b)...);

	//cout << get<0>(a.c_) << endl;
	//cout << get<0>(b.c_) << endl;

	//int i = get<0>(a.c_);

	//cout << i << endl;


}

template< template<typename...> class... A, typename... B >
void bar(A<B...>... a) {
	
}







int main() {

	func(make_tuple(0), make_tuple(1,2));

	bar(make_tuple("1"), make_tuple("2"));

}

