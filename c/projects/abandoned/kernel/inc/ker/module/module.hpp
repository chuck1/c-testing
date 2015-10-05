#ifndef __KER_MODULE_MODULE_HPP__
#define __KER_MODULE_MODULE_HPP__

#include <map>
#include <memory>

#include <stdint.h>

#include <ker/define.hpp>
#include <ker/ns.hpp>
#include <ker/module/desc.hpp>
#include <ker/module/task.hpp>

namespace ker
{
	namespace module
	{
		/** \brief module
		*/
		class module:
			public std::enable_shared_from_this<ker::module::module>
		{
			public:
				/** \brief ctor
				*/
				module()
				{
				}
				/** \brief dtor
				*/
				virtual ~module(){}
				/** \brief request
				*/
				virtual std::shared_ptr<ker::module::module>		request_module( std::shared_ptr<ker::module::desc> desc )
				{
					KERNEL_ASSERT( desc );
					KERNEL_ASSERT( desc_ );
					KERNEL_ASSERT( !desc_->parent_.expired() );

					std::shared_ptr<ker::module::module> mod = desc_->parent_.lock()->request_module( desc );

					return mod;
				}
				void							initialize()
				{
					tasks_init_.run();
				}
			public:
				/** \brief parent
				*/
				//std::weak_ptr<ker::module::module>			parent_;
				/** \brief desc
				*/
				std::shared_ptr<ker::module::desc>			desc_;
				ker::module::tasks					tasks_init_;
		};
	}
}


#endif

