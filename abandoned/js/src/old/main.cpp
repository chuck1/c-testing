#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>

#include <stdio.h>
//#include <windows.h>	   // Standard header for MS Windows applications
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header

#include <joystick/sixaxis.hpp>

#define KEY_ESCAPE 27
#define BUF_LEN 128

int fd;

struct glutWindow
{
	int width;
	int height;
	const char* title;
	float fov;
	float z_near;
	float z_far;
} win;

template <typename... Args> void pfatal(Args... args) { perror(args...); exit(1); }
template <typename... Args> void fatal(Args... args)  { printf(args...); exit(1); }

template <typename T> struct vec
{
	vec(T _x,T _y,T _z)
	{
		x=_x;
		y=_y;
		z=_z;
	}
	vec()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	template <typename U> vec( vec<U> const & v )
	{
		x = (T)v.x;
		y = (T)v.y;
		z = (T)v.z;
	}
	vec<T> operator+( vec<T> const & v )
	{
		vec<T> ret;
		ret.x = x+v.x;
		ret.y = y+v.y;
		ret.z = z+v.z;
		
		return ret;
	}
	vec<T> operator-( vec<T> const & v )
	{
		vec<T> ret;
		ret.x = x-v.x;
		ret.y = y-v.y;
		ret.z = z-v.z;
		
		return ret;
	}
	vec<T> operator*( T const & t )
	{
		vec<T> ret;
		ret.x = x*t;
		ret.y = y*t;
		ret.z = z*t;
		
		return ret;
	}
	
	template <typename U> vec<T> operator=( vec<U> const & v )
	{
		x = (T)v.x;
		y = (T)v.y;
		z = (T)v.z;
		
		return *this;
	}
	union
	{
		struct
		{
			T x,y,z;
		};
		T v[3];
	};
};

struct ss_state
{
	ss_state()
	{
	};
	ss_state( ss_event buf, ss_state prev )
	{
		struct timeval tv;
		if ( gettimeofday(&tv, NULL) ) pfatal("gettimeofday");

		time = tv.tv_sec + tv.tv_usec*1e-6;
		a.x = buf.motion.accX;//[41]<<8 | buf[42];
		a.y = buf.motion.accX;//[43]<<8 | buf[44];
		a.z = buf.motion.accX;//[45]<<8 | buf[46];

		if ( prev.time == 0 )
		{
			prev.time = time;
		}
		
		// process

		float dt = time - prev.time;

		// Time constant for highpass filter on acceleration
		float rc_dd = 2.0;
		float alpha_dd = rc_dd / ( rc_dd + dt );

		vec<float> deltaa( a - prev.a );

		dd = ( prev.dd + deltaa ) * 0.01 * alpha_dd;

		// Time constant for highpass filter on speed
		float rc_d = 2.0;
		float alpha_d = rc_d / ( rc_d + dt );

		d = ( prev.d + ( dd * dt ) ) * alpha_d;

		// Time constant for highpass filter on position
		float rc = 1.0;
		float alpha = rc / (rc+dt);

		x = ( prev.x + ( d * dt ) ) * alpha;

	}

	float time;

	vec<uint16_t>	a;  // Raw accelerometer data
	vec<float>	dd; // Acceleration
	vec<float>	d;  // Speed
	vec<float>	x;  // Position
} snew, sprev;


void ss_read()
{
	if( fd )
	{
		
		ss_event buf;

		int nr = read( fd, &buf, sizeof(ss_event) );

		if ( nr < 0 ) pfatal("read(stdin)");
		if ( nr != 49 ) fatal("Unsupported report length %d. Wrong hidraw device or kernel<2.6.26 ?\n", nr);

		printf("successful read\n");
		
		ss_state s( buf, sprev );


		sprev = snew;
		snew = s;
	}
}


void draw_cube()
{
	GLfloat clr[][3] = {{ 0.0f, 1.0f, 0.0f }};

	glBegin(GL_QUADS);					

	glColor3fv( clr[0] );
	glVertex3f( 0.5f, 0.5f, 0.5f);		
	glVertex3f( 0.5f,-0.5f, 0.5f);		
	glVertex3f(-0.5f,-0.5f, 0.5f);		
	glVertex3f(-0.5f, 0.5f, 0.5f);		

	glVertex3f( 0.5f, 0.5f,-0.5f);		
	glVertex3f( 0.5f,-0.5f,-0.5f);		
	glVertex3f(-0.5f,-0.5f,-0.5f);		
	glVertex3f(-0.5f, 0.5f,-0.5f);		

	glVertex3f( 0.5f, 0.5f, 0.5f);		
	glVertex3f( 0.5f, 0.5f,-0.5f);		
	glVertex3f(-0.5f, 0.5f,-0.5f);		
	glVertex3f(-0.5f, 0.5f, 0.5f);		

	glVertex3f( 0.5f,-0.5f, 0.5f);		
	glVertex3f( 0.5f,-0.5f,-0.5f);		
	glVertex3f(-0.5f,-0.5f,-0.5f);		
	glVertex3f(-0.5f,-0.5f, 0.5f);		

	glVertex3f( 0.5f, 0.5f, 0.5f);		
	glVertex3f( 0.5f,-0.5f, 0.5f);		
	glVertex3f( 0.5f,-0.5f,-0.5f);		
	glVertex3f( 0.5f, 0.5f,-0.5f);		

	glVertex3f(-0.5f, 0.5f, 0.5f);		
	glVertex3f(-0.5f,-0.5f, 0.5f);		
	glVertex3f(-0.5f,-0.5f,-0.5f);		
	glVertex3f(-0.5f, 0.5f,-0.5f);		

	glEnd();				

}

void display() 
{
	ss_read();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer

	glLoadIdentity();
	
	{
		glPushMatrix();
		
		vec<float> x = snew.x + vec<float>( 0.0, 0.0, -3.0 );
		
		glTranslatef( x.x, x.y, x.z );
		
		draw_cube();
		
		glPopMatrix();
	}

	glutSwapBuffers();
}


void initialize () 
{
	glMatrixMode(GL_PROJECTION);												// select projection matrix
	glViewport(0, 0, win.width, win.height);									// set the viewport
	glMatrixMode(GL_PROJECTION);												// set matrix mode
	glLoadIdentity();															// reset projection matrix
	GLfloat aspect = (GLfloat) win.width / win.height;
	gluPerspective( win.fov, aspect, win.z_near, win.z_far );		// set up a perspective projection matrix
	glMatrixMode(GL_MODELVIEW);													// specify which matrix is the current matrix
	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f );														// specify the clear value for the depth buffer
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// specify implementation-specific hints
	glClearColor(0.0, 0.0, 0.0, 1.0);											// specify clear values for the color buffers								
}


void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
	switch ( key ) 
	{
		case KEY_ESCAPE:        
			exit ( 0 );   
			break;      
		default:      
			break;
	}
}
void keyboardup ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
	switch ( key ) 
	{
		case KEY_ESCAPE:
			break;      
		default:      
			break;
	}
}



int main(int argc, char **argv) 
{
	printf("Usage %s < /dev/hidrawX\n", argv[0]);

	if( argc > 1 )
	{
		if ( ! ( fd = open( argv[1], O_RDONLY | O_NONBLOCK ) ) )
		{
			printf("failed to open %s\n",argv[1]);
		}	
	}



	//set window values
	win.width 	= 640;
	win.height 	= 480;
	win.title 	= "GLUT Sixaxis";
	win.fov		= 45;
	win.z_near 	= 1.0f;
	win.z_far 	= 500.0f;

	// initialize and run program
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( win.width, win.height );
	glutCreateWindow( win.title );					// create Window
	glutDisplayFunc( display );					// register Display Function
	glutIdleFunc( display );					// register Idle Function
	glutKeyboardFunc( keyboard );					// register Keyboard Handler
	glutKeyboardUpFunc( keyboardup );

	//glutIgnoreKeyRepeat( 1 );
	glutSetKeyRepeat( GLUT_KEY_REPEAT_OFF );

	initialize();
	glutMainLoop();							// run GLUT mainloop
	return 0;
}










/*
   void draw(struct state *s)
   {
   int xc = ww/2, yc = wh/2;
   double ppm = 1000 / 0.3;
// Position
int x = xc + s->x*ppm;
int y = yc - s->z*ppm;
int r = xc * 0.05 / (0.5+s->y);
XDrawLine(display, window, gc, xc,yc, x,y);
XDrawArc(display, window, gc, x-r,y-r, r*2,r*2, 0,360*64);
// Speed
int x1 = x + s->dx*1000;
int y1 = y - s->dz*1000;
XDrawLine(display, window, gc, x,y, x1,y1);
// Acceleration
int x2 = x1 + s->ddx*100;
int y2 = y1 - s->ddz*100;
XDrawLine(display, window, gc, x1,y1, x2,y2);
// Orientation
int a0 = 512;  // Note: Not all controllers are centered at 512 ?
double roll = - atan2(s->ax-a0, s->az-a0);
double azx = hypot(s->ax-a0, s->az-a0);
double pitch = atan2(s->ay-a0, azx);
int hw = 100, hh = 200;
double cr = cos(roll);
double sr = sin(roll);
int xh = xc + pitch*hh/(M_PI/2) * sr;
int yh = yc - pitch*hh/(M_PI/2) * cr;;
// Lines at 0 degrees
XDrawLine(display,window,gc, xh-cr*hw,yh-sr*hw,xh-cr*hw/2,yh-sr*hw/2);
XDrawLine(display,window,gc, xh+cr*hw,yh+sr*hw,xh+cr*hw/2,yh+sr*hw/2);
// Line at -90 degrees
XDrawLine(display,window,gc,
xh+sr*hh-cr*hw, yh-cr*hh-sr*hw,
xh+sr*hh+cr*hw, yh-cr*hh+sr*hw);
// Short line at +90 degrees
XDrawLine(display,window,gc,
xh-sr*hh-cr*hw/2, yh+cr*hh-sr*hw/2,
xh-sr*hh+cr*hw/2, yh+cr*hh+sr*hw/2);
}
*/

