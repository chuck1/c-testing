#ifndef __COMMUNICATING_SOCKET_H__
#define __COMMUNICATING_SOCKET_H__

#include <string>            // For string
#include <exception>         // For exception class

#include <Socket.h>

using namespace std;

/// Socket which is able to connect, send, and receive
class CommunicatingSocket : public Socket {
public:
	/**
	*   Establish a socket connection with the given foreign address and port
	*   @param foreignAddress foreign address (IP address or name)
	*   @param foreignPort foreign port
	*   @exception SocketException thrown if unable to establish connection
	*/
	void connect(const string &foreignAddress, unsigned short foreignPort) throw(SocketException);

	/**
	*   Establish a socket connection with the stored foreign address and port
	*   @exception SocketException thrown if unable to establish connection
	*/
	void connect() throw(SocketException);


	/**
	*   Write the given buffer to this socket.  Call connect() before
	*   calling send()
	*   @param buffer buffer to be written
	*   @param bufferLen number of bytes from buffer to be written
	*   @exception SocketException thrown if unable to send data
	*/
	void send(const void *buffer, int bufferLen) throw(SocketException);

	/**
	*   Read into the given buffer up to bufferLen bytes data from this
	*   socket.  Call connect() before calling recv()
	*   @param buffer buffer to receive the data
	*   @param bufferLen maximum number of bytes to read into buffer
	*   @return number of bytes read, 0 for EOF, and -1 for error
	*   @exception SocketException thrown if unable to receive data
	*/
	int recv(void *buffer, int bufferLen) throw(SocketException);

	/**
	*   Get the foreign address.  Call connect() before calling recv()
	*   @return foreign address
	*   @exception SocketException thrown if unable to fetch foreign address
	*/
	string getForeignAddress() throw(SocketException);

	/**
	*   Get the foreign port.  Call connect() before calling recv()
	*   @return foreign port
	*   @exception SocketException thrown if unable to fetch foreign port
	*/
	unsigned short getForeignPort() throw(SocketException);

protected:
	/// Constructor to be overriden
	CommunicatingSocket(int type, int protocol) throw(SocketException);
	/// Constructor to be overriden
	CommunicatingSocket(int newConnSD);

public:
	string          m_foreign_address;
	unsigned short  m_foreign_port;
	bool			m_block;
};

#endif





