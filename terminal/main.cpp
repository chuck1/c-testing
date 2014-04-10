#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <stdio.h>

int term() {
	
	int pt = posix_openpt(O_RDWR | O_NOCTTY);
	if (pt == -1)
	{
		std::cerr << "Could not open pseudo terminal.\n";
		return EXIT_FAILURE;
	}


	char* ptname = ptsname(pt);
	if (!ptname)
	{
		std::cerr << "Could not get pseudo terminal device name.\n";
		close(pt);
		return EXIT_FAILURE;
	}

	if (unlockpt(pt) == -1)
	{
		std::cerr << "Could not get pseudo terminal device name.\n";
		close(pt);
		return EXIT_FAILURE;
	}

	std::ostringstream oss;

	std::cout << ptname << std::endl;
	
	//oss << "xterm -S" << (strrchr(ptname, '/')+1) << "/" << pt << " &";
	oss << "xterm -S" << (strrchr(ptname, '/')+1) << "/0";
	
	std::cout << oss.str() << std::endl;


	//exit(0);


	system(oss.str().c_str());

	int xterm_fd = open(ptname,O_RDWR);
	char c;
	do read(xterm_fd, &c, 1); while (c!='\n');



	char const * str = "welcome to the pseudo-terminal!\n";
	write(pt, str, strlen(str));
	
	
	do
	{
		int r = read(pt, &c, 1);
		if(r == 1) printf("%x",(int)c);
	}
	while(1);


	close(pt);

}

int main()
{
	/*	int pt = posix_openpt(O_RDWR);
		if (pt == -1)
		{
		std::cerr << "Could not open pseudo terminal.\n";
		return EXIT_FAILURE;
		}


		char* ptname = ptsname(pt);
		if (!ptname)
		{
		std::cerr << "Could not get pseudo terminal device name.\n";
		close(pt);
		return EXIT_FAILURE;
		}

		if (unlockpt(pt) == -1)
		{
		std::cerr << "Could not get pseudo terminal device name.\n";
		close(pt);
		return EXIT_FAILURE;
		}

		std::ostringstream oss;
		oss << "xterm -S" << (strrchr(ptname, '/')+1) << "/" << pt << " &";

		std::cout << oss.str();

		system(oss.str().c_str());

		int xterm_fd = open(ptname,O_RDWR);
		char c;
		do read(xterm_fd, &c, 1); while (c!='\n');*/
	/*
	   if (dup2(pt, 1) <0)
	   {
	   std::cerr << "Could not redirect standard output.\n";
	   close(pt);
	   return EXIT_FAILURE;
	   }
	   if (dup2(pt, 2) <0)
	   {
	   std::cerr << "Could not redirect standard error output.\n";
	   close(pt);
	   return EXIT_FAILURE;
	   }

	   std::cout << "This should appear on the xterm." << std::endl;
	   std::cerr << "So should this.\n";
	 */
	term();





	std::cin.ignore(1);


	return EXIT_SUCCESS;
}
