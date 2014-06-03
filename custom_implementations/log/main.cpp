
#define RELEASE

#include "log.hpp"

// in compiletime config file
// for static:  set to severity leve
// for dynamic: set to channel name (variable will be created)
CREATE_CHANNEL0(core, two)
CREATE_CHANNEL1(graphics)

int main() {
	// in runtime config file/during run
	//core = one;
	graphics = three;


	// main

	LOG(core,one) << "core one " << one;
	LOG(core,two) << "core two " << two;
	LOG(core,three) << "core three ";
	LOG(core,four) << "core four ";

	LOG(graphics,one) << "graphics one";
	LOG(graphics,two) << "graphics two";
	LOG(graphics,three) << "graphics three";
	LOG(graphics,four) << "graphics four";

	graphics = two;

	LOG(graphics,one) << "graphics one";
	LOG(graphics,two) << "graphics two";
	LOG(graphics,three) << "graphics three";
	LOG(graphics,four) << "graphics four";
}



