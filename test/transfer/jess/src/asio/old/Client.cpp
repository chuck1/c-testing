

#include <iostream>

#include <Client.h>

		Client::Client():
	m_bufferA(NULL),
	m_bufferA_len(0),
	m_bufferA_pos(0),
	m_bufferB(NULL),
	m_bufferB_pos(0),
	m_packet_bytes_rem(sizeof(int)),
	m_is_receiving_header(1)
{
}
		Client::~Client()
	{}
void	Client::Recv()
{
	if ( m_bufferA == NULL )
	{
		m_bufferA = new char[BUFFER_SIZE+1];
	}
	if ( m_bufferB == NULL )
	{
		m_bufferB = new char[BUFFER_SIZE+1];
	}
	
	int consume = 0;

	for (;;)
	{
		try
		{
			// If all data from bufferA has been used...
			if ( m_bufferA_pos == m_bufferA_len )
            {
                // Receive more data
				m_bufferA_len = m_tcp_socket->recv(m_bufferA, BUFFER_SIZE);
				

				// Reset bufferA position
				m_bufferA_pos = 0;

				// If no data, break
				if ( m_bufferA_len == 0 ) break;

				cout << m_bufferA_len << " received" << endl;
            }
            

			// If the remainder of the packet is longer than the remainder of bufferA
			if ( m_packet_bytes_rem > ( m_bufferA_len - m_bufferA_pos ) )
			{
				// consume the remainder of bufferA
				consume = m_bufferA_len - m_bufferA_pos;
			}
			else
			{
				// consume only what is needed to complete the packet
				consume = m_packet_bytes_rem;
			}


			// copy data from A to B
            ::memcpy( m_bufferB + m_bufferB_pos, m_bufferA + m_bufferA_pos, consume );
			
			// update positions and length
			m_packet_bytes_rem -= consume;
			m_bufferA_pos      += consume;
			m_bufferB_pos      += consume;
            
			// if packet is complete
            if ( m_packet_bytes_rem == 0 )
            {
				// If was receiving header
				if ( m_is_receiving_header == true )
				{
					// determine packet length
					m_packet_bytes_rem = *((int*)m_bufferB);

					cout << "incoming packet is " << m_packet_bytes_rem << " bytes" << endl;
				}
				else
				{
					// Process packet
					Process();

					// Reset packet length to receiver header
					m_packet_bytes_rem = sizeof(int);
				}

				// Reset bufferB position
				m_bufferB_pos = 0;

				m_is_receiving_header = !m_is_receiving_header;
            }
		}
		catch(SocketException &e)
		{
			if ( ( e.Errno() == EWOULDBLOCK ) && ( m_tcp_socket->m_block ) )
			{
				break;
			}

			cerr << e.what() << endl;
			exit(1);
		}
	}
}
void	Client::Process()
{
	m_bufferB[m_bufferB_pos+1] = '\0';

	cout << "Packet: " << m_bufferB << endl;
}
void	Client::Send(char * buffer, int len)
{
	m_tcp_socket->send((char*)&len,sizeof(int));
	m_tcp_socket->send(buffer,len);
}


