// linmctool - Command-line tool for motion-sensing Bluetooth controllers.
// Copyright (c) 2010,2011 pabr@pabr.org
// See http://www.pabr.org/linmctool/
//
// Compile with: gcc --std=gnu99 -Wall linmctool.c -lusb -o linmctool

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>

// ----------------------------------------------------------------------
// USB support

#ifdef __USB__

#include <usb.h>
#define USB_DIR_IN 0x80
#define USB_DIR_OUT 0
#define USB_GET_REPORT 0x01
#define USB_SET_REPORT 0x09
#define VENDOR_SONY 0x054c
#define PRODUCT_SIXAXIS_DS3 0x0268
#define PRODUCT_PSMOVE 0x03d5

void usb_dump_readable_reports(usb_dev_handle *devh, int itfnum)
{
	for ( int rtype=0; rtype<=3; ++rtype )
	{
		for ( int rid=0; rid<256; ++rid )
		{
			unsigned char prev[64];
			for ( int c=0; c<repeat_dump; ++c )
			{
				unsigned char r[64];
				int nr = usb_control_msg( devh, USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE, USB_GET_REPORT, (rtype<<8)|rid, itfnum, (void*)r, sizeof(r), 5000);
				if ( c==0 || nr<0 || memcmp(r,prev,nr) )
				{
					printf("  USB READ %-7s 0x%02x %c ",
							rtypename[rtype], rid, c?'#':'=');
					if ( nr < 0 )
					{
						printf("ERR %d", nr);
					}
					else
					{
						printf("[%3d]", nr);
						for ( int i=0; i<nr; ++i ) printf(" %02x", r[i]);
					}
					printf("\n");  fflush(stdout);
				}
				memcpy(prev, r, sizeof(prev));
			}
		}
	}
	exit(0);
}
void usb_dump_writable_reports(usb_dev_handle *devh, int itfnum)
{
	for ( int rtype=0; rtype<=3; ++rtype )
	{
		for ( int rid=0; rid<256; ++rid )
		{
			unsigned char r[16];

			memset(r, 0, sizeof(r));

			int nr = usb_control_msg( devh, USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE, USB_SET_REPORT, (rtype<<8)|rid, itfnum, (void*)r, sizeof(r), 5000);

			printf("  USB WRITE %-7s 0x%02x [%d] -> [%d] %s\n", rtypename[rtype], rid, sizeof(r), nr, (nr<0)?strerror(-nr):"");

			fflush(stdout);
		}
	}
	exit(0);
}

void usb_poll_report(usb_dev_handle *devh, int itfnum, int report)
{
	int rtype = report >> 8;
	int rid = report & 255;
	while ( 1 )
	{
		unsigned char r[64];
		int nr = usb_control_msg( devh, USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE, USB_GET_REPORT, (rtype<<8)|rid, itfnum, (void*)r, sizeof(r), 5000);
		struct timeval tv;
		gettimeofday(&tv, NULL);
		printf("  %10lu.%06ld USB READ %-7s 0x%02x ", tv.tv_sec, tv.tv_usec, rtypename[rtype], rid);
		if ( nr < 0 )
		{
			printf("ERR %d", nr);
		}
		else
		{
			printf("[%3d]", nr);
			for ( int i=0; i<nr; ++i ) printf(" %02x", r[i]);
		}
		printf("\n");
	}
}

void usb_pair_device(struct usb_device *dev, int itfnum)
{

	usb_dev_handle *devh = usb_open(dev);

	if ( ! devh ) fatal("usb_open");

	usb_detach_kernel_driver_np(devh, itfnum);
	int res = usb_claim_interface(devh, itfnum);

	if ( res < 0 ) fatal("usb_claim_interface");
	if ( dump_readable ) usb_dump_readable_reports(devh, itfnum);
	if ( dump_writable ) usb_dump_writable_reports(devh, itfnum);
	if ( poll_report >= 0 ) usb_poll_report(devh, itfnum, poll_report);

	bdaddr_t current_ba;  // Current pairing address.

	switch ( dev->descriptor.idProduct )
	{
		case PRODUCT_SIXAXIS_DS3:
			{
				fprintf(stderr, "USB: SIXAXIS/DS3\n");
				unsigned char msg[8];
				res = usb_control_msg( devh, USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE, USB_GET_REPORT, 0x03f5, itfnum, (void*)msg, sizeof(msg), 5000);

				if ( res < 0 ) fatal("usb_control_msg(read master)");

				for ( int i=0; i<6; ++i ) current_ba.b[i] = msg[7-i];

				break;

			}
		case PRODUCT_PSMOVE:
			{
				fprintf(stderr, "USB: PS MOVE\n");
				unsigned char msg[16];
				int res = usb_control_msg
					(devh, USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
					 USB_GET_REPORT, 0x0304, itfnum, (void*)msg, sizeof(msg), 5000);

				if ( res < 0 ) fatal("usb_control_msg(read master)");

				for ( int i=0; i<6; ++i ) current_ba.b[i] = msg[10+i];

				break;
			}
	}

	bdaddr_t ba;  // New pairing address.

	if ( usb_force_master && !mystr2ba(usb_force_master,&ba) )
		;
	else {
		char ba_s[18];
		FILE *f = popen("hcitool dev", "r");
		if ( !f || fscanf(f, "%*s\n%*s %17s", ba_s)!=1 || mystr2ba(ba_s, &ba) )
			fatal("Unable to retrieve local bd_addr from `hcitool dev`.\n");
		pclose(f);
	}

	// Perform pairing.

	if ( ! bacmp(&current_ba, &ba) )
	{
		fprintf(stderr, "  Already paired to %s\n", myba2str(&ba));
	}
	else
	{
		fprintf(stderr, "  Changing master from %s to %s\n",
				myba2str(&current_ba), myba2str(&ba));
		switch ( dev->descriptor.idProduct )
		{
			case PRODUCT_SIXAXIS_DS3:
				{
					char msg[8] =
					{ 0x01, 0x00, ba.b[5],ba.b[4],ba.b[3],ba.b[2],ba.b[1],ba.b[0] };
					res = usb_control_msg
						(devh, USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
						 USB_SET_REPORT, 0x03f5, itfnum, msg, sizeof(msg), 5000);
					if ( res < 0 ) fatal("usb_control_msg(write master)");
					break;
				}
			case PRODUCT_PSMOVE:
				{
					char msg[]= { 0x05, ba.b[0], ba.b[1], ba.b[2], ba.b[3],
						ba.b[4], ba.b[5], 0x10, 0x01, 0x02, 0x12 };
					res = usb_control_msg
						(devh, USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
						 USB_SET_REPORT, 0x0305, itfnum, msg, sizeof(msg), 5000);
					if ( res < 0 ) fatal("usb_control_msg(write master)");
					break;
				}
		}
	}

	if ( dev->descriptor.idProduct == PRODUCT_SIXAXIS_DS3 )
		fprintf(stderr, "  Now unplug the USB cable and press the PS button.\n");
	else
		fprintf(stderr, "  Now press the PS button.\n");
}

void usb_scan()
{
	usb_init();
	if ( usb_find_busses() < 0 ) fatal("usb_find_busses");
	if ( usb_find_devices() < 0 ) fatal("usb_find_devices");

	struct usb_bus *busses = usb_get_busses();

	if ( ! busses ) fatal("usb_get_busses");

	struct usb_bus *bus;

	for ( bus=busses; bus; bus=bus->next )
	{
		struct usb_device *dev;
		for ( dev=bus->devices; dev; dev=dev->next)
		{
			struct usb_config_descriptor *cfg;
			for ( cfg = dev->config; cfg < dev->config + dev->descriptor.bNumConfigurations; ++cfg )
			{
				int itfnum;
				for ( itfnum=0; itfnum<cfg->bNumInterfaces; ++itfnum )
				{
					struct usb_interface *itf = &cfg->interface[itfnum];
					struct usb_interface_descriptor *alt;
					for ( alt = itf->altsetting; alt < itf->altsetting + itf->num_altsetting; ++alt )
					{
						if ( dev->descriptor.idVendor == VENDOR_SONY &&
								(dev->descriptor.idProduct == PRODUCT_SIXAXIS_DS3 ||
								 dev->descriptor.idProduct == PRODUCT_PSMOVE) &&
								alt->bInterfaceClass == 3 )
						{
							usb_pair_device(dev, itfnum);
						}
					}
				}
			}
		}
	}
}

#else // WITHOUT_USB

void usb_scan() { }

#endif


