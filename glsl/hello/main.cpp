
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

//#include <main.h>
#include <draw.h>
#include <object.h>

#include <math/vec3.h>
#include <math/mat44.h>

#define VIEWING_DISTANCE_MIN  3.0
#define TEXTURE_ID_CUBE 1

enum {
	MENU_LIGHTING = 1,
	MENU_POLYMODE,
	MENU_TEXTURING,
	MENU_SHADER,
	MENU_EXIT
};

typedef int BOOL;
#define TRUE 1
#define FALSE 0

static BOOL g_bLightingEnabled = TRUE;
static BOOL g_bFillPolygons = TRUE;
static BOOL g_bTexture = FALSE;
static BOOL g_bButton1Down = FALSE;
static bool g_bShader = true;


static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static int g_yClick = 0;
//static float g_lightPos[4] = { 10, 10, -100, 1 };  // Position of light
static struct timeval last_idle_time;

object cube0;
object cube1;


GLuint gprogram = 0;
GLint uniform_model;
GLint uniform_view;
GLint uniform_proj;

math::mat44 matrix_model;
math::mat44 matrix_view;
math::mat44 matrix_proj;

void print_mat44(GLfloat* m)
{
	if(!m)
	{
		printf("m is null\n");
		exit(0);
	}

	for( int a = 0; a < 4; a++ )
	{
		for( int b = 0; b < 4; b++ )
		{
			printf("% 0.2f ",m[(4*a)+b]);
		}
		printf("\n");
	}
}

void RenderObjects()
{
	//float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
	//float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
	//float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
	//float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };

	printf("proj\n");	
	print_mat44(matrix_proj);
	printf("view\n");	
	print_mat44(matrix_view);

	glUniformMatrix4fv(uniform_proj,1,GL_FALSE,matrix_proj);
	glUniformMatrix4fv(uniform_view,1,GL_FALSE,matrix_view);


	printf("model\n");	
	print_mat44(matrix_model);


	//glPushMatrix();
	{
		// Main object (cube) ... transform to its coordinates, and render
		//glRotatef(15, 1, 0, 0);
		//glRotatef(45, 0, 1, 0);
		//glRotatef(g_fTeapotAngle, 0, 1, 0);
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
		//glColor4fv(colorBlue);
		//gl/BindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);

		matrix_model.SetTranslation(math::vec3(0,0,0));
		// matrix mv
		//glGetFloatv(GL_MODELVIEW_MATRIX,matrix_mv);
		glUniformMatrix4fv(uniform_model,1,GL_FALSE,matrix_model);

		//glutSolidCube(1.0);
		cube0.draw();
		//DrawCubeWithTextureCoords(1.0);


		// Child object (teapot) ... relative transform, and render
		//glPushMatrix();
		{
			//glRotatef(g_fTeapotAngle2*0.5, 0, 1, 0);
			//glTranslatef(2, 0, 0);
			//glRotatef(g_fTeapotAngle2*0.3, 1, 1, 0);

			//glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
			//glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
			//glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
			//glColor4fv(colorBronzeDiff);
			//glBindTexture(GL_TEXTURE_2D, 0);

			// matrix mv
			//glGetFloatv(GL_MODELVIEW_MATRIX,matrix_mv);
			matrix_model.SetTranslation(math::vec3(2,0,0));
	
			glUniformMatrix4fv(uniform_model,1,GL_FALSE,matrix_model);

			//cube1.draw();
			//glutSolidSphere(1.0,30,30);
			glutSolidCube(1.0);
		}
		//glPopMatrix(); 
	}
	//glPopMatrix();
}
void display(void)
{

	// Clear frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up viewing transformation, looking down -Z axis
	//glLoadIdentity();
	//gluLookAt(0, 0, -g_fViewDistance, 0, 0, -1, 0, 1, 0);

	matrix_view = math::lookat(math::vec3(0,2,g_fViewDistance),math::vec3(0,0,0),math::vec3(0,1,0));

	// Set up the stationary light
	//glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);

	// Render the scene
	RenderObjects();

	// Make sure changes appear onscreen
	glutSwapBuffers();
}

void reshape(GLint width, GLint height)
{
	g_Width = width;
	g_Height = height;

	glViewport(0, 0, g_Width, g_Height);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(65.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
	//glMatrixMode(GL_MODELVIEW);

	matrix_proj.SetPerspective(65.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);

}

void InitGraphics(void)
{
	//int width, height;
	//int nComponents;
	//void* pTextureImage;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Create texture for cube; load marble texture from file and bind it

	/*
	   pTextureImage = read_texture("marble.rgb", &width, &height, &nComponents);
	   glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
	   gluBuild2DMipmaps(GL_TEXTURE_2D,     // texture to specify
	   GL_RGBA,           // internal texture storage format
	   width,             // texture width
	   height,            // texture height
	   GL_RGBA,           // pixel format
	   GL_UNSIGNED_BYTE,	// color component format
	   pTextureImage);    // pointer to texture image

	   glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	   glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	   GL_LINEAR_MIPMAP_LINEAR);
	   glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

*/

	GLenum err = glewInit();
	if (err != GLEW_OK)
		exit(1); // or handle the error in a nicer way
	if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
		exit(1); // or handle the error in a nicer way

	CheckExt();

	printf("%s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

	// shaders
	GLuint shaders[2];

	shaders[0] = Load("vs.glsl", GL_VERTEX_SHADER, true);
	shaders[1] = Load("fs.glsl", GL_FRAGMENT_SHADER, true);

	CompileProgram(gprogram, shaders, 2);

	// uniforms
	uniform_model = glGetUniformLocation(gprogram,"model_matrix");
	uniform_view = glGetUniformLocation(gprogram,"view_matrix");
	uniform_proj = glGetUniformLocation(gprogram,"proj_matrix");

	printf("uniform model_matrix: %i\n",uniform_model);
	printf("uniform view_matrix:  %i\n",uniform_view);
	printf("uniform proj_matrix:  %i\n",uniform_proj);


	printf("location of position: %i\n",glGetAttribLocation(gprogram, "position"));
	printf("location of normal:   %i\n",glGetAttribLocation(gprogram, "normal"));

	printf("program:              %i\n",gprogram);

	glUseProgram(gprogram);

	// drawing
	cube0.load("cube.obj");
	//cube1.load("cube.obj");

	cube0.init_buffer(gprogram);
	//cube1.init_buffer(gprogram);

	
	
}

void MouseButton(int button, int state, int x, int y)
{
	// Respond to mouse button presses.
	// If button1 pressed, mark this state so we know in motion function.

	if (button == GLUT_LEFT_BUTTON)
	{
		g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
		g_yClick = y - 3 * g_fViewDistance;
	}
}

void MouseMotion(int x, int y)
{
	// If button1 pressed, zoom in/out if mouse is moved up/down.

	if (g_bButton1Down)
	{
		g_fViewDistance = (y - g_yClick) / 3.0;
				
		if (g_fViewDistance < VIEWING_DISTANCE_MIN)
			g_fViewDistance = VIEWING_DISTANCE_MIN;
	
		//printf("g_fViewDistacne=%f\n",g_fViewDistance);
	
		glutPostRedisplay();
	}
}

void AnimateScene(void)
{
	float dt;

#ifdef _WIN32
	DWORD time_now;
	time_now = GetTickCount();
	dt = (float) (time_now - last_idle_time) / 1000.0;
#else
	// Figure out time elapsed since last call to idle function
	struct timeval time_now;
	gettimeofday(&time_now, NULL);
	dt = (float)(time_now.tv_sec  - last_idle_time.tv_sec) +
		1.0e-6*(time_now.tv_usec - last_idle_time.tv_usec);
#endif

	// Animate the teapot by updating its angles
	g_fTeapotAngle += dt * 30.0;
	g_fTeapotAngle2 += dt * 100.0;

	// Save time_now for next time
	last_idle_time = time_now;

	// Force redraw
	glutPostRedisplay();
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

		case MENU_TEXTURING:
			g_bTexture = !g_bTexture;
			if (g_bTexture)
				glEnable(GL_TEXTURE_2D);
			else
				glDisable(GL_TEXTURE_2D);
			break;    
		case MENU_SHADER:
			g_bShader = !g_bShader;
			if(g_bShader)
			glUseProgramObjectARB(gprogram);
			else
			glUseProgramObjectARB(0);
			break;
		case MENU_EXIT:
			exit (0);
			break;
	}

	// Almost any menu selection requires a redraw
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:             // ESCAPE key
			exit (0);
			break;

		case 'l':
			SelectFromMenu(MENU_LIGHTING);
			break;

		case 'p':
			SelectFromMenu(MENU_POLYMODE);
			break;

		case 't':
			SelectFromMenu(MENU_TEXTURING);
			break;
		case 's':
			SelectFromMenu(MENU_SHADER);
			break;

	}
}

int BuildPopupMenu (void)
{
	int menu;

	menu = glutCreateMenu (SelectFromMenu);
	glutAddMenuEntry ("[l] Toggle lighting", MENU_LIGHTING);
	glutAddMenuEntry ("[p] Toggle polygon fill", MENU_POLYMODE);
	glutAddMenuEntry ("[t] Toggle texturing", MENU_TEXTURING);
	glutAddMenuEntry ("[s] Toggle shaders", MENU_TEXTURING);

	glutAddMenuEntry ("[Esc] Exit demo", MENU_EXIT);

	return menu;
}

int main(int argc, char** argv)
{
	// GLUT Window Initialization:
	glutInit (&argc, argv);
	glutInitWindowSize (g_Width, g_Height);
	glutInitWindowPosition(2000,100);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("shaders");


	// Register callbacks:
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutKeyboardFunc (Keyboard);
	glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutIdleFunc (AnimateScene);

	// Create our popup menu
	BuildPopupMenu ();
	glutAttachMenu (GLUT_RIGHT_BUTTON);

	// Get the initial time, for use by animation
	gettimeofday (&last_idle_time, NULL);

	// Initialize OpenGL graphics state
	InitGraphics();


	// Turn the flow of control over to GLUT
	glutMainLoop ();
	return 0;
}


