#include <iostream>

#include <jess/print/print.hpp>

jess::ostream::ostream(): os_(0)
{
}
jess::ostream::ostream(std::ostream* os): os_(os)
{
}
jess::ostream::funcsig()
{
	#ifdef __LINUX
		os_ << __PRETTY_FUNCTION__ << 
	#elif defined(__WINDOWS)
		os_ << __FUNCSIG__ << std::endl;
	#endif
}
jess::ostream& operator<<(jess::ostream& os, const char* c)
{
	if (os.os_) (*os.os_) << c;
	return os;
}
jess::ostream& operator<<(jess::ostream& os, const std::string& s)
{
	if (os.os_) (*os.os_) << s;
	return os;
}
jess::ostream& operator<<(jess::ostream& os, const int &i)
{
	if (os.os_) (*os.os_) << i;
	return os;
}
jess::ostream& operator<<(jess::ostream& os, const void* v)
{
	if (os.os_) (*os.os_) << v;
	return os;
}
jess::ostream& operator<<(jess::ostream& os, const boost::system::error_code& ec)
{
	if (os.os_) (*os.os_) << ec;
	return os;
}
jess::ostream& operator<<(jess::ostream& os, jess::ostream&(*func)(jess::ostream&))
{
	func(os);
	return os;
}
jess::ostream& endl(jess::ostream& os)
{
	if (os.os_) (*os.os_) << std::endl;
	return os;
}



