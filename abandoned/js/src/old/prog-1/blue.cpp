// linmctool - Command-line tool for motion-sensing Bluetooth controllers.
// Copyright (c) 2010,2011 pabr@pabr.org
// See http://www.pabr.org/linmctool/
//
// Compile with: gcc --std=gnu99 -Wall linmctool.c -lusb -o linmctool

#ifdef __BLUE__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>


// ----------------------------------------------------------------------
// Replacement for libbluetooth

int mystr2ba(const char *s, bdaddr_t *ba)
{
	if ( strlen(s) != 17 ) return 1;
	for ( int i=0; i<6; ++i )
	{
		int d = strtol(s+15-3*i, NULL, 16);
		if ( d<0 || d>255 ) return 1;
		ba->b[i] = d;
	}
	return 0;
}

const char *myba2str(const bdaddr_t *ba)
{
	static char buf[2][18];  // Static buffer valid for two invocations.

	static int index = 0;

	index = (index+1)%2;

	sprintf(buf[index], "%02x:%02x:%02x:%02x:%02x:%02x", ba->b[5], ba->b[4], ba->b[3], ba->b[2], ba->b[1], ba->b[0]);

	return buf[index];
}

static const char *rtypename[] = { "OTHER", "INPUT", "OUTPUT", "FEATURE" };

/**********************************************************************/
// Bluetooth HID devices

static const char *devtypename[] =
{ "Wiimote", "Sixaxis", "DS3", "PS Move" };

struct motion_dev
{
	int index;
	bdaddr_t addr;
	enum { WIIMOTE, SIXAXIS, DS3, PSMOVE } type;
	int csk; 
	int isk;
	int rgb[3];  // For PSMOVE
	time_t latest_refresh;  // For PSMOVE. 0 if inactive.
	struct motion_dev *next;
};

#define L2CAP_PSM_HIDP_CTRL 0x11
#define L2CAP_PSM_HIDP_INTR 0x13

#define HIDP_TRANS_GET_REPORT    0x40
#define HIDP_TRANS_SET_REPORT    0x50
#define HIDP_DATA_RTYPE_INPUT    0x01
#define HIDP_DATA_RTYPE_OUTPUT   0x02
#define HIDP_DATA_RTYPE_FEATURE  0x03

void bluetooth_dump_readable_reports(int csk)
{
	for ( int rtype=0; rtype<=3; ++rtype )
	{
		for ( int rid=0; rid<256; ++rid )
		{
			unsigned char prev[64];
			for ( int c=0; c<repeat_dump; ++c )
			{
				unsigned char r[66];

				char get[] = { HIDP_TRANS_GET_REPORT | rtype | 8, rid, sizeof(r), sizeof(r)>>8 };

				send(csk, get, sizeof(get), 0);

				int nr = recv(csk, r, sizeof(r), 0);

				if ( c==0 || nr<0 || memcmp(r,prev,nr) )
				{
					printf("  BLUETOOTH READ %-7s 0x%02x %c ", rtypename[rtype], rid, c?'#':'=');
			
					if ( nr < 1 )
					{
						printf("ERR %d", nr);
					}
					else if ( r[0] == (0xa0|rtype) )
					{
						printf("[%3d]", nr-1);
					}
					else
					{
						printf("ERR %d", r[0]);
					}

					for ( int i=1; i<nr; ++i )
					{
						printf(" %02x", r[i]);
					}

					printf("\n"); fflush(stdout);
				}
				memcpy(prev, r, sizeof(prev));
			}
		}
	}
	exit(0);
}

void bluetooth_dump_writable_reports(int csk)
{
	for ( int rtype=0; rtype<=3; ++rtype )
	{
		for ( int rid=0; rid<256; ++rid )
		{
			char set[] = { HIDP_TRANS_SET_REPORT | rtype, rid, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };

			send(csk, set, sizeof(set), 0);

			unsigned char ack[16];

			int nr = recv(csk, ack, sizeof(ack), 0);

			printf("  BLUETOOTH WRITE %-7s 0x%02x [%d] -> [%d] %02x\n", rtypename[rtype], rid, sizeof(set)-2, nr, ack[0]);

			fflush(stdout);
		}
	}
	exit(0);
}

void bluetooth_poll_report(int csk, int report)
{
	int rtype = report >> 8;
	int rid = report & 255;
	while ( 1 )
	{
		unsigned char r[66];
		char get[] = { HIDP_TRANS_GET_REPORT | rtype | 8,
			rid, sizeof(r), sizeof(r)>>8 };
		send(csk, get, sizeof(get), 0);
		int nr = recv(csk, r, sizeof(r), 0);
		if ( nr < 0 ) fatal("recv");
		struct timeval tv;
		gettimeofday(&tv, NULL);
		printf("  %10lu.%06ld BLUETOOTH READ %-7s 0x%02x ",
				tv.tv_sec, tv.tv_usec, rtypename[rtype], rid);
		if ( r[0] == (0xa0|rtype) )
			printf("[%3d]", nr-1);
		else
			printf("ERR %d", r[0]);
		for ( int i=1; i<nr; ++i ) printf(" %02x", r[i]);
		printf("\n");
	}
}

// Incoming connections.

int l2cap_listen(const bdaddr_t *bdaddr, unsigned short psm)
{
	int sk = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
	if ( sk < 0 ) fatal("socket");

	struct sockaddr_l2 addr;
	memset(&addr, 0, sizeof(addr));
	addr.l2_family = AF_BLUETOOTH;
	addr.l2_bdaddr = *BDADDR_ANY;
	addr.l2_psm = htobs(psm);
	if ( bind(sk, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
	{
		perror("bind");
		close(sk);
		return -1;
	}

	if ( listen(sk, 5) < 0 ) fatal("listen");
	return sk;
}

struct motion_dev *accept_device(int csk, int isk)
{
	fprintf(stderr, "Incoming connection...\n");
	struct motion_dev *dev = malloc(sizeof(struct motion_dev));
	if ( ! dev ) fatal("malloc");

	dev->csk = accept(csk, NULL, NULL);
	if ( dev->csk < 0 ) fatal("accept(CTRL)");
	dev->isk = accept(isk, NULL, NULL);
	if ( dev->isk < 0 ) fatal("accept(INTR)");

	struct sockaddr_l2 addr;
	socklen_t addrlen = sizeof(addr);
	if ( getpeername(dev->isk, (struct sockaddr *)&addr, &addrlen) < 0 )
		fatal("getpeername");
	dev->addr = addr.l2_bdaddr;

	{
		// Distinguish SIXAXIS / DS3 / PSMOVE.
		unsigned char resp[64];

		char get03f2[] = { HIDP_TRANS_GET_REPORT | HIDP_DATA_RTYPE_FEATURE | 8, 0xf2, sizeof(resp), sizeof(resp)>>8 };

		send(dev->csk, get03f2, sizeof(get03f2), 0);  // 0301 is interesting too.

		int nr = recv(dev->csk, resp, sizeof(resp), 0);

		if ( nr < 19 )
		{
			dev->type = PSMOVE;
		}
		else if ( force_sixaxis )
		{
			dev->type = SIXAXIS;
		}
		else if ( force_ds3 )
		{
			dev->type = DS3;
		}
		else
		{
			dev->type = (resp[13]==0x40) ? SIXAXIS : DS3;  // My guess.
		}
	}

	return dev;
}

// Outgoing connections.

int l2cap_connect(bdaddr_t *ba, unsigned short psm)
{
	int sk = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);

	if ( sk < 0 ) fatal("socket");

	struct sockaddr_l2 daddr;
	memset(&daddr, 0, sizeof(daddr));
	daddr.l2_family = AF_BLUETOOTH;
	daddr.l2_bdaddr = *ba;
	daddr.l2_psm = htobs(psm);

	if ( connect(sk, (struct sockaddr *)&daddr, sizeof(daddr)) < 0 ) fatal("connect");

	return sk;
}

struct motion_dev *connect_device(bdaddr_t *ba)
{
	fprintf(stderr, "Connecting to %s\n", myba2str(ba));

	struct motion_dev *dev = malloc(sizeof(struct motion_dev));

	if ( ! dev ) fatal("malloc");

	dev->addr = *ba;
	dev->csk = l2cap_connect(ba, L2CAP_PSM_HIDP_CTRL);
	dev->isk = l2cap_connect(ba, L2CAP_PSM_HIDP_INTR);
	dev->type = WIIMOTE;

	return dev;
}

#endif
