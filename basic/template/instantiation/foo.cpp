#include "foo.hpp"

template<> int foo<int,int>(int) {
	return 1;
}
