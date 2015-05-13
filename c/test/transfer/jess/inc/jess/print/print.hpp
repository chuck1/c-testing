#ifndef __JESS_PRINT_PRINT_HPP__
#define __JESS_PRINT_PRINT_HPP__

#include <iostream>
#include <string>
#include <boost/system/error_code.hpp>

namespace jess
{

	class ostream
	{
	public:
		ostream();
		ostream(std::ostream*);		
		
		void funcsig();

		std::ostream* os_;
	};
	
	ostream cout(&std::cout);
	ostream cerr(&std::cerr);
	ostream clog(&std::clog);
	
}

jess::ostream& operator<<(jess::ostream& f, const char*);
jess::ostream& operator<<(jess::ostream& f, const std::string&);
jess::ostream& operator<<(jess::ostream& f, const int&);
jess::ostream& operator<<(jess::ostream& f, const void*);
jess::ostream& operator<<(jess::ostream& f, const boost::system::error_code&);
jess::ostream& operator<<(jess::ostream& f, jess::ostream&(*)(jess::ostream&));
jess::ostream& endl(jess::ostream&);



#endif








