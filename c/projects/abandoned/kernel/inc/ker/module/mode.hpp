#ifndef __KERNEL_MODULE_MODE_HPP__
#define __KERNEL_MODULE_MODE_HPP__

#include <stdint.h>

namespace ker
{
	namespace module
	{
		/** \brief mode
		 */
		enum mode: uint16_t
		{
			INVALID		= 0X0,
			CREATE		= 0x1,
			FIND		= 0x2,
			KERNEL		= 0x3,
		};
	}
}

#endif
