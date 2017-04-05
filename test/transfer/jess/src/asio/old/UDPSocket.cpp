#include <UDPSocket.h>



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
#include <errno.h>             // For errno

using namespace std;

#ifdef WIN32
static bool initialized = false;
#endif

// UDPSocket Code
UDPSocket::UDPSocket() throw(SocketException) : CommunicatingSocket(SOCK_DGRAM,IPPROTO_UDP) {
  setBroadcast();
}
UDPSocket::UDPSocket(unsigned short localPort)  throw(SocketException) : CommunicatingSocket(SOCK_DGRAM, IPPROTO_UDP) {
  setLocalPort(localPort);
  setBroadcast();
}
UDPSocket::UDPSocket(const string &localAddress, unsigned short localPort) throw(SocketException) : CommunicatingSocket(SOCK_DGRAM, IPPROTO_UDP) {
  setLocalAddressAndPort(localAddress, localPort);
  setBroadcast();
}
void UDPSocket::setBroadcast() {
  // If this fails, we'll hear about it when we try to send.  This will allow 
  // system that cannot broadcast to continue if they don't plan to broadcast
  int broadcastPermission = 1;
  setsockopt(m_sockDesc, SOL_SOCKET, SO_BROADCAST, 
             (raw_type *) &broadcastPermission, sizeof(broadcastPermission));
}
void UDPSocket::disconnect() throw(SocketException) {
	sockaddr_in nullAddr;
	memset(&nullAddr, 0, sizeof(nullAddr));
	nullAddr.sin_family = AF_UNSPEC;

	// Try to disconnect
	if (::connect(m_sockDesc, (sockaddr *) &nullAddr, sizeof(nullAddr)) < 0) {
#ifdef WIN32
		if (errno != WSAEAFNOSUPPORT) {
#else
		if (errno != EAFNOSUPPORT) {
#endif
			throw SocketException("Disconnect failed (connect())", true);
		}
	}
}
void UDPSocket::sendTo(const void *buffer, int bufferLen, const string &foreignAddress, unsigned short foreignPort) throw(SocketException) {
  sockaddr_in destAddr;
  fillAddr(foreignAddress, foreignPort, destAddr);

  // Write out the whole buffer as a single message.
  if (sendto(m_sockDesc, (raw_type *) buffer, bufferLen, 0,
             (sockaddr *) &destAddr, sizeof(destAddr)) != bufferLen) {
    throw SocketException("Send failed (sendto())", true);
  }
}
int UDPSocket::recvFrom(void *buffer, int bufferLen, string &sourceAddress, unsigned short &sourcePort) throw(SocketException) {
  sockaddr_in clntAddr;
  socklen_t addrLen = sizeof(clntAddr);
  int rtn;
  if ((rtn = recvfrom(m_sockDesc, (raw_type *) buffer, bufferLen, 0, 
                      (sockaddr *) &clntAddr, (socklen_t *) &addrLen)) < 0) {
    throw SocketException("Receive failed (recvfrom())", true);
  }
  sourceAddress = inet_ntoa(clntAddr.sin_addr);
  sourcePort = ntohs(clntAddr.sin_port);

  return rtn;
}
void UDPSocket::setMulticastTTL(unsigned char multicastTTL) throw(SocketException) {
  if (setsockopt(m_sockDesc, IPPROTO_IP, IP_MULTICAST_TTL, 
                 (raw_type *) &multicastTTL, sizeof(multicastTTL)) < 0) {
    throw SocketException("Multicast TTL set failed (setsockopt())", true);
  }
}
void UDPSocket::joinGroup(const string &multicastGroup) throw(SocketException) {
  struct ip_mreq multicastRequest;

  multicastRequest.imr_multiaddr.s_addr = inet_addr(multicastGroup.c_str());
  multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
  if (setsockopt(m_sockDesc, IPPROTO_IP, IP_ADD_MEMBERSHIP, 
                 (raw_type *) &multicastRequest, 
                 sizeof(multicastRequest)) < 0) {
    throw SocketException("Multicast group join failed (setsockopt())", true);
  }
}
void UDPSocket::leaveGroup(const string &multicastGroup) throw(SocketException) {
  struct ip_mreq multicastRequest;

  multicastRequest.imr_multiaddr.s_addr = inet_addr(multicastGroup.c_str());
  multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
  if (setsockopt(m_sockDesc, IPPROTO_IP, IP_DROP_MEMBERSHIP, 
                 (raw_type *) &multicastRequest, 
                 sizeof(multicastRequest)) < 0) {
    throw SocketException("Multicast group leave failed (setsockopt())", true);
  }
}























