#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t loop = 1;

void handler(int sig)
{
	fprintf(stdout,"signal:%i\n",sig);
	loop = 0;
}

int main()
{
	signal(SIGTERM,handler);
	signal(SIGINT,handler);
	//signal(SIGINT,handler);

	
	long int a = 0;
	while(loop)
	{
		sleep(1);
		fprintf(stdout,"%i\n",a++);
	}
	
	return 0;
}

