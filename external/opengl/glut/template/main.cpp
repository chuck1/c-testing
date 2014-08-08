#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "glut.hpp"

#define VIEWING_DISTANCE_MIN  3.0
#define TEXTURE_ID_CUBE 1



int g_cam_mode = 0;



typedef int BOOL;
#define TRUE 1
#define FALSE 0

static BOOL g_bLightingEnabled = TRUE;
static BOOL g_bFillPolygons = TRUE;
static BOOL g_bButton1Down = FALSE;

static GLfloat g_nearPlane = 1E5;
static GLfloat g_farPlane =  1E9;

static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
#ifdef _WIN32
#else
#endif





void reshape(GLint width, GLint height)
{
	g_Width = width;
	g_Height = height;

	glViewport(0, 0, g_Width, g_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// Create texture for cube; load marble texture from file and bind it
}

int g_mx = 0;
int g_my = 0;

void MouseButton(int button, int state, int x, int y)
{
	// Respond to mouse button presses.
	// If button1 pressed, mark this state so we know in motion function.

	//printf("button\n");

	if (button == GLUT_LEFT_BUTTON)
	{
		g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
	
		if(state == GLUT_DOWN) {
			g_mx = x;
			g_my = y;
		}
	} else if(button == 3) {
		g_view_dist /= 1.2;
	} else if(button == 4) {
		g_view_dist *= 1.2;
	}

}


void MouseMotion(int x, int y)
{
	// If button1 pressed, zoom in/out if mouse is moved up/down.

	if (g_bButton1Down)
	{
		//g_fViewDistance = (y - g_yClick) / 3.0;
		//if (g_fViewDistance < VIEWING_DISTANCE_MIN)
		//	g_fViewDistance = VIEWING_DISTANCE_MIN;
		//glutPostRedisplay();
		
		int dx = x - g_mx;
		int dy = y - g_my;
		
		g_view_yaw += (float)dx * 3.14 / 300.0;
		g_view_pitch += (float)dy * 3.14 / 300.0;
		
		g_mx = x;
		g_my = y;

		//printf("%i %i\n", g_mx, x);
	}
}


void SelectFromMenu(int idCommand)
{
	switch (idCommand)
	{
		case MENU_LIGHTING:
			g_bLightingEnabled = !g_bLightingEnabled;
			if (g_bLightingEnabled)
				glEnable(GL_LIGHTING);
			else
				glDisable(GL_LIGHTING);
			break;
		case MENU_POLYMODE:
			g_bFillPolygons = !g_bFillPolygons;
			glPolygonMode (GL_FRONT_AND_BACK, g_bFillPolygons ? GL_FILL : GL_LINE);
			break;      
		case MENU_CAMERA:
			g_cam_mode++;
			if (g_cam_mode == 2) g_cam_mode = 0;
		case MENU_EXIT:
			exit (0);
			break;
	}

	// Almost any menu selection requires a redraw
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27: // ESCAPE
			exit (0);
			break;
		case 'l':
			SelectFromMenu(MENU_LIGHTING);
			break;

		case 'p':
			SelectFromMenu(MENU_POLYMODE);
			break;
		case 'c':
			SelectFromMenu(MENU_CAMERA);

	}
}

int BuildPopupMenu (void) {
	int menu;

	menu = glutCreateMenu (SelectFromMenu);
	glutAddMenuEntry ("Toggle lighting\tl", MENU_LIGHTING);
	glutAddMenuEntry ("Toggle polygon fill\tp", MENU_POLYMODE);
	glutAddMenuEntry ("Cycle camera mode\tp", MENU_CAMERA);
	glutAddMenuEntry ("Exit demo\tEsc", MENU_EXIT);

	return menu;
}

void	display();
void	animate();



int main(int argc, char** argv) {

	// GLUT Window Initialization:
	glutInit (&argc, argv);
	glutInitWindowSize (g_Width, g_Height);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("CS248 GLUT example");

	// Initialize OpenGL graphics state
	InitGraphics();

	// Register callbacks:
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(animate);

	// Create our popup menu
	BuildPopupMenu ();
	glutAttachMenu (GLUT_RIGHT_BUTTON);

	// Get the initial time, for use by animation
	gettimeofday (&last_idle_time, NULL);

	// Turn the flow of control over to GLUT
	glutMainLoop();

	return 0;
}




