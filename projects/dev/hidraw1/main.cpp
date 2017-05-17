#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>



int main(int argc,char** argv)
{
	int fd = open(argv[0], O_RDONLY);

if( fd < 0)
{
perror("open");
exit(0);
}
	
	int bytes;
	char buf[256];
	
	while(1)
	{
		bytes = read(fd, buf, 256);
if( bytes < 0 )
{
perror("read");
}		


		printf("%i\n",bytes);
	}
	
	return 0;
}



