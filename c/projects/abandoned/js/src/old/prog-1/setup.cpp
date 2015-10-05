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

//#include <bluetooth/bluetooth.h>
//#include <bluetooth/l2cap.h>

/**********************************************************************/
// Device setup

#define IR0 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x41
#define IR1 0x40, 0x00

#define BIT1 2

void dump(const char *tag, const unsigned char *buf, int len)
{
	fprintf(stderr, "%s[%d]", tag, len);
	for ( int i=0; i<len; ++i ) fprintf(stderr, " %02x", buf[i]);
	fprintf(stderr, "\n");
}

void hidp_trans(int csk, const char *buf, int len)
{
	if ( verbose ) dump("SEND", (unsigned char*)buf, len);
	if ( send(csk, buf, len, 0) != len ) fatal("send(CTRL)");
	unsigned char ack;
	int nr = recv(csk, &ack, sizeof(ack), 0);
	if ( verbose) fprintf(stderr, "    result %d  %02x\n", nr, ack);
	if ( nr!=1 || ack!=0 ) fatal("ack");
}

void wiimote_command(struct motion_dev *dev, char *req, int n)
{
	// Try 3 times.
	for ( int try=0; try<3; ++try ) {
		// Send command
		hidp_trans(dev->csk, req, n);
		// Wait for application-level ack
		for ( int c=0; c<100; ++c ) {
			fd_set fds; FD_ZERO(&fds); FD_SET(dev->isk, &fds);
			struct timeval tv = { .tv_sec=1, .tv_usec=0 };
			if ( select(dev->isk+1,&fds,NULL,NULL,&tv) != 1 ) break;
			unsigned char rsp[16];
			int nr = recv(dev->isk, rsp, sizeof(rsp), 0);
			if ( verbose ) dump("WAIT", rsp, nr);
			if ( nr>=2 && rsp[1]==0x22 ) return;
		}
		fprintf(stderr, "req %02x not acked, retrying\n", req[1]);
	}
	fprintf(stderr, "req %02x failed\n", req[1]);
	fatal("wiimote_command");
}

void setup_device(struct motion_dev *dev)
{
	if ( dump_readable ) bluetooth_dump_readable_reports(dev->csk);
	if ( dump_writable ) bluetooth_dump_writable_reports(dev->csk);
	if ( poll_report >= 0 ) bluetooth_poll_report(dev->csk, poll_report);

	switch ( dev->type ) {
		case SIXAXIS:
		case DS3:
			{
				// Enable reporting
				char set03f4[] = { HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_FEATURE, 0xf4, 0x42, 0x03, 0x00, 0x00 };
				hidp_trans(dev->csk, set03f4, sizeof(set03f4));
				// Leds: Display 1+index in additive format.
				static const char ledmask[10] = { 1, 2, 4, 8, 6, 7, 11, 13, 14, 15 };

#define LED_PERMANENT 0xff, 0x27, 0x00, 0x00, 0x32

				char set0201[] = {
					HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_OUTPUT, 0x01,
					0x00, 0x00, 0x00, 0,0, 0x00, 0x00, 0x00,
					0x00, ledmask[dev->index%10]<<1,
					LED_PERMANENT,
					LED_PERMANENT,
					LED_PERMANENT,
					LED_PERMANENT,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				};
				if ( dev->type == SIXAXIS )
				{
					set0201[5] = 0xff;  // Enable gyro
					set0201[6] = 0x78;  // Constant bias (should adjust periodically ?)
				}
				else
				{
					set0201[5] = 0;     // Set to e.g. 20 to test rumble on startup
					set0201[6] = 0x70;  // Weak rumble
				}
				hidp_trans(dev->csk, set0201, sizeof(set0201));
				break;
			}
		case PSMOVE:
			{
				memcpy(dev->rgb, def_rgb, sizeof(dev->rgb));
				if ( dev->rgb[0] || dev->rgb[1] || dev->rgb[2] )
					dev->latest_refresh = 1;  // Force refresh in main loop.
				else
					dev->latest_refresh = 0;
				break;
			}
		case WIIMOTE:
			char req11[] = { 0x52, 0x11, 0x10|BIT1 };  // LED

			wiimote_command(dev, req11, sizeof(req11));

			unsigned char format = 0x31;

			if ( enable_wmp )
			{
				char setf0[23] = { 0x52, 0x16, 0x04, 0xa6,0x00,0xf0, 1, 0x55 };
				char setfe[23] = { 0x52, 0x16, 0x04, 0xa6,0x00,0xfe, 1, 0x04 };
				wiimote_command(dev, setf0, sizeof(setf0));
				wiimote_command(dev, setfe, sizeof(setfe));
				format |= 0x04;
			}

			if ( enable_ir ) {
				char req13[] = { 0x52, 0x13, 0x04|BIT1 };  // IR enable 1
				char req1a[] = { 0x52, 0x1a, 0x04|BIT1 };  // IR enable 2
				wiimote_command(dev, req13, sizeof(req13));
				wiimote_command(dev, req1a, sizeof(req1a));

				char set30[23] = { 0x52, 0x16, 0x04, 0xb0,0x00,0x30, 1, 0x01 };
				char set00[23] = { 0x52, 0x16, 0x04, 0xb0,0x00,0x00, 9, IR0 };
				char set1a[23] = { 0x52, 0x16, 0x04, 0xb0,0x00,0x1a, 2, IR1 };  
				int mode = enable_wmp ? 0x01 : 0x03;
				char set33[23] = { 0x52, 0x16, 0x04, 0xb0,0x00,0x33, 1, mode };
				char set30b[23] = { 0x52, 0x16, 0x04, 0xb0,0x00,0x30, 1, 0x08 };
				wiimote_command(dev, set30, sizeof(set30));
				wiimote_command(dev, set00, sizeof(set00));
				wiimote_command(dev, set1a, sizeof(set1a));
				wiimote_command(dev, set33, sizeof(set33));
				wiimote_command(dev, set30b, sizeof(set30b));
				format |= 0x02;
			}

			sleep(1);  // For some reason, this helps.
			char req12[] = { 0x52, 0x12, 0x00|BIT1, format };  // Format 0x33
			wiimote_command(dev, req12, sizeof(req12));
			break;

	}
	fprintf(stderr, "New device %d %s is a %s\n", dev->index, myba2str(&dev->addr), devtypename[dev->type]);
}

void psmove_set_rgb(struct motion_dev *dev, int rgb[3])
{
	char report[] = {
		HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_OUTPUT,
		2, 0, rgb[0],rgb[1],rgb[2], 0, 0
	};
	hidp_trans(dev->csk, report, sizeof(report));
}


