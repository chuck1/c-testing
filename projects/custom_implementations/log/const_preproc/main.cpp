

#include <cstddef>
#include <iostream>
#include <sstream>
#include <iomanip>


#define LOG(lg, channel, sev) if(sev >= channel) log(lg)

#define LOG_FUNC(lg, channel, sev) LOG(lg, channel, sev) << __PRETTY_FUNCTION__

enum severity_level {
	debug,
	info,
	warning,
	error,
	critical
};

struct log
{
	log(std::ostream& ss): ss_(ss) {}
	log(log&& b): ss_(b.ss_) {}
	~log() { ss_ << std::endl; }
	template<typename T> log&              operator<<(T const & t) {
		ss_ << t;
		//return move(*this);
		return *this;
	}
	std::ostream&                           ss_;
};



namespace ns1 {

	severity_level sl;

	namespace ns2 {
		


		void	fun(int)
		{
			LOG_FUNC(std::cout, ns1::sl, debug);
		}
	}
}


int main()
{

	ns1::sl = debug;

	ns1::ns2::fun(1);
	ns1::ns2::fun(2);
	ns1::ns2::fun(3);



}

