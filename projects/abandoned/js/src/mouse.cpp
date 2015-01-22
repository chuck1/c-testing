#include <linux/input.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

#include <SIG/signal.h>

#include <JSL/Event.h>

bool _test_bit( int bit, unsigned char * array)
{
        return ( ( array[ bit/8 ] >> ( bit % 8 )) & 1 );
}

bool _test_bit2( int bit, unsigned int integer )
{
        return ( (integer >> bit) & 1 );
}



JSL::Event::Event():
	flag_(0)
{
	signals_ = new SIG::signal<unsigned int>[2];

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


	map_abs_str_[ABS_X]      = "ABS_X";
	map_abs_str_[ABS_Y]      = "ABS_Y";
	map_abs_str_[ABS_Z]      = "ABS_Z";
	map_abs_str_[ABS_RX]     = "ABS_RX";
	map_abs_str_[ABS_RY]     = "ABS_RY";
	map_abs_str_[ABS_RZ]     = "ABS_RZ";



	map_key[BTN_GAMEPAD] = "BTN_GAMEPAD";
	map_key[BTN_A] = "BTN_A";
	map_key[BTN_B] = "BTN_B";
	map_key[BTN_C] = "BTN_C";
	map_key[BTN_X] = "BTN_X";
	map_key[BTN_Y] = "BTN_Y";
	map_key[BTN_Z] = "BTN_Z";
	map_key[BTN_TL] = "BTN_TL";
	map_key[BTN_TR] = "BTN_TR";
	map_key[BTN_TL2] = "BTN_TL2";
	map_key[BTN_TR2] = "BTN_TR2";
	map_key[BTN_SELECT] = "BTN_SELECT";
	map_key[BTN_START] = "BTN_START";
	map_key[BTN_MODE] = "BTN_MODE";
	map_key[BTN_THUMBL] = "BTN_THUMBL";
	map_key[BTN_THUMBR] = "BTN_THUMBR";

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
}
void	JSL::Event::Init()
{
	query_abs();
	
	
}
void	JSL::Event::query_abs()
{       
	unsigned int size = ABS_CNT / 8;
	
	__u8 query[size];
	
	//printf("%i %X\n",(int)size,(int)end);

	// Query force feedback
	if (ioctl(fd_, EVIOCGBIT( EV_ABS, size ), query ) < 0)
	{
		perror("Ioctl query");
		exit(1);
	}

	
	for(__u32 i = 0; i < ABS_CNT; ++i )
	{
		if( _test_bit(i,query))
		{
/*			auto it = map.find(i);
			if(it != map.end())
			{
				printf("\t%s\n",(*it).second);
			}
			else
			{
				printf("\t%X\n",i);
			}*/

			query_absinfo(i);
		}
	}
}
void	JSL::Event::query(__u32 start, __u32 end, std::map<__u32,char const *> map )
{       
	unsigned int size = end / 8;
	
	__u8 query[size];

	//printf("%i %X\n",(int)size,(int)end);

	// Query force feedback
	if (ioctl( fd_, EVIOCGBIT( start, size ), query ) < 0)
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
void	JSL::Event::query_absinfo(__u32 abs)
{	
	input_absinfo ai;
	
	if (ioctl(fd_, EVIOCGABS(abs), &ai ) < 0)
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

	map_abs_[abs].min_ = (float)ai.minimum;
	map_abs_[abs].max_ = (float)ai.maximum;
	map_abs_[abs].mean_ = ( (float)ai.maximum + (float)ai.minimum ) / 2.0f;
	map_abs_[abs].range_ = ( (float)ai.maximum - (float)ai.minimum );

	
}
void JSL::Event::Set(unsigned int f)
{
	flag_ |= f;
}
void *wrapper(void* dev)
{
	((JSL::Event*)dev)->Read();

	return NULL;
}
void JSL::Event::Launch()
{
	//printf("%s\n",__FUNCTION__);

	int rc = pthread_create(&thread_, NULL, wrapper, this);
	if( rc > 0 )
	{
		printf("pthread_create: %i\n",rc);
		exit(1);
	}
}
void JSL::Event::Join()
{
	pthread_join(thread_, NULL);
}
void JSL::Event::Read()
{
	//printf("%s\n",__FUNCTION__);

	input_event ie;

	char message[64];

	char str_time[32];
	char str_type[32];
	char str_code[32];
	char str_value[32];


	while(1)
	{
		int len = read(fd_, &ie, sizeof(input_event));

		//printf("read %i\n",len);

		if( len < 0 )
		{
			perror("read");
			exit(1);
		}
		if(len != sizeof(input_event))
		{
			printf("unknown error:read %i\n",(int)len);
			exit(1);
		}


		sprintf(str_time, "%16i", (int)ie.time.tv_sec);
		sprintf(str_type, "%16s", map_ev[ie.type]);
		sprintf(str_value, "%16i", (int)ie.value);



		auto it_key = map_key.find(ie.code);
		auto it_rel = map_rel.find(ie.code);
		auto it_abs_str = map_abs_str_.find(ie.code);
		auto it_msc = map_msc.find(ie.code);
		//auto it_ff  = map_ff.find(ie.code);


		switch(ie.type)
		{
			case EV_SYN:
				sprintf(str_code, "%16s", "SYN");
				break;
			case EV_KEY:
				// string
				if(it_key == map_key.end())
				{
					sprintf(str_code, "%16X", ie.code);
				}
				else
				{
					sprintf(str_code, "%16s", map_key[ie.code]);
				}

				// signal
				sig_key_(ie.code,ie.value);
				map_sig_key_[ie.code](ie.value);
				break;
			case EV_REL:
				// string
				if(it_rel == map_rel.end())
				{
					sprintf(str_code, "%16X", ie.code);
				}
				else
				{
					sprintf(str_code, "%16s", map_rel[ie.code]);
				}

				// signal
				sig_rel_(ie.code, ie.value);
				map_sig_rel_[ie.code](ie.value);
				break;
			case EV_ABS:
				if(it_abs_str == map_abs_str_.end())
				{
					sprintf(str_code, "%16X", ie.code);
				}
				else
				{
					sprintf(str_code, "%16s", (*it_abs_str).second);
				}

				// signal
				sig_abs_(ie.code, map_abs_[ie.code](ie.value));
				map_sig_abs_[ie.code](map_abs_[ie.code](ie.value));
				break;
			case EV_MSC:
				if(it_msc == map_msc.end())
				{
					sprintf(str_code, "%16X", ie.code);
				}
				else
				{
					sprintf(str_code, "%16s", map_msc[ie.code]);
				}
				break;
			default:
				sprintf(str_code, "%16X",ie.code);
				break;
		}



		if( ( flag_ & JSL::Event::flag::PRINT ) > 0 )
		{
			strncpy(message,     str_time, 16);
			strncpy(message +16, str_type, 16);
			strncpy(message +32, str_code, 16);
			strncpy(message +48, str_value,16);


			message[64] = '\0';

			if( ( ie.type == EV_ABS ) || ( ie.type == EV_KEY ) || ( ie.type == EV_REL ) )
			{
				printf("%s\n",message);
			}
		}
	}
}


