#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int pipe_write(char const* data_out, int len)
{
	int fd;
	char fifo_name[] = "/tmp/myfifo";
	
	mkfifo(fifo_name, 0666);
	
	fd = open(fifo_name, O_WRONLY);
	
	int a = write(fd, data_out, len);
	
	close(fd);

	return a;
}
int pipe_read(char * buf, int len)
{
	int fd;
	char fifo_name[] = "/tmp/myfifo";
	
	mkfifo(fifo_name, 0666);
	
	fd = open(fifo_name, O_RDONLY);
	
	int a = read(fd, buf, len);
	
	//printf("received: %s\n", buf);
	
	close(fd);

	return a;
}



