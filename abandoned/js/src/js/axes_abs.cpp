#include <sys/types.h>


#include <js/axes_abs.h>

js::axes_abs::axes_abs():
	mean_(1.0f)
{

}
float js::axes_abs::operator()(__s32 value)
{
	float m = 2.0f / range_;
	
	return ( (float)value - max_ ) * m + 1.0f;
}



