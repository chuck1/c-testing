#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <asio/message.hpp>

#include <asio/network/socket_client.hpp>

#include <print/print.hpp>

namespace ns1 = jess::asio::network;


void process_body(jess::asio::message::shared_ptr msg)
{
	std::cout.write(msg->body(), msg->body_length());
	std::cout << std::endl;
}

void run_service(boost_io_service_ptr io_service)
{
	//if(verb) std::cout << "running " << io_service.get() << std::endl;
	
	io_service->run();

	//if(verb) std::cout << "run finished " << io_service.get() << std::endl;
}

void chat_loop(jess::asio::network::socket_client::shared_ptr c)
{
	note("chat_loop start");

	char line[jess::asio::message::max_body_length + 1];
	
	while (std::cin.getline(line, jess::asio::message::max_body_length + 1))
	{
		jess::asio::message::shared_ptr msg(new jess::asio::message);

		msg->body_length(std::strlen(line));

		std::memcpy(msg->body(), line, msg->body_length());

		msg->encode_header();

		c->write(msg);
	}
	
	c->close();
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: chat_client <host> <port>" << std::endl;
			return 1;
		}
		
		boost_io_service_ptr io_service(new boost::asio::io_service);
		
		boost::asio::ip::tcp::resolver resolver(*io_service);
		
		auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
		
		jess::asio::network::socket_client::shared_ptr c(new jess::asio::network::socket_client(io_service, endpoint_iterator));
		
		c->process_body_ = process_body;
		
		boost::thread t;
		
		boost::asio::io_service::work w(*io_service);
		{
			t = boost::thread(boost::bind(&run_service,io_service));
			
			chat_loop(c);
		}
		
		t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	
	//if(verb) std::cout << "exiting" << std::endl;

	return 0;
}


