#ifndef __KERNEL_FACTORY_HPP__
#define __KERNEL_FACTORY_HPP__

#include <memory>

#include <ker/ns.hpp>

#include <ker/module/type.hpp>

namespace ker
{
	/** \brief factory
	 * The kernel uses a factory to create modules.
	 * The factory, unlike the kernel, knows all of the app-specific modules.
	 */
	class factory
	{
		public:
			/** \brief ctor
			*/
			factory()
			{}
			/** \brief dtor
			*/
			virtual ~factory()
			{}
			/** \brief create
			*/
			virtual std::shared_ptr<ker::module::module>		create( std::shared_ptr<ker::module::desc> desc )
			{
				KERNEL_LOG_FUNC;
			
				std::shared_ptr<ker::module::module> mod;

				/*
				   switch ( desc->type_ )
				   {
				   }
				   */

				return mod;
			}
	};
}


#endif



