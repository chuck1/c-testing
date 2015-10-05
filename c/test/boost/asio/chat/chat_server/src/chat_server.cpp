#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <print/print.hpp>

#include <asio/network/socket_communicating.hpp>
#include <asio/network/socket_server.hpp>

//bool verb = false;

//----------------------------------------------------------------------


class chat_participant;

typedef std::shared_ptr<chat_participant> chat_participant_ptr;
typedef std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

//----------------------------------------------------------------------
 
class chat_server: public jess::asio::network::socket_server
{
public:
	chat_server(boost_io_service_ptr io_service, boost::asio::ip::tcp::endpoint endpoint):
		jess::asio::network::socket_server(io_service, endpoint)
	{
		process_accept_ = boost::bind(&chat_server::process_accept,this,_1);
	}
	
	void join(jess::asio::network::socket_communicating::shared_ptr socket)
	{
		note("join");
		
		socket_vector_.push_back(socket);

		for (auto it = recent_msgs_.begin(); it != recent_msgs_.end(); it++)
		{
			socket->write(*it);
		}

		socket->do_read_header();
	}

	void leave(jess::asio::network::socket_communicating::shared_ptr socket)
	{
		//socket_vector_.erase(socket);
	}

	void deliver(jess::asio::message::shared_ptr msg)
	{
		note("deliver");
		
		recent_msgs_.push_back(msg);

		while (recent_msgs_.size() > max_recent_msgs)
		{
			recent_msgs_.pop_front();
		}

		for (auto it = socket_vector_.begin(); it != socket_vector_.end(); it++)
		{
			(*it)->write(msg);
		}
	}

	void process_accept(jess::asio::network::socket_communicating::shared_ptr socket)
	{
		note("process_accept");
		
		socket->process_body_ = boost::bind(&chat_server::deliver,this,_1);

		join(socket);
	}

private:
	jess::asio::message::deque	recent_msgs_;

	enum { max_recent_msgs = 100 };
};

//----------------------------------------------------------------------

//----------------------------------------------------------------------

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2)
		{
			std::cerr << "Usage: chat_server <port> [<port> ...]\n";
			return 1;
		}
		
		boost_io_service_ptr io_service(new boost::asio::io_service);
		
		std::list<chat_server> servers;

		for (int i = 1; i < argc; ++i)
		{
			boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), std::atoi(argv[i]));

			servers.emplace_back(io_service, endpoint);
		}
		
		io_service->run();
		
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}


