#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>

#include <js/Master.h>
#include <js/Event.h>

namespace js
{
	Master master;
}

void js::Master::Init()
{
	event_device_list_.insert({LOGITECH,	MOUSE,		0});
	event_device_list_.insert({LOGITECH,	KEYBOARD,	0});
	event_device_list_.insert({XBOX,	CONTROLLER,	0});
	event_device_list_.insert({SONY,	SIXAXIS,	0});
	
	scan_event_devices();
}
void	js::Master::Launch()
{
	for(auto it = event_devices_.begin(); it != event_devices_.end(); ++it)
	{
		(*it).second->Launch();
	}
}
void	js::Master::Join()
{
	for(auto it = event_devices_.begin(); it != event_devices_.end(); ++it)
	{
		(*it).second->Join();
	}

}
void js::Master::scan_event_devices()
{	
	int fd;
	char filename[64];

	for(int i = 0; i < 32; i++)
	{
		snprintf(filename, sizeof(filename), "/dev/input/event%i", i);

		// try to open
		fd = device_open(filename);

		if (fd == -1) break;

		event_device_id id = device_info(fd);


		auto it = event_device_list_.find(id);

		if(it != event_device_list_.end())
		{
			id.count = map_event_device_count_[id]++;
			
			
			std::shared_ptr<js::Event> device(new js::Event);
			device->fd_ = fd;

			event_devices_[id] = device;

			device->Init();
		}
		else
		{
			close(fd);
		}
	}

}
std::shared_ptr<js::Event> js::Master::find_event_device(js::event_device_id id)
{
	auto it = event_devices_.find(id);

	if(it != event_devices_.end()) return (*it).second;

	return std::shared_ptr<js::Event>();
}
int js::Master::device_open(char * filename)
{
	int fd, version;

	fd = open(filename, O_RDONLY);

	if(fd == -1)
	{
		perror("open");
		return -1;
	}

	//if(verbose) fprintf(stderr,"%s\n",filename);

	if(ioctl(fd, EVIOCGVERSION, &version) == -1)
	{
		perror("ioctl EVIOCGVERSION");
		close(fd);
		return -1;
	}

	if (EV_VERSION != version)
	{
		fprintf(stderr, "protocol version mismatch (expected %i, got %i)\n", EV_VERSION, version);
		close(fd);
		return -1;
	}

	return fd;
}

js::event_device_id js::Master::device_info(int fd)
{
	struct input_id id;

	__u32 bits[32];
	char buf[32];
	int rc,bit;

	rc = ioctl(fd, EVIOCGID, &id);

	if (rc >= 0)
	{
		fprintf(stderr,
				"   bustype : 0x%x\n"
				"   vendor  : 0x%x\n"
				"   product : 0x%x\n"
				"   version : %d\n",
				id.bustype,
				id.vendor,
				id.product,
				id.version);
	}

	rc = ioctl(fd,EVIOCGNAME(sizeof(buf)),buf);

	if (rc >= 0) fprintf(stderr,"   name    : \"%.*s\"\n",rc,buf);

	rc = ioctl(fd,EVIOCGPHYS(sizeof(buf)),buf);

	if (rc >= 0) fprintf(stderr,"   phys    : \"%.*s\"\n",rc,buf);

	rc = ioctl(fd,EVIOCGUNIQ(sizeof(buf)),buf);

	if (rc >= 0) fprintf(stderr,"   uniq    : \"%.*s\"\n",rc,buf);

	rc = ioctl(fd,EVIOCGBIT(0,sizeof(bits)),bits);

	if (rc >= 0)
	{
		fprintf(stderr,"   bits ev :");

		for (bit = 0; bit < rc*8 && bit < EV_MAX; bit++)
		{
			//if(test_bit(bit, bits)) fprintf(stderr," %s", EV_NAME[bit]);
		}
		fprintf(stderr,"\n");
	}
	fprintf(stderr,"\n");

	return {id.vendor, id.product};

}
