
#include <boost/python.hpp>

#include "stat.hpp"


BOOST_PYTHON_MODULE(libstatfs)
{

	boost::python::class_<stat_file>("stat_file")
		.def_readonly("name", &stat_file::name)
		.def("size", &stat_file::size);

	boost::python::class_<stat_dir>("stat_dir")
		.def_readonly("name", &stat_dir::name)
		.def("size", &stat_dir::size)
		.def("read", &stat_dir::read)
		.def("get_dirs", &stat_dir::get_dirs)
		.def("get_files", &stat_dir::get_files);

}

