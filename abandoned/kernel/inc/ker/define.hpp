#ifndef __KERNEL_DEFINE_HPP__
#define __KERNEL_DEFINE_HPP__

#include <stdio.h>

#include <assert.h>




#ifdef __LIN__
	#define KERNEL_FUNCSIG __PRETTY_FUNCTION__
#elif defined __WIN__
	#define KERNEL_FUNCSIG __FUNCSIG__
#else
	#error "must define __WIN__ or __LIN__"
#endif


#define KERNEL_ASSERT(x)	assert(x)
#define KERNEL_LOG(...)		printf( __VA_ARGS__ )
#define KERNEL_LOG_FUNC		printf( "%s\n", KERNEL_FUNCSIG )


#endif
