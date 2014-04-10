#ifndef __NEBULA_PLATFORM_JOYSTICK_HPP__
#define __NEBULA_PLATFORM_JOYSTICK_HPP__

#include <SIG/signal.h>

namespace JSL
{
	class device
	{
		protected:
			base( base const & ) = default;
			base&				operator=( base const & ) = default;
		public:
			base();
			void				open();
			void				close();
			void				run();
			SIG::signal*			signals;
	};
}

#endif
