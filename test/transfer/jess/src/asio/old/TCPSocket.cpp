#include <TCPSocket.h>

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

// TCPSocket Code
TCPSocket::TCPSocket() throw(SocketException) : CommunicatingSocket(SOCK_STREAM, IPPROTO_TCP) {
}
TCPSocket::TCPSocket(const string &foreign_address, unsigned short foreign_port) throw(SocketException):
	CommunicatingSocket(SOCK_STREAM, IPPROTO_TCP)
{
	m_foreign_address = foreign_address;
	m_foreign_port    = foreign_port;
	//connect(foreignAddress, foreignPort);
}
TCPSocket::TCPSocket(int newConnSD):
	CommunicatingSocket(newConnSD)
{
}









