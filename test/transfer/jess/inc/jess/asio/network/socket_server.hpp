#ifndef __JESS_ASIO_NETWORK_SOCKET_SERVER_HPP__
#define __JESS_ASIO_NETWORK_SOCKET_SERVER_HPP__

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <jess/asio/network/socket_communicating.hpp>

typedef std::shared_ptr<boost::asio::io_service>      boost_io_service_ptr;
typedef std::shared_ptr<boost::asio::ip::tcp::socket> boost_socket_ptr;

namespace jess
{
	namespace asio
	{
		namespace network
		{





			/// socket server
			class socket_server
			{
			public:
				/// ctor
				socket_server(boost_io_service_ptr io_service, const boost::asio::ip::tcp::endpoint& endpoint);

			private:
				/// do accept
				void do_accept();
				/// handle do accept
				void handle_do_accept(boost::system::error_code ec);
				/// process_accept
				void process_accept(jess::asio::network::socket_communicating::shared_ptr);
				

			public:
				/// process_accept_
				boost::function<void (jess::asio::network::socket_communicating::shared_ptr)> process_accept_;	

				/// io_service
				boost_io_service_ptr					io_service_;
				/// acceptor
				boost::asio::ip::tcp::acceptor				acceptor_;
				/// socket
				boost_socket_ptr					socket_;
				/// deque
				jess::asio::network::socket_communicating::vector	socket_vector_;
			};





		}
	}
}








#endif



