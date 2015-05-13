#include <stdio.h>
#include <thread>

int should_exit = 0;

void input() {
	int i = 1;
	while(i>0) {
		scanf("%i",&i);
	}
	should_exit = 1;
}

int main() {
	
	std::thread t(std::bind(input));
	
	while(should_exit == 0) {
		sleep(1);
		fprintf(stdout, "hello\n");
		
	}
		
	t.join();
}



