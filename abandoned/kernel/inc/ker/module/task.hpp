#ifndef __KERNEL_MODULE_INIT_TASK_HPP__
#define __KERNEL_MODULE_INIT_TASK_HPP__

#include <stdlib.h>
#include <stdint.h>
#include <exception>
#include <map>
#include <memory>

#include <ker/define.hpp>
#include <ker/ns.hpp>

namespace ker
{
	namespace module
	{
		/** \brief tasks
		 */
		struct tasks
		{
			public:
				tasks();
				tasks&								operator=( tasks const & t );
				operator bool();
				void								run();
				//std::shared_ptr<ker::module::module>				parent_;
				uint32_t							task_flag_;
				std::map<uint32_t,std::shared_ptr<ker::module::task> >		task_map_;
		};


		/** \brief task
		 */
		struct task
		{
			public:
				task();
				task( std::function<void()> func );
				task&							operator=( task const & task );
				operator bool();
				void							run();
				//std::shared_ptr<ker::module::module>			parent_;
				std::function<void()>					func_;
				bool							complete_;
				ker::module::tasks					tasks_;
		};
	}
}

#endif
