#ifndef __JSL_MASTER_H__
#define __JSL_MASTER_H__

#include <set>
#include <map>
#include <memory>

#include <linux/input.h>

#define LOGITECH 0x46d
#define KEYBOARD 0xc31c

#define LOGITECH 0x46d
#define MOUSE 0xc52b

#define XBOX 0x45e
#define CONTROLLER 0x291

#define SONY 0x54c
#define SIXAXIS 0x268

namespace js
{
	struct event_device_id
	{
		__u16 vendor;
		__u16 product;
		__u16 count;
	};
}

struct id_less
{
	bool operator()(js::event_device_id a, js::event_device_id b)
	{
		if(a.vendor == b.vendor)
		{
			if(a.product == b.product)
			{
				return (a.count < b.count);
			}

			return (a.product < b.product);
		}

		return (a.vendor > b.vendor);
	}
};

namespace js
{
	class Event;


	class Master
	{
		public:
			void				Init();

			void				Launch();
			void				Join();

			int				device_open(char*);
			event_device_id			device_info(int);
			void				scan_event_devices();
			std::shared_ptr<js::Event>	find_event_device(js::event_device_id id);




			std::map<event_device_id,std::shared_ptr<js::Event>,id_less>	event_devices_;
			std::set<event_device_id,id_less>				event_device_list_;
			std::map<event_device_id,__u16,id_less>				map_event_device_count_;
	};

	extern Master master;
}

#endif

