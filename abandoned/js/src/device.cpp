#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <stdlib.h> // exit()
#include <unistd.h> // close()

#include <JSL/device.h>



JSL::device::device()
{

}
void JSL::device::Open(char const * filename)
{

}
void JSL::device::Info()
{
	
}
void JSL::device::Read()
{
	char buf[512];
	
	int len = read(fd_, &buf, 512);
	if( len < 0 )
	{
		perror("read");
		exit(1);
	}
	
	printf("%i bytes read\n",len);
}
void JSL::device::Close()
{
	close(fd_);
}
/*void JSL::device::Read()
{
	read(
}*/


