#ifndef __KERNEL_MODULE_TASK_HPP__
#define __KERNEL_MODULE_TASK_HPP__

#include <ker/module/task.hpp>

ker::module::tasks::tasks():
	task_flag_(0)
{
	KERNEL_LOG_FUNC;
}
ker::module::tasks&					ker::module::tasks::operator=( ker::module::tasks const & t )
{
	KERNEL_LOG_FUNC;

	task_flag_	= t.task_flag_;
	task_map_	= t.task_map_;

	return *this;
}
ker::module::tasks::operator bool()
{
	return ( task_flag_ == 0 );
}
void							ker::module::tasks::run()
{
	while( task_flag_ )
	{
		int count = 0;

		for( uint8_t i = 0; i < 32; i++ )
		{
			uint32_t mask = 1 << i;
			if( task_flag_ & mask )
			{
				KERNEL_LOG( "%i %i\n", task_flag_, mask );	

				std::shared_ptr<ker::module::task> task = task_map_[mask];

				KERNEL_ASSERT( task );

				try 
				{
					task->run();

					task_flag_ &= ~mask;

					count++;
				}
				catch( std::exception& e )
				{
					KERNEL_LOG( "%s\n", e.what() );
				}
			}
		}

		if( count == 0 )
		{
			KERNEL_LOG( "no in tasks progress\n" );
			exit(0);
		}
	}
}
ker::module::task::task():
	complete_( false )
{
	KERNEL_LOG_FUNC;
}
ker::module::task::task( std::function<void()> func ):
	func_( func ),
	complete_( false )
{
	KERNEL_LOG_FUNC;

	KERNEL_ASSERT( func_ );
}
ker::module::task&							ker::module::task::operator=( ker::module::task const & task )
{
	KERNEL_LOG_FUNC;

	func_		= task.func_;
	complete_	= task.complete_;
	tasks_		= task.tasks_;

	return *this;
}
ker::module::task::operator bool()
{
	return complete_;
}
void							ker::module::task::run()
{
	KERNEL_ASSERT( !complete_ );


	// this task
	if( func_ )
	{
		try
		{
			func_();

			complete_ = true;
		}
		catch( std::exception& e )
		{
			KERNEL_LOG( "%s\n", e.what() );
		}
	}
}

#endif
