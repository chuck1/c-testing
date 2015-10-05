#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <jess/print/print.hpp>

#include <jess/asio/network/socket_server.hpp>



jess::asio::network::socket_server::socket_server(boost_io_service_ptr io_service, const boost::asio::ip::tcp::endpoint& endpoint):
	io_service_(io_service),
	acceptor_(*io_service, endpoint),
	socket_(new boost::asio::ip::tcp::socket(*io_service))
{
	jess::clog << "socket_server ctor begin" << endl;

	process_accept_ = boost::bind(&jess::asio::network::socket_server::process_accept,this,_1); 

	do_accept();

	jess::clog << "socket_server ctor end" << endl;
}
void jess::asio::network::socket_server::do_accept()
{
	//boost::asio::io_service& io_service = acceptor_.get_io_service();

	jess::clog << "do_accept begin" << endl;
		
	acceptor_.async_accept(
		*socket_,
		boost::bind(&socket_server::handle_do_accept, this, boost::asio::placeholders::error));
	
	jess::clog << "do_accept end" << endl;
}
void jess::asio::network::socket_server::handle_do_accept(boost::system::error_code ec)
{
	jess::clog << "handle_do_accept" << endl;
	
	if (!ec)
	{
		jess::clog << "accept successfull" << endl;
		
		jess::clog << "socket_server::socket_ " << socket_.get() << endl;

		socket_communicating::shared_ptr socket(new socket_communicating(io_service_,socket_));

		process_accept_(socket);

		jess::clog << socket_.use_count() << endl;

		socket_.reset(new boost::asio::ip::tcp::socket(*io_service_));

		jess::clog << socket_.use_count() << endl;

		jess::clog << socket->socket_.use_count() << endl;

		jess::clog << "socket_server::socket_ " << socket_.get() << endl;
	}
	else
	{
		jess::clog << "accept failed " << ec.message() << endl;
	}

	do_accept();

	jess::clog << "handle_do_accept end" << endl;
}
void jess::asio::network::socket_server::process_accept(jess::asio::network::socket_communicating::shared_ptr socket)
{
	socket_vector_.push_back(socket);
}			



