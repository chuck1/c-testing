#ifndef HELLO_HPP
#define HELLO_HPP


struct World {
	void set(std::string msg) { this->msg = msg; }
	std::string greet() { return msg; }
	std::string msg;
};


#endif
