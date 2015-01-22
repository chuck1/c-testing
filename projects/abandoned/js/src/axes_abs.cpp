#include <sys/types.h>


#include <JSL/axes_abs.h>

JSL::axes_abs::axes_abs():
	mean_(1.0f)
{

}
float JSL::axes_abs::operator()(__s32 value)
{
	float m = 2.0f / range_;
	
	return ( (float)value - max_ ) * m + 1.0f;
}

