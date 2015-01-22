#ifndef _SOCKET_EXCEPTION_H
#define _SOCKET_EXCEPTION_H

#include <string>            // For string
#include <exception>         // For exception class

using namespace std;

/// Signals a problem with the execution of a socket call
class SocketException:
	public exception
{
public:
	/**
	*   Construct a SocketException with a explanatory message.
	*   @param message explanatory message
	*   @param inclSysMsg true if system message (from strerror(errno)) should be postfixed to the user provided message
	*/
	SocketException(const string &message, bool inclSysMsg = false) throw();

	/**
	*   Provided just to guarantee that no exceptions are thrown.
	*/
	~SocketException() throw();

	/**
	*   Get the exception message
	*   @return exception message
	*/
	const char*	what() const throw();
	/**
	*   Get the system error number
	*   @return system error number
	*/
	int			Errno() const throw();
private:
	/// exception message
	string userMessage;

	/// system error number
	int		m_errno;
};

#endif








