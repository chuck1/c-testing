#include <cstdio>
#include <cstdlib>
#include <cstring>


#include <jess/asio/message.hpp>



jess::asio::message::message(): body_length_(0)
{
}
const char*		jess::asio::message::data() const
{
	return data_;
}
char*			jess::asio::message::data()
{
	return data_;
}
std::size_t		jess::asio::message::length() const
{
	return header_length + body_length_;
}
const char*		jess::asio::message::body() const
{
	return data_ + header_length;
}
char*			jess::asio::message::body()
{
	return data_ + header_length;
}
std::size_t		jess::asio::message::body_length() const
{
	return body_length_;
}
void			jess::asio::message::body_length(std::size_t new_length)
{
	body_length_ = new_length;
	if (body_length_ > max_body_length)
	{
		body_length_ = max_body_length;
	}
}
bool			jess::asio::message::decode_header()
{
	char header[header_length + 1] = "";

	std::strncat(header, data_, header_length);

	body_length_ = std::atoi(header);

	std::cout << "decoded header: \"" << header << "\" " << body_length_ << std::endl;

	if (body_length_ > max_body_length)
	{
		body_length_ = 0;
		return false;
	}

	return true;
}
void			jess::asio::message::encode_header()
{
	char header[header_length + 1] = "";
	std::sprintf(header, "%4d", int(body_length_));
	std::memcpy(data_, header, header_length);
}






