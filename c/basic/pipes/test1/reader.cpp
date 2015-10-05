#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "fifo.hpp"

int main()
{
	char buf[64];
	
	pipe_read(buf, 64);
	
	printf("received: %s\n", buf );
}

