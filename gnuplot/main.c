#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void mywrite(int fd, char const *s)
{
	write(fd, s, strlen(s));
}
int method3()
{
	FILE * fp = popen("gnuplot", "w");
	printf("fp=%p\n", fp);

	for(int i = 1; i < 5; ++i)
	{
		fprintf(fp, "plot [0:%i] sin(x)\n", i);
		if (ferror (fp))
		{
			fprintf (stderr, "Output to stream failed.\n");
			exit (EXIT_FAILURE);
		}      

		fflush(fp);

		sleep(1);
	}

	int rc = pclose(fp);
	printf("pclose rc=%i\n", rc);
}
int method1()
{
	int fd;
	//char * myfifo = "/tmp/myfifo";
	char * myfile = "myfifo";

	/* create the FIFO (named pipe) */
	//printf("mkfifo\n");
	//mkfifo(myfifo, 0666);

	printf("open\n");
	fd = open(myfile, O_WRONLY);

	printf("system call\n");
	int rc = system("gnuplot -p < myfifo");
	printf("system rc: %i\n", rc);

	printf("write\n");
	mywrite(fd, "plot [-3:3] sin(x)\n");

	printf("close\n");
	close(fd);

	printf("done\n");
	return 0;
}
int method2()
{
	int fd;
	//char * myfifo = "/tmp/myfifo";
	char * myfifo = "myfifo";

	/* create the FIFO (named pipe) */
	printf("mkfifo\n");
	mkfifo(myfifo, 0666);

	printf("system call\n");
	system("gnuplot < myfifo");

	printf("open\n");
	fd = open(myfifo, O_WRONLY);
	printf("write\n");
	mywrite(fd, "plot [-3:3] sin(x)");
	printf("close\n");
	close(fd);

	/* remove the FIFO */
	printf("unlink\n");
	unlink(myfifo);

	printf("done\n");
	return 0;
}
int main()
{
	method3();
	return 0;
}
