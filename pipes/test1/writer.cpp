#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int fd;
	char fifo_name[] = "/tmp/myfifo";
	
	mkfifo(fifo_name, 0666);
	
	fd = open(fifo_name, O_WRONLY);
	
	write(fd, "hello", 5);
	
	close(fd);
	
	
}

