#include <SocketException.h>



#ifdef WIN32
	#include <winsock.h>         // For socket(), connect(), send(), and recv()
	typedef int socklen_t;
	typedef char raw_type;       // Type used for raw data on this platform
#else
	#include <sys/types.h>       // For data types
	#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
	#include <netdb.h>           // For gethostbyname()
	#include <arpa/inet.h>       // For inet_addr()
	#include <unistd.h>          // For close()
	#include <netinet/in.h>      // For sockaddr_in
	typedef void raw_type;       // Type used for raw data on this platform
#endif

#include <errno.h>             // For errno
#include <cstring>             // for strerror

using namespace std;

#ifdef WIN32
static bool initialized = false;
#endif

// SocketException Code
SocketException::SocketException(const string &message, bool inclSysMsg)throw() : userMessage(message)
{
	m_errno = errno;
	
	if (inclSysMsg)
	{
		userMessage.append(": ");
		userMessage.append(strerror(m_errno));
	}
}
SocketException::~SocketException() throw() {
}
const char*	SocketException::what() const throw() {
	return userMessage.c_str();
}
int			SocketException::Errno() const throw()
{
	return m_errno;
}

