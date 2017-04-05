//#include <boost/preprocessor/control/if.hpp>

#include <utility>

//#define RELEASE

#ifdef RELEASE
#include <iostream>
#else
// for assembly analysis
int a = 0;
#endif


struct logtemp {
	~logtemp() {
#ifdef RELEASE
		std::cout << std::endl;
#else
		a++;
#endif
	}
};


template<typename T> logtemp&&		operator<<(logtemp&& lg, T const & t) {
#ifdef RELEASE
	std::cout << t;
#endif
	return std::move(lg);
}


// define severity level
enum sl {
	one,
	two,
	three,
	four
};

// channel creation macros
#define CREATE_CHANNEL0(ch_,val_) static const sl ch_ = val_;
#define CREATE_CHANNEL1(ch_) sl ch_ = two;


// define log macro
# define LOG(ch_,sl_) if(ch_ <= sl_) logtemp()




