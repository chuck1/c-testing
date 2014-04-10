#ifndef __KERNEL_KERNEL_HPP__
#define __KERNEL_KERNEL_HPP__

#include <ker/define.hpp>

#include <ker/factory.hpp>
#include <ker/module/module.hpp>
#include <ker/module/desc.hpp>

namespace ker
{
	/** \brief kernel
	*/
	class kernel:
		public ker::module::module
	{
		public:
			virtual ~kernel(){}
			/** \brief create
			 *
			 * return a module using the description.
			 */
			virtual std::shared_ptr<ker::module::module>			request_module( std::shared_ptr<ker::module::desc> desc )
			{
				KERNEL_ASSERT( factory_ );
				KERNEL_ASSERT( desc );
				
				std::shared_ptr<ker::module::module> mod;
				
				switch ( desc->mode_ )
				{
					case ker::module::mode::KERNEL:
						mod = shared_from_this();
						break;
					case ker::module::mode::CREATE:
						mod = factory_->create( desc );
						
						KERNEL_ASSERT( mod );
						
						if ( desc->parent_.expired() )
						{
							desc->parent_ = request_module( desc->desc_parent_ );
						}
						
						mod->desc_ = desc;
						
						mod->initialize();
						
						break;
					case ker::module::mode::FIND:
						
						break;
					default:
						break;
				}		
				
				return mod;
			}

		public:
			/** \brief factory
			*/
			std::shared_ptr<ker::factory>			factory_;
	};
}

#endif
