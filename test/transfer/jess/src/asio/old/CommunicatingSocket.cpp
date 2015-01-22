#include <CommunicatingSocket.h>
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

using namespace std;

#ifdef WIN32
static bool initialized = false;
#endif

// CommunicatingSocket Code
				CommunicatingSocket::CommunicatingSocket(int type, int protocol) throw(SocketException):
	Socket(type, protocol), m_block(true)
{

}
				CommunicatingSocket::CommunicatingSocket(int newConnSD):
	Socket(newConnSD), m_block(true)
{
}
void			CommunicatingSocket::connect(const string &foreignAddress,unsigned short foreignPort) throw(SocketException) {
	throw SocketException("Remove this function!", false);
}
void			CommunicatingSocket::connect() throw(SocketException) {
	// Get the address of the requested host
	sockaddr_in destAddr;
	fillAddr(m_foreign_address, m_foreign_port, destAddr);

	// Try to connect to the given port
	try
	{
		int error = ::connect(m_sockDesc, (sockaddr *) &destAddr, sizeof(destAddr));
		if ( error < 0 )
		{
			throw SocketException("Connect failed (connect())", true);
		}
	}
	catch(SocketException &e)
	{
		if ( ( e.Errno() != EINPROGRESS ) || ( m_block == false ) )
		{
			throw;
		}
	}

	fd_set wfds;
	struct timeval tv;
	int retval;

	FD_ZERO(&wfds);
	FD_SET(m_sockDesc, &wfds);

	// Wait
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	retval = ::select(1, NULL, &wfds, NULL, &tv);
	if ( retval < 0 )
	{
		throw SocketException("select failed (select())");
	}
}
void			CommunicatingSocket::send(const void *buffer, int bufferLen) throw(SocketException) {
	int error = ::send(m_sockDesc, (raw_type *) buffer, bufferLen, 0);
	
	if ( error < 0 )
	{
		throw SocketException("Send failed (send())", true);
	}
}
int				CommunicatingSocket::recv( void *buffer, int bufferLen ) throw(SocketException) {
	int rtn = ::recv( m_sockDesc, (raw_type*) buffer, bufferLen, 0 );
	
	if ( rtn < 0 ) {
		throw SocketException("Received failed (recv())", true);
	}

	return rtn;
}
string			CommunicatingSocket::getForeignAddress() throw(SocketException) {
	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);

	if ( getpeername(m_sockDesc, (sockaddr *) &addr,(socklen_t *) &addr_len) < 0 )
	{
		throw SocketException("Fetch of foreign address failed (getpeername())", true);
	}
	return inet_ntoa(addr.sin_addr);
}
unsigned short	CommunicatingSocket::getForeignPort() throw(SocketException) {
	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);

	if (getpeername(m_sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
		throw SocketException("Fetch of foreign port failed (getpeername())", true);
	}
	return ntohs(addr.sin_port);
}








