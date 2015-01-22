#ifndef __JESS_ASIO_MESSAGE_HPP__
#define __JESS_ASIO_MESSAGE_HPP__

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <boost/function.hpp>

#include <memory> 
#include <deque>

namespace jess
{
	namespace asio
	{



		/// message
		class message
		{
		public:
			/// shared_ptr
			typedef std::shared_ptr<message>          shared_ptr;
			/// boost_function
			typedef boost::function<void(shared_ptr)> boost_function;
			/// deque
			typedef std::deque<shared_ptr>            deque;
			
			/// header length
			enum { header_length = 4 };
			/// max body length
			enum { max_body_length = 512 };
			
			/// ctor
			message();
						
			/// data
			const char*		data() const;
			/// data
			char*			data();
			
			/// length
			std::size_t		length() const;
			
			/// body
			const char*		body() const;
			/// body
			char*			body();
			
			/// body length
			std::size_t		body_length() const;
			/// body length
			void			body_length(std::size_t new_length);
			
			/// decode header
			bool			decode_header();
			/// encode header
			void			encode_header();

		private:
			/// data
			char			data_[header_length + max_body_length];
			/// body length
			std::size_t		body_length_;
		};




	}
}





#endif // __JESS_ASIO_MESSAGE_HPP__
