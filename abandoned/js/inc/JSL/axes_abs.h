#ifndef __JSL_AXES_ABS_H__
#define __JSL_AXES_ABS_H__

#include <linux/input.h>
#include <sys/types.h>

namespace JSL
{
	class axes_abs
	{
		public:
			axes_abs();
			float min_;
			float max_;
			float mean_;
			float range_;

			float operator()(__s32);
	};
}


#endif
