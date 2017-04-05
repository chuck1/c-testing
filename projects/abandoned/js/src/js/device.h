#ifndef __JS_DEVICE_H__
#define __JS_DEVICE_H__

#include <SIG/signal.h>

namespace js
{
	class device
	{
		protected:
			device( device const & ) = default;
			device&				operator=( device const & ) = default;
		public:
			device();
			void				open(char const *);
			void				info();
			void				read();
			void				close();
			void				run();
			//SIG::signal*			signals;

			int fd_;
	};
}

#endif
