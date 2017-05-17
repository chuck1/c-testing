#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <stdlib.h> // exit()
#include <unistd.h> // close()

#include <js/device.h>



js::device::device()
{

}
void js::device::open(char const * filename)
{

}
void js::device::info()
{
	
}
void js::device::read()
{
	char buf[512];
	
	int len = ::read(fd_, &buf, 512);
	if( len < 0 )
	{
		perror("read");
		exit(1);
	}
	
	printf("%i bytes read\n",len);
}
void js::device::close()
{
	::close(fd_);
}
/*void js::device::Read()
{
	read(
}*/


