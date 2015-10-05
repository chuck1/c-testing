
#include <boost/python.hpp>

#include "stat.hpp"

template<class T> PyObject* std_vector_to_py_list(const std::vector<T>& v) {

	/*
	   boost::python::object get_iter = boost::python::iterator<std::vector<T> >();
	   boost::python::object iter = get_iter(v);
	   boost::python::list* l = new boost::python::list(iter);
	   return l->ptr();
	   */
	boost::python::list* l = new boost::python::list();
	for(size_t i = 0; i < v.size(); i++)
		(*l).append(v[i]);

	return l->ptr();
}


struct py_stat_dir: stat_dir {
	py_stat_dir() {}
	py_stat_dir(stat_dir& sd):
		stat_dir(sd)
	{}
	
	PyObject*		get_dirs() {
		boost::python::list* l = new boost::python::list();

		for(size_t i = 0; i < dirs.size(); i++)
			(*l).append(py_stat_dir(dirs[i]));

		return l->ptr();
	}
	PyObject*		get_files() {
		return std_vector_to_py_list(files);
	}
};

BOOST_PYTHON_MODULE(libstatfs)
{

	boost::python::class_<stat_file>("stat_file")
		.def_readonly("name", &stat_file::name)
		.def("size", &stat_file::size);

	boost::python::class_<py_stat_dir>("stat_dir")
		.def_readonly("name",
				&py_stat_dir::name)
		.def("size",
				&py_stat_dir::size)
		.def("read", &py_stat_dir::read)
		.def("get_dirs", &py_stat_dir::get_dirs)
		.def("get_files", &py_stat_dir::get_files);

}

