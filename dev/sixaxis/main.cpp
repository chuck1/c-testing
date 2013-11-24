#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <js/Master.h>
#include <js/Event.h>

float ax,ay,az;

int handle_abs(unsigned short code, float value)
{
	switch( code)
	{
		case 0x3c:
			ax = value;
			break;
		case 0x3d:
			ay = value;
			break;
		case 0x3e:
			az = value;
			break;
	}

	
	printf("% 3.2f % 3.2f % 3.2f\n",ax,ay,az);	
	
	
	return 1;
}
int main(int argc,char** argv)
{
	js::master.Init();

	js::event_device_id id = {SONY, SIXAXIS};

	std::shared_ptr<js::Event> ev = js::master.find_event_device(id);

	//ev->Set(js::Event::flag::PRINT);

	ev->sig_abs_.connect(handle_abs);

	ev->Launch();

	ev->Join();

	return 0;
}



