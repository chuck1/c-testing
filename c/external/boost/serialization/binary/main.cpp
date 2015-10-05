
#include <cstdio>

#include <boost/archive/binary_oarchive.hpp>

#include <sstream>

void printar(std::stringstream const & s) {

	std::string str = s.str();
	
	//std::cout << str.size() << std::endl;
	
	unsigned char* c = (unsigned char*)str.c_str();
	
	//s.get((char*)c,4);
	
	for(int i = 0; i < str.size(); i++) {
		printf("%02X ", c[i]);
	}
	printf("\n");
}

int main() {
	
	std::stringstream s;
	
	boost::archive::binary_oarchive ar(s);

	printar(s);
	
	unsigned char i = 16;

	ar << i;

	printar(s);

	ar << i;

	printar(s);

	ar << i;

	printar(s);
	
	
	
}




