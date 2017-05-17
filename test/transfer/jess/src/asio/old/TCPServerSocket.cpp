#include <TCPServerSocket.h>

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

using namespace std;

#ifdef WIN32
static bool initialized = false;
#endif

// TCPServerSocket Code
TCPServerSocket::TCPServerSocket(unsigned short localPort, int queueLen) throw(SocketException):
	Socket(SOCK_STREAM, IPPROTO_TCP)
{
	setLocalPort(localPort);
	setListen(queueLen);
}
TCPServerSocket::TCPServerSocket(const string &localAddress, unsigned short localPort, int queueLen) throw(SocketException):
	Socket(SOCK_STREAM, IPPROTO_TCP)
{
	setLocalAddressAndPort(localAddress, localPort);
	setListen(queueLen);
}
TCPSocket *TCPServerSocket::accept() throw(SocketException)
{
	int newConnSD = ::accept(m_sockDesc, NULL, 0);

	if ( newConnSD < 0 )
	{
		throw SocketException("Accept failed (accept())", true);
	}

	return new TCPSocket(newConnSD);
}
void TCPServerSocket::setListen(int queueLen) throw(SocketException)
{
	if ( listen(m_sockDesc, queueLen) < 0 )
	{
		throw SocketException("Set listening socket failed (listen())", true);
	}
}



















