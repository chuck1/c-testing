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

template<typename T>
int print(T& t) {
	cout << t << " ";
	return 0;
}

template<typename... T> void dumby(T...) {}

template<typename... A>
void expand(A... a) {
}

template<typename... A, int... S>
void expand(tuple<A...> a, seq<S...>) {
	dumby(print(get<S>(a))...);
	cout << endl;
}

template<class... Types>
void func(Types...) {
	// ...
}

template<template<typename...> class A, class... Types, class... tup_types>
void func(A<tup_types...> a, Types... args) {
	expand(a, typename gens<sizeof...(tup_types)>::type());
	
	func(args...);
}

template<typename... A>
struct bar {

};


int main () {
	func(make_tuple(0,1), make_tuple(2), 1, make_tuple("hello"), 0);
	func(make_tuple(0,1), bar<int,int>(), make_tuple(2), 1, make_tuple("hello"), 0);
}

