#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <jess/print/print.hpp>

#include <jess/asio/message.hpp>

#include <jess/asio/network/socket_communicating.hpp>

jess::asio::network::socket_communicating::socket_communicating(boost_io_service_ptr io_service,boost_socket_ptr socket):
	io_service_(io_service),
	socket_(socket),
	read_msg_(new jess::asio::message)
{
}
void	jess::asio::network::socket_communicating::write(const jess::asio::message::shared_ptr msg)
{
	io_service_->post( boost::bind(&socket_communicating::post_write, this, msg) );
}
void	jess::asio::network::socket_communicating::close()
{
	io_service_->post(boost::bind(&socket_communicating::post_close, this));
}
void	jess::asio::network::socket_communicating::post_write(const jess::asio::message::shared_ptr msg)
{
	jess::clog << "post_write begin" << endl;
		
	bool write_in_progress = !write_msgs_.empty();

	write_msgs_.push_back(msg);

	if (!write_in_progress)
	{
		do_write();
	}

	jess::clog << "exiting post_write..." << endl;
}
void	jess::asio::network::socket_communicating::post_close()
{
	socket_->close();
}
void	jess::asio::network::socket_communicating::do_read_header()
{
	jess::clog << "do_read_header..." << endl;
	
	if ( !socket_->is_open() ) jess::cerr << "SOCKET NOT OPEN" << endl;

	if ( !read_msg_->data() ) jess::cerr << "WTF!" << endl;

	jess::clog << "message::header_length " << message::header_length << endl;
	
	boost::asio::async_read(
		*socket_,
		boost::asio::buffer(read_msg_->data(), message::header_length),
		boost::bind(
			&socket_communicating::handle_do_read_header,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	jess::clog << "do_read_header end" << endl;
}
void	jess::asio::network::socket_communicating::do_read_body()
{
	jess::clog << "do_read_body begin" << endl;

	boost::asio::async_read(
		*socket_,
		boost::asio::buffer(read_msg_->body(), read_msg_->body_length()),
		boost::bind(
			&socket_communicating::handle_do_read_body,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	jess::clog << "do_read_body end" << endl;
}
void	jess::asio::network::socket_communicating::do_write()
{
	jess::clog << "do_write..." << endl;
		
	boost::asio::async_write(
		*socket_,
		boost::asio::buffer(write_msgs_.front()->data(), write_msgs_.front()->length()),
		boost::bind(
			&socket_communicating::handle_do_write,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	jess::clog << "do_write end" << endl;
}
void	jess::asio::network::socket_communicating::handle_do_read_header(boost::system::error_code ec, std::size_t /*length*/)
{
	jess::clog << "handle_do_read_header begin" << endl;

	if (!ec && read_msg_->decode_header())
	{
		do_read_body();
	}
	else
	{
		if (ec)
		{
			jess::cerr << "read failed " << ec.message() << endl;
			
			jess::cerr << "socket_ " << socket_.get() << endl;
		}	
		else
		{
			jess::cout << "header decode failed" << endl;
		}

		socket_->close();
	}

	jess::clog << "handle_do_read_header end" << endl;
}
void	jess::asio::network::socket_communicating::handle_do_read_body(boost::system::error_code ec, std::size_t /*length*/)
{
	jess::clog << "handle_do_read_body begin" << endl;

	if (!ec)
	{
		//jess::clog.write(read_msg_.body(), read_msg_.body_length());
		//jess::clog << "\n";

		if (process_body_)
		{
			jess::clog << "process_body_" << endl;
			
			process_body_(read_msg_);
		}
		
		do_read_header();
	}
	else
	{
		jess::cerr << ec.message() << endl;
	
		socket_->close();
	}
	
	jess::clog << "handle_do_read_body end" << endl;
}
void	jess::asio::network::socket_communicating::handle_do_write(boost::system::error_code ec, std::size_t /*length*/)
{
	jess::clog << "handle_do_write begin" << endl;

	if (!ec)
	{
		write_msgs_.pop_front();

		if (!write_msgs_.empty())
		{
			do_write();
		}
	}
	else
	{
		socket_->close();
	}

	jess::clog << "handle_do_write end" << endl;
}







