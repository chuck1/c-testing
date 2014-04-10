#ifndef __NEBULA_FRAMEWORK_KERNEL_HPP__
#define __NEBULA_FRAMEWORK_KERNEL_HPP__

#include <memory>

#include <ker/ns.hpp>

namespace ker
{
	namespace module
	{
		/** \brief module parent
		*/
		class parent
		{
			protected:
				/** \brief request
				*/
				virtual std::shared_ptr< ker::module::module>		request_module( std::shared_ptr< ker::module::desc> ) = 0;
		};
	}
}

#endif
