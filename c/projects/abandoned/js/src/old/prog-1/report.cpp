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
// Reports

void wiimote_parse_accel(unsigned char *r)
{
	int aX = r[0] - 128;
	int aY = r[1] - 128;
	int aZ = r[2] - 128;
	printf(" aX=%-4d aY=%-4d aZ=%-4d", aX,aY,aZ);
}

void wiimote_parse_ir10(unsigned char *r)
{
	for ( int i=0; i<2; ++i ) {
		unsigned char *p = &r[i*5];
		int x1 = p[0] | ((p[2]<<4)&0x300);
		int y1 = p[1] | ((p[2]<<2)&0x300);
		int x2 = p[3] | ((p[2]<<8)&0x300);
		int y2 = p[4] | ((p[2]<<6)&0x300);
		printf(" ir%dx=%-4d ir%dy=%-4d ir%dx=%-4d ir%dy=%-4d",
				i*2,x1,i*2,y1, i*2+1,x2,i*2+1,y2);
	}
}

void wiimote_parse_ir12(unsigned char *r)
{
	for ( int i=0; i<4; ++i ) {
		unsigned char *p = &r[i*3];
		int x = p[0] | ((p[2]<<4)&0x300);
		int y = p[1] | ((p[2]<<2)&0x300);
		int s = p[2] & 0x0f;
		printf(" ir%dx=%-4d ir%dy=%-4d ir%ds=%-2d", i,x, i,y, i,s);
	}
}

void wiimote_parse_wmp(unsigned char *r)
{
	short sgZ = ( ((r[3]&0xfc)<<8) | (r[0]<<2) ) - 32768;
	short sgY = ( ((r[4]&0xfc)<<8) | (r[1]<<2) ) - 32768;
	short sgX = ( ((r[5]&0xfc)<<8) | (r[2]<<2) ) - 32768;
	int gZ = (r[3]&2) ? sgZ>>2 : (sgZ*2000/440)>>2;
	int gX = (r[3]&1) ? sgX>>2 : (sgX*2000/440)>>2;
	int gY = (r[4]&2) ? sgY>>2 : (sgY*2000/440)>>2;
	printf(" gX=%-6d gY=%-6d gZ=%-6d", -gX,gY,gZ);
}

void wiimote_parse_report(unsigned char *r, int len)
{
	switch ( r[0] )
	{
		case 0x20:
		case 0x22:
			break;
		case 0x31:
			wiimote_parse_accel(r+3);
			break;
		case 0x33:
			wiimote_parse_accel(r+3);
			wiimote_parse_ir12(r+6);
			break;
		case 0x35:
			wiimote_parse_accel(r+3);
			wiimote_parse_wmp(r+6);
			break;
		case 0x37:
			wiimote_parse_accel(r+3);
			wiimote_parse_ir10(r+6);
			wiimote_parse_wmp(r+16);
			break;
		default:
			dump("????", r, len);
			fatal("Unsupported report format");
	}
	printf("\n");
}

void sixaxis_ds3_parse_report(unsigned char *r, int len)
{
	if ( r[0]==0x01 && len>=49 ) {
		int aX = r[41]*256 + r[42] - 512;
		int aY = r[43]*256 + r[44] - 512;
		int aZ = r[45]*256 + r[46] - 512;
		int gZ = r[47]*256 + r[48] - 512;
		printf(" aX=%-4d aY=%-4d aZ=%-4d gZ=%-4d", aX,aY,aZ, gZ);
	}
	printf("\n");
}

void psmove_parse_report(unsigned char *r, int len, int latest)
{
	if ( r[0]==0x01 && len>=49 )
	{
		printf(" seq=%-2d", (r[4]&15)*2+(latest?1:0));
		int ai = latest ? 19 : 13;
		short aX = r[ai+0] + r[ai+1]*256 - 32768;
		short aY = r[ai+2] + r[ai+3]*256 - 32768;
		short aZ = r[ai+4] + r[ai+5]*256 - 32768;
		printf(" aX=%-6d aY=%-6d aZ=%-6d", aX,aY,aZ);
		int ri = latest ? 31 : 25;
		short gX = r[ri+0] + r[ri+1]*256 - 32768;
		short gY = r[ri+2] + r[ri+3]*256 - 32768;
		short gZ = r[ri+4] + r[ri+5]*256 - 32768;
		printf(" gX=%-6d gY=%-6d gZ=%-6d", gX,gY,gZ);
		short mX = (r[38]<<12) | (r[39]<<4);
		short mY = (r[40]<<8)  | (r[41]&0xf0);
		short mZ = (r[41]<<12) | (r[42]<<4);
		mY = - mY;  // Inconsistent sign conventions between acc+gyro and compass.
		printf(" mX=%-5d mY=%-5d mZ=%-5d", mX>>4,mY>>4,mZ>>4);
	}
	printf("\n");
}

void parse_report(struct motion_dev *dev, unsigned char *r, int len)
{
	struct timeval tv;
	if ( timestamp )
	{
		gettimeofday(&tv, NULL);
		printf("%10lu.%06ld ", tv.tv_sec, tv.tv_usec);
	}

	switch ( dev->type )
	{
		case WIIMOTE:
			printf("%d %s WIIMOTE", dev->index, myba2str(&dev->addr));
			wiimote_parse_report(r, len);
			break;
		case SIXAXIS:
			printf("%d %s SIXAXIS", dev->index, myba2str(&dev->addr));
			sixaxis_ds3_parse_report(r, len);
			break;
		case DS3:
			printf("%d %s DS3    ", dev->index, myba2str(&dev->addr));
			sixaxis_ds3_parse_report(r, len);
			break;
		case PSMOVE:  // Two samples per report on accel and gyro axes
			printf("%d %s PSMOVE ", dev->index, myba2str(&dev->addr));
			psmove_parse_report(r, len, 0);
			if ( timestamp ) printf("%10lu.%06ld ", tv.tv_sec, tv.tv_usec);
			printf("%d %s PSMOVE ", dev->index, myba2str(&dev->addr));
			psmove_parse_report(r, len, 1);
			break;
	}
	fflush(stdout);
}

#endif
