template<typename T, typename U> U foo(T) {
	return U();
}

template<> int foo<int,int>(int);


