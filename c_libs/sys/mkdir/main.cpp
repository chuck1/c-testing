#define _POSIX_SOURCE
#include <sys/stat.h>
#include <unistd.h>
#undef _POSIX_SOURCE


#include <iostream>
using namespace std;

int main(int ac,char** av) {

	if(ac != 2) {
		cout << "usage: " << av[0] << " <dir>" << endl;
		return 1;
	}
	

	int result = mkdir(av[1],S_IRWXU|S_IRGRP|S_IXGRP);
	
	if(result != 0) {
		perror("mkdir:");
		return 1;
	}

	cout << result << endl;
	
	return 0;

}



