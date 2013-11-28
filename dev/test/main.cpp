#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <linux/input.h>
#include <linux/joystick.h>



int main( int argc, char const ** argv )
{
	if ( argc != 2 )
	{
		printf( "usage: %s <dev file>\n", argv[0] );
		return 0;
	}


	//input_event ie;
	js_event ie;

	int fd = open( argv[1], O_RDONLY );

	if ( fd < 0 )
	{
		printf("%s\n", strerror(errno) );
		return 0;
	}

	char buttonc;
	char axesc;
	char name[128];

	unsigned char buf[8];

	ioctl( fd, JSIOCGAXES, &axesc );
	ioctl( fd, JSIOCGBUTTONS, &buttonc );
	ioctl( fd, JSIOCGNAME(128), name );

	int axes[ (int)axesc ];
	int button[ (int)buttonc ];
	
	for ( int a = 0; a < buttonc; a++ )
	{
		button[a] = 0;
	}

	printf( "buttonc=%i axesc=%i name=%s\n", buttonc, axesc, name );

	int bytes;

	unsigned int time;
	unsigned int value;
	unsigned int type;
	unsigned int number;





	while(1)
	{


		for ( int i = 0; i < bytes; i++ )
		{
			//printf("%02X ", buf[i] );
		}



		
		/*
		   printf("%12i ", time );
		   printf("%12i ", value );
		   printf("%12i ", type );
		   printf("%12i ", number );
		 */
		//printf("\n");


			bytes = read( fd, buf, 8 );

			time = buf[0] + ( buf[1] << 8 ) + ( buf[2] << 16 ) + ( buf[3] << 24 );
			value = buf[4] + ( buf[5] << 8 );
			type = buf[6];	
			number = buf[7];

			

			if ( type == 1 )
			{
				if ( ( number < 0 ) || ( number >= buttonc ) )
				{
					printf( "unknown button number\n" );
					return 0;
				}
				else
				{
					button[ number ] = value;
				}
			}
			else if ( type == 2 )
			{
				axes[ number ] = value;
			}
			else
			{
				printf( "unknown type %i\n", type );
				//return 0;
			}

		for ( int a = 0; a < buttonc; a++ )
		{
			printf( "%1i ", button[a] );
		}
		for ( int a = 0; a < axesc; a++ )
		{
			printf( "%8i ", axes[a] );
		}
		printf( "\n" );
	}
}





