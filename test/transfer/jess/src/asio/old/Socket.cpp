#include <Socket.h>

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
#include <cstring>
#include <fcntl.h>

using namespace std;

#ifdef WIN32
static bool initialized = false;
#endif



// Socket Code
Socket::Socket(int type, int protocol) throw(SocketException)
{
#ifdef WIN32
	if (!initialized)
	{
		WORD wVersionRequested;
		WSADATA wsaData;

		// Request WinSock v2.0
		wVersionRequested = MAKEWORD(2, 0);              
		if (WSAStartup(wVersionRequested, &wsaData) != 0)
		{  // Load WinSock DLL
			throw SocketException("Unable to load WinSock DLL");
		}
		initialized = true;
	}
#endif
	
	// Make a new socket 
	m_sockDesc = socket(PF_INET, type, protocol);

	if ( m_sockDesc < 0 )
	{
		throw SocketException("Socket creation failed (socket())", true);
	}

	// make non-blocking
	int error = fcntl(m_sockDesc, F_SETFL, O_NONBLOCK);
	if ( error < 0 )
	{
		throw SocketException("Setting non-blocking failed (fcntl())", true);
	}

	printf("non-blocking set\n");
}
Socket::Socket(int m_sockDesc) {
	this->m_sockDesc = m_sockDesc;
}
Socket::~Socket() {
	#ifdef WIN32
	::closesocket(m_sockDesc);
	#else
	::close(m_sockDesc);
	#endif
	m_sockDesc = -1;
}
string			Socket::getLocalAddress() throw(SocketException) {
	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);

	if (getsockname(m_sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
		throw SocketException("Fetch of local address failed (getsockname())", true);
	}
	return inet_ntoa(addr.sin_addr);
}
unsigned short	Socket::getLocalPort() throw(SocketException) {
	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);

	if (getsockname(m_sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
		throw SocketException("Fetch of local port failed (getsockname())", true);
	}
	return ntohs(addr.sin_port);
}
void			Socket::setLocalPort(unsigned short localPort) throw(SocketException) {
	// Bind the socket to its port
	sockaddr_in localAddr;
	memset(&localAddr, 0, sizeof(localAddr));
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(localPort);

	if (bind(m_sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0) {
		throw SocketException("Set of local port failed (bind())", true);
	}
}
void			Socket::setLocalAddressAndPort(const string &localAddress, unsigned short localPort) throw(SocketException) {
	// Get the address of the requested host
	sockaddr_in localAddr;
	fillAddr(localAddress, localPort, localAddr);

	if (bind(m_sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0) {
		throw SocketException("Set of local address and port failed (bind())", true);
	}
}
void			Socket::cleanUp() throw(SocketException) {
	#ifdef WIN32
		if (WSACleanup() != 0) {
			throw SocketException("WSACleanup() failed");
		}
	#endif
}
unsigned short	Socket::resolveService(const string &service, const string &protocol) {
	struct servent *serv;        /* Structure containing service information */

	if ((serv = getservbyname(service.c_str(), protocol.c_str())) == NULL) {
		return atoi(service.c_str());  /* Service is port number */
	}
	else  {
		return ntohs( serv->s_port );    /* Found port (network byte order) by name */
	}
}















