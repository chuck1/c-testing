#include <Network.h>  // For Socket and SocketException

#include <iostream>           // For cerr and cout
#include <cstdlib>            // For atoi()
#include <pthread.h>          // For POSIX threads
#include <cstring>

using namespace std;

const int RCVBUFSIZE = 32;    // Size of receive buffer
const int ECHOMAX = 255;     // Longest string to echo

int TCPEchoClient(int argc, char *argv[]);
int TCPEchoServer(int argc, char *argv[]);
int TCPEchoServerThreaded(int argc, char *argv[]);
int UDPEchoClient(int argc, char *argv[]);
int UDPEchoServer(int argc, char *argv[]);
void HandleTCPClient(TCPSocket *sock); // TCP client handling function
void HandleTCPClientThreaded(TCPSocket *sock); // TCP client handling function
void *ThreadMain(void *arg);               // Main program of a thread

int main(int argc, char *argv[]) {
	if (argc == 1) {                     // Test for correct number of arguments
		cerr << "Usage: " << argv[0] << " <Mode>" << endl;
		cerr << "Modes:" << endl;
		cerr << "    1: TCPEchoClient" << endl;
		cerr << "    2: TCPEchoServer" << endl;
		cerr << "    3: TCPEchoServerThreaded" << endl;
		cerr << "    4: UDPEchoClient" << endl;
		cerr << "    5: UDPEchoClient" << endl;
		exit(1);
	}

	int mode = atoi(argv[1]);

	switch ( mode ) {
	case 1:
		return TCPEchoClient(argc,argv);
	case 2:
		return TCPEchoServer(argc,argv);
	case 3:
		return TCPEchoServerThreaded(argc,argv);
	case 4:
		return UDPEchoClient(argc,argv);
	case 5:
		return UDPEchoServer(argc,argv);
	default:
		cerr << "invalid mode" << endl;
		exit(1);
	}
}





int TCPEchoClient(int argc, char *argv[]) {
	if ((argc < 4) || (argc > 5)) {     // Test for correct number of arguments
		cerr << "Usage: " << argv[0] << " 1 <Server> <Echo String> [<Server Port>]" << endl;
		exit(1);
	}

	string servAddress = argv[2]; // First arg: server address
	char *echoString = argv[3];   // Second arg: string to echo
	int echoStringLen = strlen(echoString);   // Determine input length
	unsigned short echoServPort = (argc == 5) ? atoi(argv[4]) : 7;


	Client client;
	
	client.m_tcp_socket = new TCPSocket(servAddress, echoServPort);
	

	
	try
	{
		// Establish connection with the echo server
		client.m_tcp_socket->connect();

		printf("connection successfull\n");

		// Send the string to the echo server
		client.m_tcp_socket->send(echoString, echoStringLen);

		printf("message sent\n");
	}
	catch (SocketException &e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	for (;;) client.Recv();

	return 0;
}
int TCPEchoServer(int argc, char *argv[]) {
	if (argc != 3) {                     // Test for correct number of arguments
		cerr << "Usage: " << argv[0] << " 2 <Server Port>" << endl;
		exit(1);
	}

	unsigned short echoServPort = atoi(argv[2]);  // First arg: local port

	TCPServerSocket* servSock = NULL;

	try
	{
		servSock = new TCPServerSocket(echoServPort);     // Server Socket object
	}
	catch (SocketException &e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	// Run forever
	for (;;)
	{   
		try
		{
			HandleTCPClient( servSock->accept() );
		}
		catch (SocketException &e)
		{
			
			if ( e.Errno() != EWOULDBLOCK )
			{
				cerr << e.what() << endl;
				exit(1);
			}
		}
	}
	// NOT REACHED
	return 0;
}
// TCP client handling function
void HandleTCPClient(TCPSocket *sock) {
	//sock->send( "ping", 4 );
	
	cout << "Handling client ";
	try
	{
		cout << sock->getForeignAddress() << ":";
	}
	catch (SocketException e)
	{
		cerr << "Unable to get foreign address" << endl;
	}

	try
	{
		cout << sock->getForeignPort();
	}
	catch (SocketException e)
	{
		cerr << "Unable to get foreign port" << endl;
	}

	cout << endl;

	Client client;

	// Send received string and receive again until the end of transmission
	char echoBuffer[RCVBUFSIZE];
	int recvMsgSize;

	// Zero means end of transmission
	while ( ( recvMsgSize = sock->recv( echoBuffer, RCVBUFSIZE ) ) > 0)
	{ 
		// Echo message back to client
		client.Send(echoBuffer, recvMsgSize);
	}

	delete sock;
}
int TCPEchoServerThreaded(int argc, char *argv[]) {
  if (argc != 3) {                 // Test for correct number of arguments  
    cerr << "Usage: " << argv[0] << " 3 <Server Port> " << endl;
    exit(1);
  }

  unsigned short echoServPort = atoi(argv[2]);    // First arg:  local port  

  try {
    TCPServerSocket servSock(echoServPort);   // Socket descriptor for server  
  
    for (;;) {      // Run forever  
      // Create separate memory for client argument  
      TCPSocket *clntSock = servSock.accept();
  
      // Create client thread  
      pthread_t threadID;              // Thread ID from pthread_create()  
      if (pthread_create(&threadID, NULL, ThreadMain, 
              (void *) clntSock) != 0) {
        cerr << "Unable to create thread" << endl;
        exit(1);
      }
    }
  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
  // NOT REACHED

  return 0;
}
// TCP client handling function
void HandleTCPClientThreaded(TCPSocket *sock) {
  cout << "Handling client ";
  try {
    cout << sock->getForeignAddress() << ":";
  } catch (SocketException &e) {
    cerr << "Unable to get foreign address" << endl;
  }
  try {
    cout << sock->getForeignPort();
  } catch (SocketException &e) {
    cerr << "Unable to get foreign port" << endl;
  }
  cout << " with thread " << pthread_self() << endl;

  // Send received string and receive again until the end of transmission
  char echoBuffer[RCVBUFSIZE];
  int recvMsgSize;
  while ((recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE)) > 0) { // Zero means
                                                         // end of transmission
    // Echo message back to client
    sock->send(echoBuffer, recvMsgSize);
  }
  // Destructor closes socket
}
void *ThreadMain(void *clntSock) {
	// Guarantees that thread resources are deallocated upon return  
	pthread_detach(pthread_self()); 

	// Extract socket file descriptor from argument  
	HandleTCPClientThreaded((TCPSocket *) clntSock);

	delete (TCPSocket *) clntSock;
	return NULL;
}
int UDPEchoClient(int argc, char *argv[]) {
	if ((argc < 4) || (argc > 5)) {   // Test for correct number of arguments
		cerr << "Usage: " << argv[0] << " 4 <Server> <Echo String> [<Server Port>]\n";
		exit(1);
	}

	string servAddress = argv[2];             // First arg: server address
	char* echoString = argv[3];               // Second arg: string to echo
	int echoStringLen = strlen(echoString);   // Length of string to echo
	if (echoStringLen > ECHOMAX) {    // Check input length
		cerr << "Echo string too long" << endl;
		exit(1);
	}

	unsigned short echoServPort = Socket::resolveService( (argc == 5) ? argv[4] : "echo", "udp" );

	try {
		UDPSocket sock;

		// Send the string to the server
		sock.sendTo(echoString, echoStringLen, servAddress, echoServPort);
  
		// Receive a response
		char echoBuffer[ECHOMAX + 1];       // Buffer for echoed string + \0
		int respStringLen;                  // Length of received response
		if ( (respStringLen = sock.recv(echoBuffer, ECHOMAX) ) != echoStringLen) {
			cerr << "Unable to receive" << endl;
			exit(1);
		}

		echoBuffer[respStringLen] = '\0';             // Terminate the string!
		cout << "Received: " << echoBuffer << endl;   // Print the echoed arg

		// Destructor closes the socket

	} catch (SocketException &e) {
		cerr << e.what() << endl;
		exit(1);
	}
  
	return 0;
}
int UDPEchoServer(int argc, char *argv[]) {

	if (argc != 3) {                  // Test for correct number of parameters
		cerr << "Usage: " << argv[0] << " 5 <Server Port>" << endl;
		exit(1);
	}

	unsigned short echoServPort = atoi(argv[2]);     // First arg:  local port

	try {
		UDPSocket sock(echoServPort);                
  
		char echoBuffer[ECHOMAX];         // Buffer for echo string
		int recvMsgSize;                  // Size of received message
		string sourceAddress;             // Address of datagram source
		unsigned short sourcePort;        // Port of datagram source
		for (;;) {  // Run forever
			// Block until receive message from a client
			recvMsgSize = sock.recvFrom(echoBuffer, ECHOMAX, sourceAddress, sourcePort);
  
			cout << "Received packet from " << sourceAddress << ":" << sourcePort << endl;
  
			sock.sendTo(echoBuffer, recvMsgSize, sourceAddress, sourcePort);
		}
	} catch (SocketException &e) {
		cerr << e.what() << endl;
		exit(1);
	}
	// NOT REACHED

	return 0;
}








