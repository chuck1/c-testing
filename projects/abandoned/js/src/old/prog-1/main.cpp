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

#include <command.hpp>

#ifdef __BLUE__
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>
#endif

#ifdef __USB__
#include <usb.h>
#define USB_DIR_IN 0x80
#define USB_DIR_OUT 0
#define USB_GET_REPORT 0x01
#define USB_SET_REPORT 0x09
#define VENDOR_SONY 0x054c
#define PRODUCT_SIXAXIS_DS3 0x0268
#define PRODUCT_PSMOVE 0x03d5
#endif

#include <joystick/usb.hpp>


// Global configuration

int verbose = 0;
int enable_ir = 0;
int enable_wmp = 0;
int def_rgb[3] = { 0, 0, 0 };
int output_text = 0;
int output_binary = 0;
int dump_readable = 0;
int dump_writable = 0;
int repeat_dump = 1;
int poll_report = -1;
char *usb_force_master = NULL;
int force_sixaxis = 0;
int force_ds3 = 0;
int timestamp = 0;
int nostdin = 0;

void fatal(char *msg)
{
	if ( errno ) perror(msg); else fprintf(stderr, "%s\n", msg);
	exit(1);
}


/**********************************************************************/
// Main

void	loop();

void usage()
{
	fprintf(stderr, "linmctool version TBD.\n");
	fprintf(stderr, "Usage: linmctool [options] [BDADDR...]\n"
			"  [--master BDADDR]   Pair USB devices with this adapter\n"
			"  [--ir]              [WIIMOTE] Enable IR tracking\n"
			"  [--wmp]             [WIIMOTE] Enable MotionPlus\n"
			"  [--rgb R,G,B]       [PSMOVE] Default bulb color\n"
			"  [--timestamp]       Print timestamp\n"
			"  [--force-sixaxis]   Force detection of SIXAXIS\n"
			"  [--force-ds3]       Force detection of DS3\n"
			"  [--binary]          Write raw reports to stdout\n"
			"  [--verbose]         Print debugging information\n"
			"  [--dump-readable]   Try to read all reports\n"
			"  [--dump-writable]   Try to write all reports (dangerous)\n"
			"  [--repeat-dump N]   Try to write all reports (dangerous)\n"
			"  [--poll-report N]   Poll (ReportType<<8 | ReportID)\n"
			"  [--nostdin]         Do not read from standard input\n");
	exit(1);
}

int main( int argc, char *argv[] )
{
#ifdef __BLUE__

	struct motion_dev *devs = NULL;
	int next_devindex = 0;

	int csk = 0;
	int isk = 0;
	csk = l2cap_listen(BDADDR_ANY, L2CAP_PSM_HIDP_CTRL);
	isk = l2cap_listen(BDADDR_ANY, L2CAP_PSM_HIDP_INTR);


	if ( csk>=0 && isk>=0 )
	{
		fprintf(stderr, "Waiting for Bluetooth connections.\n");
	}
	else
	{
		fprintf(stderr, "Unable to listen on HID PSMs. Only Wiimote will be supported\n");
	}

	int binary_skip = 5;  // Avoid confusing binhistogram.

#endif

	command c( argc, argv );
	c.add( { '-', "master"       , true } );
	c.add( { '-', "ir"           , true } );
	c.add( { '-', "wmp"          , true } );
	c.add( { '-', "rgb"          , true } );
	c.add( { '-', "timestamp"    , true } );
	c.add( { '-', "force-sixaxis", true } );
	c.add( { '-', "force-ds3"    , true } );
	c.add( { '-', "text"         , true } );
	c.add( { '-', "binary"       , true } );
	c.add( { '-', "verbose"      , true } );
	c.add( { '-', "dump-readable", true } );
	c.add( { '-', "dump-writable", true } );
	c.add( { '-', "repeat-dump"  , true } );
	c.add( { '-', "poll-report"  , true } );
	c.add( { '-', "nostdin"      , true } );




	/*
	   for ( int i=1; i<argc; ++i )
	   {
	   if ( ! strcmp(argv[i], "--master") && i+1<argc ) usb_force_master = argv[++i];
	   else if ( ! strcmp(argv[i], "--ir") )            enable_ir = 1;
	   else if ( ! strcmp(argv[i], "--wmp") )           enable_wmp = 1;
	   else if ( ! strcmp(argv[i], "--rgb") && i+1<argc && sscanf(argv[i+1],"%d,%d,%d", &def_rgb[0],&def_rgb[1],&def_rgb[2])==3 ) ++i;
	   else if ( ! strcmp(argv[i], "--timestamp") )     timestamp = 1;
	   else if ( ! strcmp(argv[i], "--force-sixaxis") ) force_sixaxis = 1;
	   else if ( ! strcmp(argv[i], "--force-ds3") )     force_ds3 = 1;
	   else if ( ! strcmp(argv[i], "--text") )          output_text = 1;
	   else if ( ! strcmp(argv[i], "--binary") )        output_binary = 1;
	   else if ( ! strcmp(argv[i], "--verbose") )       verbose = 1;
	   else if ( ! strcmp(argv[i], "--dump-readable") ) dump_readable = 1;
	   else if ( ! strcmp(argv[i], "--dump-writable") ) dump_writable = 1;
	   else if ( ! strcmp(argv[i], "--repeat-dump") && i+1<argc )
	   repeat_dump = atoi(argv[++i]);
	   else if ( ! strcmp(argv[i], "--poll-report") && i+1<argc )
	   poll_report = strtol(argv[++i], NULL, 0);
	   else if ( ! strcmp(argv[i], "--nostdin") ) nostdin = 1;
	   else
	   {
	   bdaddr_t ba;
	   if ( mystr2ba(argv[i], &ba) ) usage();
	   struct motion_dev *dev = connect_device(&ba);
	   dev->index = next_devindex++;
	   dev->next = devs;
	   devs = dev;
	   setup_device(dev);
	   }
	   }

*/




	usb_scan();

	if ( ! output_binary ) output_text = 1;

	
	while ( 1 )
	{

#ifdef __BLUE__
		fd_set fds;
		FD_ZERO(&fds);
		if ( ! nostdin ) FD_SET(0, &fds);
		
		int fdmax = 0;
		
		if ( csk >= 0 ) FD_SET(csk, &fds);
		if ( isk >= 0 ) FD_SET(isk, &fds);
		if ( csk > fdmax ) fdmax = csk;
		if ( isk > fdmax ) fdmax = isk;

		for ( struct motion_dev *dev=devs; dev; dev=dev->next )
		{
			FD_SET(dev->csk, &fds); if ( dev->csk > fdmax ) fdmax = dev->csk;
			FD_SET(dev->isk, &fds); if ( dev->isk > fdmax ) fdmax = dev->isk;
		}

		if ( select(fdmax+1,&fds,NULL,NULL,NULL) < 0 ) fatal("select");
		struct timeval tv;
		gettimeofday(&tv, NULL);
		time_t now = tv.tv_sec;

		// Incoming connection ?
		if ( csk>=0 && FD_ISSET(csk,&fds) )
		{
			struct motion_dev *dev = accept_device(csk, isk);
			dev->index = next_devindex++;
			dev->next = devs;
			devs = dev;
			setup_device(dev);
		}

		// Incoming input report ?
		for ( struct motion_dev *dev=devs; dev; dev=dev->next )
		{
			if ( FD_ISSET(dev->isk, &fds) )
			{
				unsigned char report[256];
				int nr = recv(dev->isk, report, sizeof(report), 0);
				if ( nr <= 0 )
				{
					fprintf(stderr, "%d disconnected\n", dev->index);
					close(dev->csk); close(dev->isk);
					struct motion_dev **pdev;

					for ( pdev=&devs; *pdev!=dev; pdev=&(*pdev)->next ) ;

					*pdev = dev->next;
					free(dev);
				}
				else
				{
					if ( verbose ) dump("RECV", report, nr);

					if ( report[0] == 0xa1 )
					{
						if ( output_binary )
						{
							if ( ! binary_skip )
							{
								write(1, report, nr);
							}
							else
							{
								--binary_skip;
							}
						}
						else
						{
							parse_report(dev, report+1, nr-1);
							fflush(stdout);
						}
					}
				}
			}
		}
	}


	// User command on stdin ?
	if ( FD_ISSET(0, &fds) )
	{
		char line[256];
		if ( ! fgets(line, sizeof(line), stdin) ) return 0;
		int index, rgb[3];
		if ( sscanf(line, "%d rgb %d,%d,%d", &index, &rgb[0], &rgb[1], &rgb[2]) == 4 )
		{
			for ( struct motion_dev *dev=devs; dev; dev=dev->next )
			{
				if ( dev->index==index && dev->type==PSMOVE )
				{
					memcpy(dev->rgb, rgb, sizeof(dev->rgb));
					if ( ! dev->latest_refresh )
						dev->latest_refresh = now-4;  // Force send now (see below).
				}
			}
		}
	}


	// Periodic stuff.
	for ( struct motion_dev *dev=devs; dev; dev=dev->next )
	{
		if ( dev->type==PSMOVE && dev->latest_refresh && now>=dev->latest_refresh+3 )
		{
			for ( int i=0; i<3; ++i )
			{
				if ( dev->rgb[i] > 64 )
				{
					fprintf(stderr, "Limiting brightness to 25%%\n");
					dev->rgb[i] = 64;
				}
			}

			psmove_set_rgb(dev, dev->rgb);
			dev->latest_refresh = ( dev->rgb[0] || dev->rgb[1] || dev->rgb[2] ) ? now : 0;
		}
	}

#endif
}

return 0;
}

