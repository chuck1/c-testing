#ifndef __JESS_ASIO_NETWORK_SOCKET_COMMUNICATING_HPP__
#define __JESS_ASIO_NETWORK_SOCKET_COMMUNICATING_HPP__

#include <cstdlib>
#include <deque>
#include <vector>
#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <jess/asio/message.hpp>





typedef std::shared_ptr<boost::asio::io_service>		boost_io_service_ptr;
typedef std::shared_ptr<boost::asio::ip::tcp::socket>	boost_socket_ptr;

namespace jess
{
	namespace asio
	{
		namespace network
		{




			/// socket communicating
			class socket_communicating
			{
			public:
				/// pointer
				typedef std::shared_ptr<socket_communicating>	shared_ptr;
				/// deque
				typedef std::vector<shared_ptr>			vector;

				/// ctor
				socket_communicating(boost_io_service_ptr io_service, boost_socket_ptr);
				
				/// write
				void	write(const jess::asio::message::shared_ptr msg);
				/// close
				void	close();

			//protected:
				/// write
				void	post_write(const jess::asio::message::shared_ptr msg);
				/// close
				void	post_close();

				/// read header
				void	do_read_header();
				/// read body
				void	do_read_body();
				/// write
				void	do_write();
	
				/// handle read header
				void	handle_do_read_header(boost::system::error_code ec, std::size_t /*length*/);
				/// handle read body
				void	handle_do_read_body(boost::system::error_code ec, std::size_t /*length*/);
				/// handle write
				void	handle_do_write(boost::system::error_code ec, std::size_t /*length*/);


			//protected:
				/// io_service
				boost_io_service_ptr			io_service_;
				/// socket
				boost_socket_ptr			socket_;
				/// message
				jess::asio::message::shared_ptr		read_msg_;
				/// message deque
				jess::asio::message::deque		write_msgs_;
			public:	
				/// process body
				jess::asio::message::boost_function	process_body_;
			};





		}
	}
}




#endif // __JESS_ASIO_NETWORK_SOCKET_COMMUNICATING_HPP__





