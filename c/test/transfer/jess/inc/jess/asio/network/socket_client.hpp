#ifndef __JESS_ASIO_NETWORK_SOCKET_CLIENT_HPP__
#define __JESS_ASIO_NETWORK_SOCKET_CLIENT_HPP__

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <jess/asio/network/socket_communicating.hpp>

typedef std::shared_ptr<boost::asio::io_service>	boost_io_service_ptr;

namespace jess
{
	namespace asio
	{
		namespace network
		{



			/// socket_client
			class socket_client: public jess::asio::network::socket_communicating
			{
			public:
				/// shared_ptr
				typedef std::shared_ptr<socket_client>	shared_ptr;

				/// ctor
				socket_client(boost_io_service_ptr io_service, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

				/// write
				void	write(const jess::asio::message::shared_ptr msg);
				/// close
				void	close();

			private:
				/// do_connect
				void	do_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
				/// handle_do_connect
				void	handle_do_connect(boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
	

			};






		}
	}
}


#endif // __JESS_ASIO_NETWORK_SOCKET_CLIENT_HPP__






