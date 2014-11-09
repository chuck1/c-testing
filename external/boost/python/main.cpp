#include <iostream>
#include <string>

#include <boost/circular_buffer.hpp>
#include <boost/python.hpp>

#include <hello.hpp>

namespace bp = boost::python;


class PythonStdIoRedirect {
	public:
		typedef boost::circular_buffer<std::string> ContainerType;

		void Write( std::string const& str ) {
			if (m_outputs.capacity()<100)
				m_outputs.resize(100);
			m_outputs.push_back(str);
		}

		static std::string GetOutput()
		{
			std::string ret;
			std::stringstream ss;
			for(boost::circular_buffer<std::string>::const_iterator it=m_outputs.begin();
					it!=m_outputs.end();
					it++)
			{
				ss << *it;
			}
			m_outputs.clear();
			ret =  ss.str();
			return ret;
		}
	private:
		static ContainerType m_outputs; // must be static, otherwise output is missing
};

typedef boost::python::api::object (*func_type)(boost::python::str, boost::python::api::object, boost::python::api::object);

void		mybase(std::string const & str, bp::object& ns, func_type func) {
	

	bp::object o;
	try
	{
		o = func(str.c_str(), ns, bp::object());
	}
	catch(bp::error_already_set const &)
	{
		PyErr_Print();
	}

	std::cout << "str = \"" << str << "\"\n";
	std::cout << "output:\n\"" << PythonStdIoRedirect::GetOutput() << "\"" << std::endl;


	if(!o.is_none()) {
		std::cout << "not none\n";
		ns["temp_obj"] = o;
		bp::exec("print temp_obj", ns);

		std::cout << "output:\n\"" << PythonStdIoRedirect::GetOutput() << "\"" << std::endl;

	}

}
void	myexec(std::string const & str, bp::object& ns) {

	mybase(str, ns, bp::exec);

}
void	myeval(std::string const & str, bp::object& ns) {

	mybase(str, ns, bp::eval);

}
bp::object		myevalexec(std::string const & str, bp::object& ns) {
	
	std::cout << ">>> " << str << "\n";
	

	bp::object o;
	try
	{
		o = bp::eval(str.c_str(), ns);

		if(!o.is_none()) {
			//std::cout << "not none\n";
			ns["temp_obj"] = o;
			bp::exec("print temp_obj", ns);
		}

	}
	catch(bp::error_already_set const &)
	{

		PyErr_Clear();

		//PyErr_Print();
		//std::cout << "exec\n";

		try
		{
			o = bp::exec(str.c_str(), ns, bp::object());
		}
		catch(bp::error_already_set const &)
		{
			PyErr_Print();
		}

	}

	//std::cout << "output:\n\""
	std::cout << PythonStdIoRedirect::GetOutput();
	//std::cout << "\"" << std::endl;

	return o;

}



PythonStdIoRedirect::ContainerType PythonStdIoRedirect::m_outputs;

int main() {

	try
	{
		// startup
		Py_Initialize();


		bp::object main_module = bp::import("__main__");
		bp::object main_namespace = main_module.attr("__dict__");




		// expose redirect class
		main_namespace["PythonStdIoRedirect"] = bp::class_<PythonStdIoRedirect>("PythonStdIoRedirect", bp::init<>())
			.def("write", &PythonStdIoRedirect::Write);
		
		// set redirect
		PythonStdIoRedirect python_stdio_redirector;
		boost::python::import("sys").attr("stderr") = python_stdio_redirector;
		boost::python::import("sys").attr("stdout") = python_stdio_redirector; 

		// general imports
		main_namespace["os"] = boost::python::import("os");
		main_namespace["sys"] = boost::python::import("sys");
		
		// load my module
		bp::exec("sys.path.append(os.getcwd())", main_namespace);

		main_namespace["libhello"] = bp::import("libhello");
		
		
		// example
		bp::exec(
				"hello = file('hello.txt', 'w')\n"
				"hello.write('Hello world!\\n')\n"
				"hello.close()",
				main_namespace);


		// example
		myevalexec("1+1", main_namespace);
		myevalexec("a=1+1", main_namespace);
		myevalexec("a", main_namespace);
		myevalexec("print 1+1", main_namespace);

		// my module example
		
		bp::object o = bp::eval("libhello.World()", main_namespace);
		
		World& w = bp::extract<World&>(o);
		w.set("howdy");
		
		main_namespace["w"] = o;
		myevalexec("w", main_namespace);
		myevalexec("w.greet()", main_namespace);
		myevalexec("w.set('bonjour')", main_namespace);
		myevalexec("w.greet()", main_namespace);
	
		std::cout << "w = " << &w << std::endl;
		std::cout << "w.greet() = " << w.greet() << std::endl;
	}
	catch(bp::error_already_set const &)
	{
		std::cout << "unhandled execption\n";
		PyErr_Print();
	}

	std::cout << PythonStdIoRedirect::GetOutput();


}

