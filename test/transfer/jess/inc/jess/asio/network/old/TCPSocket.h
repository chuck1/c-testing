#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include <string>            // For string
#include <exception>         // For exception class

#include <CommunicatingSocket.h>

using namespace std;

/// TCP socket for communication with other TCP sockets
class TCPSocket : public CommunicatingSocket {
public:
	/**
	*   Construct a TCP socket with no connection
	*   @exception SocketException thrown if unable to create TCP socket
	*/
	TCPSocket() throw(SocketException);

	/**
	*   Construct a TCP socket with a connection to the given foreign address
	*   and port
	*   @param foreignAddress foreign address (IP address or name)
	*   @param foreignPort foreign port
	*   @exception SocketException thrown if unable to create TCP socket
	*/
	TCPSocket(const string &foreignAddress, unsigned short foreignPort) throw(SocketException);
	
private:
// Access for TCPServerSocket::accept() connection creation
	friend class TCPServerSocket;
	TCPSocket(int newConnSD);


};


#endif





