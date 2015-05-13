#include <boost/python.hpp>

#include <hello.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(libhello) {
	class_<World>("World")
		.def("greet", &World::greet)
		.def("set", &World::set)
		;
}


