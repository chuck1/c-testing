#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct event
{
	struct timeval time;
	unsigned short type;
	unsigned short code;
	unsigned int value;
};

int read_event( event* ev )
{
	
}

int main()
{
	int fd = -1;
	event* ev = new event;
	int bytes = -1;
	
	fd = open("/dev/input/mice",O_RDONLY | O_NONBLOCK);
	if ( fd == -1 )
	{
		printf("%s\n",strerror(errno));
		exit(0);
	}
	
	while(1)
	{
		bytes = read( fd, ev, sizeof(event) );
		
		if ( bytes == -1 )
		{
			printf("error bytes==-1");
			exit(0);
		}
	}
	
	
	
}

