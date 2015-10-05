
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#ifdef __LINUX
	#include <execinfo.h>
	#include <cxxabi.h>
#elif defined(__WINDOWS)
	#include <Windows.h>
	#include <WinBase.h>
	#include <DbgHelp.h>
#endif


#include <StackTrace/Include/StackTrace.h>

#include <Except.h>

using namespace std;



Except::Except(const string &message, int code, bool inclSysMsg)throw() : userMessage(message), errorno(code) {

#ifdef __LINUX
	if (inclSysMsg) {
		userMessage.append(": ");
		userMessage.append(strerror(errno));
	}
#elif __WINDOWS
	if (inclSysMsg) {
		int* perrno = _errno();
		
		const int len = 64;
		char buffer[len+1];

		strerror_s(buffer,len,*perrno);

		userMessage.append(": ");
		userMessage.append(buffer);

	}
#endif
	printf("%s\n",userMessage.c_str());
	print_stacktrace();
}
Except::~Except() throw() {
}
const char *Except::what() const throw() {
	return userMessage.c_str();
}






    

    







