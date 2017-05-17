#include <boost/python.hpp>

#include "Bar.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(libbar)
{
	class_<Bar,bases<Foo>>("Bar");
}

