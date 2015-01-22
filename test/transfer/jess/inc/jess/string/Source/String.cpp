#include <string.h>
#include <stdlib.h>


#include <Utilities/String.h>


int		String::strncmp( const char* str1, const char* str2, int num ) {
	int result = 0;

#ifdef __WINDOWS
	result = ::strncmp( str1, str2, num );
#elif defined __LINUX
	result = ::strncmp( str1, str2, num );
#endif
	
	return result;
}
char*	String::strncat( char* dest, unsigned int dest_count, const char* src, unsigned int src_count ) {
	char* result = 0;

#ifdef __WINDOWS
	errno_t err = ::strncat_s( dest, dest_count, src, src_count );

#elif defined __LINUX
	result = ::strncat( str1, str2, num );
#endif
	
	return result;
}






