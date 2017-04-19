#include <boost/python.hpp>

#include "Foo.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(libfoo)
{
	class_<Foo>("Foo").def("hello", &Foo::hello);
}

