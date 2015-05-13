#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd;
	char fifo_name[] = "/tmp/myfifo";
	char buf[64];
	
	mkfifo(fifo_name, 0666);
	
	fd = open(fifo_name, O_RDONLY);
	
	read(fd, buf, 64);
	
	printf("received: %s\n", buf );
	
	
	close(fd);
	
	
}

