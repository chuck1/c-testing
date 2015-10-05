#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>



#include <jess/asio/network/socket_client.hpp>

#include <jess/print/print.hpp>



jess::asio::network::socket_client::socket_client(boost_io_service_ptr io_service, boost::asio::ip::tcp::resolver::iterator endpoint_iterator):
	socket_communicating(
		io_service,
		boost_socket_ptr(new boost::asio::ip::tcp::socket(*io_service)))
{
	do_connect(endpoint_iterator);
}
void	jess::asio::network::socket_client::write(const jess::asio::message::shared_ptr msg)
{
	jess::cout << "write begin " << io_service_.get() << endl;
		
	io_service_->post(boost::bind(&socket_client::post_write, this, msg));

	jess::cout << "write end   " << io_service_.get() << endl;
}
void	jess::asio::network::socket_client::close()
{
	io_service_->post(boost::bind(&socket_client::post_close, this));
}
void	jess::asio::network::socket_client::do_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	jess::clog << "do_connect begin" << endl;
	
	boost::asio::async_connect(
		*socket_,
		endpoint_iterator,
		boost::bind(
			&socket_client::handle_do_connect,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::iterator));
	
	jess::clog << "do_connect end" << endl;
}
void	jess::asio::network::socket_client::handle_do_connect(boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	jess::clog << "handle_do_connect begin" << endl;

	if (!ec)
	{
		jess::cout << "connection successful " << ec << " " << ec.message() << endl;
		
		jess::cout << "socket_ " << socket_.get() << endl;

		do_read_header();
	}
	else
	{
		jess::cout << "connection failed " << ec << " " << ec.message() << endl;
	}

	jess::clog << "handle_do_connect end" << endl;
}
	






