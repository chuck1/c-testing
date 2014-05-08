#include <iostream>

#include "../../../gru/src/Nebula/Enum.hpp"

DEFINE_TYPE(Type,int,
		((ONE)(1))
		((TWO)(2))
		)

DEFINE_TYPE_STATICS(Type)

int main() {
	
	Type t1(Type::ONE);
	Type t2((Type::E)2);
	
	std::cout << t1.val_ << std::endl;
	std::cout << t2.val_ << std::endl;
	
	std::cout << Type::toString(t1.val_) << std::endl;
	std::cout << Type::toString(t2.val_) << std::endl;


	return 0;
}


