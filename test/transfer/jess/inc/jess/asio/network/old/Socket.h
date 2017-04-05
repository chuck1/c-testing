#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>            // For string
#include <exception>         // For exception class


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

#include <cstring>

#include <SocketException.h>

using namespace std;

// Function to fill in address structure given an address and port
static void fillAddr(const string &address, unsigned short port, sockaddr_in &addr) {
	memset(&addr, 0, sizeof(addr));  // Zero out address structure
	addr.sin_family = AF_INET;       // Internet address

	hostent *host;  // Resolve name
	if ((host = gethostbyname(address.c_str())) == NULL) {
		// strerror() will not work for gethostbyname() and hstrerror() 
		// is supposedly obsolete
		throw SocketException("Failed to resolve name (gethostbyname())");
	}
	addr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);

	addr.sin_port = htons(port);     // Assign port in network byte order
}


/// Base class representing basic communication endpoint
class Socket {
public:
	/// Close and deallocate this socket
	~Socket();
	
	/**
	*   Get the local address
	*   @return local address of socket
	*   @exception SocketException thrown if fetch fails
	*/
	string getLocalAddress() throw(SocketException);
	
	/**
	*   Get the local port
	*   @return local port of socket
	*   @exception SocketException thrown if fetch fails
	*/
	unsigned short getLocalPort() throw(SocketException);
	
	/**
	*   Set the local port to the specified port and the local address to any interface
	*   @param localPort local port
	*   @exception SocketException thrown if setting local port fails
	*/
	void setLocalPort( unsigned short localPort ) throw(SocketException);
	
	/**
	*   Set the local port to the specified port and the local address to the specified address.  If you omit the port, a random port will be selected.
	*   @param localAddress local address
	*   @param localPort local port
	*   @exception SocketException thrown if setting local port or address fails
	*/
	void setLocalAddressAndPort( const string& localAddress, unsigned short localPort = 0 ) throw(SocketException);
	
	/**
	*   If WinSock, unload the WinSock DLLs; otherwise do nothing.  We ignore this in our sample client code but include it in the library for completeness.  If you are running on Windows and you are concerned
	*   about DLL resource consumption, call this after you are done with all Socket instances.  If you execute this on Windows while some instance of Socket exists, you are toast.  For portability of client code, this is 
	*   an empty function on non-Windows platforms so you can always include it.
	*   @exception SocketException thrown WinSock clean up fails
	*/
	static void cleanUp() throw(SocketException);
	
	/**
	*   Resolve the specified service for the specified protocol to the corresponding port number in host byte order
	*   @param service service to resolve (e.g., "http")
	*   @param protocol protocol of service to resolve.  Default is "tcp".
	*/
	static unsigned short resolveService(const string &service,const string &protocol = "tcp");

private:
	/// Prevent the user from trying to use value semantics on this object
	Socket(const Socket &sock);
	/// Prevent the user from trying to use value semantics on this object
	void operator=(const Socket &sock);
public:
//protected:
	/// socket descriptor
	int m_sockDesc;
	/// Constructor overridden by derived class
	Socket(int type, int protocol) throw(SocketException);
	/// Constructor overridden by derived class
	Socket(int sockDesc);
};

#endif




/*
*   @param buffer buffer to receive the data
	*   @param bufferLen maximum number of bytes to read into buffer
	*   @return number of bytes read, 0 for EOF, and -1 for error
	*/