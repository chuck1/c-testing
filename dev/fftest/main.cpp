/*
* $id$
*
* Tests the force feedback driver
* Copyright 2001-2002 Johann Deneux <deneux@ifrance.com>
*/

/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
* 02110-1301 USA.
*
* You can contact the author by email at this address:
* Johann Deneux <deneux@ifrance.com>
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/input.h>

#include <map>

std::map<unsigned int,char const *> map_ev;
std::map<unsigned int,char const *> map_rel;
std::map<unsigned int,char const *> map_abs;
std::map<unsigned int,char const *> map_key;
std::map<unsigned int,char const *> map_ff;

void init()
{
	map_rel[REL_X]      = "REL_X      ";
	map_rel[REL_Y]      = "REL_Y      ";
	map_rel[REL_Z]      = "REL_Z      ";
	map_rel[REL_RX]     = "REL_RX     ";
	map_rel[REL_RY]     = "REL_RY     ";
	map_rel[REL_RZ]     = "REL_RZ     ";
	map_rel[REL_HWHEEL] = "REL_HWHEEL ";
	map_rel[REL_DIAL]   = "REL_DIAL   ";
	map_rel[REL_WHEEL]  = "REL_WHEEL  ";
	map_rel[REL_MISC]   = "REL_MISC   ";
	map_rel[REL_MAX]    = "REL_MAX    ";


	map_key[BTN_GAMEPAD] = "BTN_GAMEPAD";
	map_key[BTN_A      ] = "BTN_A";
	map_key[BTN_B      ] = "BTN_B";
	map_key[BTN_C      ] = "BTN_C";
	map_key[BTN_X      ] = "BTN_X";
	map_key[BTN_Y      ] = "BTN_Y";
	map_key[BTN_Z      ] = "BTN_Z";
	map_key[BTN_TL     ] = "BTN_TL";
	map_key[BTN_TR     ] = "BTN_TR";
	map_key[BTN_TL2    ] = "BTN_TL2";
	map_key[BTN_TR2    ] = "BTN_TR2";
	map_key[BTN_SELECT ] = "BTN_SELECT";
	map_key[BTN_START  ] = "BTN_START";
	map_key[BTN_MODE   ] = "BTN_MODE";
	map_key[BTN_THUMBL ] = "BTN_THUMBL";
	map_key[BTN_THUMBR ] = "BTN_THUMBR";
	
	//map_ev[EV_SYN] = "EV_SYN";
	map_ev[EV_KEY] = "EV_KEY";
	map_ev[EV_REL] = "EV_REL";
	map_ev[EV_ABS] = "EV_ABS";
	map_ev[EV_MSC] = "EV_MSC";
	map_ev[EV_LED] = "EV_LED";
	map_ev[EV_SND] = "EV_SND";
	map_ev[EV_REP] = "EV_REP";
	map_ev[EV_FF ] = "EV_FF";
	map_ev[EV_PWR] = "EV_PWR";
	map_ev[EV_FF_STATUS] = "EV_FF_STATUS";
	

	map_ff[ABS_X      ] = "ABS_X";
	map_ff[ABS_Y      ] = "ABS_Y";
	map_ff[ABS_WHEEL  ] = "ABS_WHEEL";
	
	map_ff[FF_RUMBLE  ] = "FF_RUMBLE";
	map_ff[FF_PERIODIC] = "FF_PERIODIC";
	map_ff[FF_CONSTANT] = "FF_CONSTANT";
	map_ff[FF_SPRING  ] = "FF_SPRING";
	map_ff[FF_FRICTION] = "FF_FRICTION";
	map_ff[FF_DAMPER  ] = "FF_DAMPER";
	map_ff[FF_INERTIA ] = "FF_INERTIA"; 
	map_ff[FF_RAMP    ] = "FF_RAMP";
	map_ff[FF_SQUARE  ] = "FF_SQUARE";
	map_ff[FF_TRIANGLE] = "FF_TRIANGLE";
	map_ff[FF_SINE]     = "FF_SINE";
	map_ff[FF_SAW_UP]   = "FF_SAW_UP";
	map_ff[FF_SAW_DOWN] = "FF_SAW_DOWN";
	map_ff[FF_CUSTOM]   = "FF_CUSTOM";

	map_ff[FF_GAIN]       = "FF_GAIN";
	map_ff[FF_AUTOCENTER] = "FF_AUTOCENTER";

/*
520 #define ABS_X                   0x00
521 #define ABS_Y                   0x01
522 #define ABS_Z                   0x02
523 #define ABS_RX                  0x03
524 #define ABS_RY                  0x04
525 #define ABS_RZ                  0x05
526 #define ABS_THROTTLE            0x06
527 #define ABS_RUDDER              0x07
528 #define ABS_WHEEL               0x08
529 #define ABS_GAS                 0x09
530 #define ABS_BRAKE               0x0a
531 #define ABS_HAT0X               0x10
532 #define ABS_HAT0Y               0x11
533 #define ABS_HAT1X               0x12
534 #define ABS_HAT1Y               0x13
535 #define ABS_HAT2X               0x14
536 #define ABS_HAT2Y               0x15
537 #define ABS_HAT3X               0x16
538 #define ABS_HAT3Y               0x17
539 #define ABS_PRESSURE            0x18
540 #define ABS_DISTANCE            0x19
541 #define ABS_TILT_X              0x1a
542 #define ABS_TILT_Y              0x1b
543 #define ABS_TOOL_WIDTH          0x1c
544 #define ABS_VOLUME              0x20
545 #define ABS_MISC                0x28
546 #define ABS_MAX                 0x3f
*/


}

#define N_EFFECTS 6

bool _test_bit( int bit, unsigned char * array)
{
	return ( ( array[ bit/8 ] >> ( bit % 8 )) & 1 );
}

bool _test_bit2( int bit, unsigned int integer )
{
	return ( (integer >> bit) & 1 );
}


void print_bits( void *v, int c )
{
	unsigned char *ch = (unsigned char *)v;

	for( int byt = 0; byt < c; ++byt )
	{
		for( int bit = 0; bit < 8; ++bit )
		{
			printf("%i ", ( ( ch[byt] >> bit )  & 1) );
		}
	}
	printf("\n");
}





void query( int fd, unsigned int start, unsigned int end, std::map<unsigned int,char const *> map )
{	
	unsigned int size = end / 8;
	
	unsigned char query[size];
	
	//printf("%i %X\n",(int)size,(int)end);

	// Query force feedback
	if (ioctl( fd, EVIOCGBIT( start, size ), query ) < 0)
	{
		perror("Ioctl query");
		exit(1);
	}

	auto it = map_ev.find(start);
	if(it != map_ev.end())
	{
		printf("%s\n",(*it).second);
	}
	else
	{
		printf("%X:\n",start);
	}

	for(unsigned int i = 0; i < end; ++i )
	{
		if( _test_bit(i,query))
		{
			auto it = map.find(i);
			if(it != map.end())
			{
				printf("\t%s\n",(*it).second);
			}
			else
			{
				printf("\t%X\n",i);
			}
		}
	}



}
void query_num_effects( int fd, int *num_effects )
{

	if (ioctl(fd, EVIOCGEFFECTS, num_effects) < 0)
	{
		perror("Ioctl number of effects");
	}

	printf("Number of simultaneous effects: %i\n", *num_effects);
}

void query_absinfo( int fd, unsigned int abs )
{
	input_absinfo ai;
	
	if (ioctl(fd, EVIOCGABS(abs), &ai ) < 0)
	{
		perror("ioctl");
		return;
	}


	printf("value %i\n",ai.value);
	printf("minimum %i\n",ai.minimum);
	printf("maximum %i\n",ai.maximum);
	printf("fuzz %i\n",ai.fuzz);
	printf("flat %i\n",ai.flat);
	printf("resolution %i\n",ai.resolution);
	
}
void query_features( int fd, unsigned long *features )
{
	init();

	query(fd, 0,      EV_CNT,  map_ev);
	query(fd, EV_KEY, KEY_CNT, map_key);
	query(fd, EV_REL, REL_CNT, map_rel);
	query(fd, EV_ABS, ABS_CNT, map_abs);
	query(fd, EV_FF , FF_CNT , map_ff);


	//query_absinfo(fd, 0);
	
}



char effect_names[][32] = {
	"Sine vibration",
	"Constant Force",
	"Spring Condition",
	"Damping Condition",
	"Strong Rumble",
	"Weak Rumble"
};

int main(int argc, char** argv)
{
	struct ff_effect effects[N_EFFECTS];
	struct input_event play, stop;
	int fd;
	char device_file_name[64];
	unsigned long features[4];
	int n_effects;        /* Number of effects the device can play at the same time */
	int i;

	printf("Force feedback test program.\n");
	printf("HOLD FIRMLY YOUR WHEEL OR JOYSTICK TO PREVENT DAMAGES\n\n");

	strncpy(device_file_name, "/dev/input/event0", 64);

	for (i=1; i<argc; ++i)
	{
		if (strncmp(argv[i], "--help", 64) == 0)
		{
			printf("Usage: %s /dev/input/eventXX\n", argv[0]);
			printf("Tests the force feedback driver\n");
			exit(1);
		}
		else
		{
			strncpy(device_file_name, argv[i], 64);
		}
	}

	/* Open device */
	fd = open(device_file_name, O_RDWR);
	if (fd == -1)
	{
		perror("Open device file");
		exit(1);
	}

	printf("Device %s opened\n", device_file_name);

	// Query features
	query_features( fd, features );
	query_num_effects( fd, &n_effects );


	/* download a periodic sinusoidal effect */
	effects[0].type = FF_PERIODIC;
	effects[0].id = -1;
	effects[0].u.periodic.waveform = FF_SINE;
	effects[0].u.periodic.period = 0.1*0x100;        /* 0.1 second */
	effects[0].u.periodic.magnitude = 0x4000;        /* 0.5 * Maximum magnitude */
	effects[0].u.periodic.offset = 0;
	effects[0].u.periodic.phase = 0;
	effects[0].direction = 0x4000;        /* Along X axis */
	effects[0].u.periodic.envelope.attack_length = 0x100;
	effects[0].u.periodic.envelope.attack_level = 0;
	effects[0].u.periodic.envelope.fade_length = 0x100;
	effects[0].u.periodic.envelope.fade_level = 0;
	effects[0].trigger.button = 0;
	effects[0].trigger.interval = 0;
	effects[0].replay.length = 20000; /* 20 seconds */
	effects[0].replay.delay = 0;

	if ( ioctl( fd, EVIOCSFF, &effects[0] ) < 0 )
	{
		perror("Upload effects[0]");
	}

	/* download a constant effect */
	effects[1].type = FF_CONSTANT;
	effects[1].id = -1;
	effects[1].u.constant.level = 0x2000;        /* Strength : 25 % */
	effects[1].direction = 0x6000;        /* 135 degrees */
	effects[1].u.constant.envelope.attack_length = 0x100;
	effects[1].u.constant.envelope.attack_level = 0;
	effects[1].u.constant.envelope.fade_length = 0x100;
	effects[1].u.constant.envelope.fade_level = 0;
	effects[1].trigger.button = 0;
	effects[1].trigger.interval = 0;
	effects[1].replay.length = 20000; /* 20 seconds */
	effects[1].replay.delay = 0;

	if (ioctl(fd, EVIOCSFF, &effects[1]) < 0)
	{
		perror("Upload effects[1]");
	}

	/* download an condition spring effect */
	effects[2].type = FF_SPRING;
	effects[2].id = -1;
	effects[2].u.condition[0].right_saturation = 0x7fff;
	effects[2].u.condition[0].left_saturation = 0x7fff;
	effects[2].u.condition[0].right_coeff = 0x2000;
	effects[2].u.condition[0].left_coeff = 0x2000;
	effects[2].u.condition[0].deadband = 0x0;
	effects[2].u.condition[0].center = 0x0;
	effects[2].u.condition[1] = effects[2].u.condition[0];
	effects[2].trigger.button = 0;
	effects[2].trigger.interval = 0;
	effects[2].replay.length = 20000; /* 20 seconds */
	effects[2].replay.delay = 0;

	if (ioctl(fd, EVIOCSFF, &effects[2]) < 0)
	{
		perror("Upload effects[2]");
	}

	/* download an condition damper effect */
	effects[3].type = FF_DAMPER;
	effects[3].id = -1;
	effects[3].u.condition[0].right_saturation = 0x7fff;
	effects[3].u.condition[0].left_saturation = 0x7fff;
	effects[3].u.condition[0].right_coeff = 0x2000;
	effects[3].u.condition[0].left_coeff = 0x2000;
	effects[3].u.condition[0].deadband = 0x0;
	effects[3].u.condition[0].center = 0x0;
	effects[3].u.condition[1] = effects[3].u.condition[0];
	effects[3].trigger.button = 0;
	effects[3].trigger.interval = 0;
	effects[3].replay.length = 20000; /* 20 seconds */
	effects[3].replay.delay = 0;

	if (ioctl(fd, EVIOCSFF, &effects[3]) < 0)
	{
		perror("Upload effects[3]");
	}

	/* a strong rumbling effect */
	effects[4].type = FF_RUMBLE;
	effects[4].id = -1;
	effects[4].u.rumble.strong_magnitude = 0x8000;
	effects[4].u.rumble.weak_magnitude = 0;
	effects[4].replay.length = 5000;
	effects[4].replay.delay = 1000;

	if (ioctl(fd, EVIOCSFF, &effects[4]) < 0)
	{
		perror("Upload effects[4]");
	}

	/* a weak rumbling effect */
	effects[5].type = FF_RUMBLE;
	effects[5].id = 1;
	effects[5].u.rumble.strong_magnitude = 0;
	effects[5].u.rumble.weak_magnitude = 0xc000;
	effects[5].replay.length = 5000;
	effects[5].replay.delay = 0;

	if (ioctl(fd, EVIOCSFF, &effects[5]) < 0)
	{
		perror("Upload effects[5]");
	}


	/* Ask user what effects to play */
	do
	{
		printf("Enter effect number, -1 to exit\n");
		scanf("%d", &i);
		if (i >= 0 && i < N_EFFECTS) {
			play.type = EV_FF;
			play.code = effects[i].id;
			play.value = 1;

			if (write(fd, (const void*) &play, sizeof(play)) == -1) {
				perror("Play effect");
				exit(1);
			}

			printf("Now Playing: %s\n", effect_names[i]);
		}
		else if (i == -2) {
			/* Crash test */
			int i = *((int *)0);
			printf("Crash test: %d\n", i);
		}
		else {
			printf("No such effect\n");
		}
	} while (i>=0);

	/* Stop the effects */
	for (i=0; i<N_EFFECTS; ++i)
	{
		stop.type = EV_FF;
		stop.code = effects[i].id;
		stop.value = 0;

		if (write(fd, (const void*) &stop, sizeof(stop)) == -1) {
			perror("Stop effect");
			exit(1);
		}
	}


	exit(0);
}


