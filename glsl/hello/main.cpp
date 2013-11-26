
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include <main.h>
#include <draw.h>
#include <object.h>

void RenderObjects(void)
{
	float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
	float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
	float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
	float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };

	// get projection matrix
	glGetFloatv(GL_PROJECTION_MATRIX,matrix_proj);
	glUniformMatrix4fv(uniform_proj,1,GL_FALSE,matrix_proj);

	glGetFloatv(GL_MODELVIEW_MATRIX,matrix_view);
	glUniformMatrix4fv(uniform_view,1,GL_FALSE,matrix_view);

	glMatrixMode(GL_MODELVIEW);



	glPushMatrix();
	{
		// Main object (cube) ... transform to its coordinates, and render
		//glRotatef(15, 1, 0, 0);
		//glRotatef(45, 0, 1, 0);
		//glRotatef(g_fTeapotAngle, 0, 1, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
		glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
		glColor4fv(colorBlue);
		glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);


		cube0.draw();
		//DrawCubeWithTextureCoords(1.0);


		// Child object (teapot) ... relative transform, and render
		//glPushMatrix();
		{
			glRotatef(g_fTeapotAngle2*0.5, 0, 1, 0);
			glTranslatef(2, 0, 0);
			glRotatef(g_fTeapotAngle2*0.3, 1, 1, 0);

			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
			glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
			glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
			glColor4fv(colorBronzeDiff);
			glBindTexture(GL_TEXTURE_2D, 0);

			cube1.draw();
		}
		//glPopMatrix(); 
	}
	glPopMatrix();
}
void display(void)
{

	// Clear frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up viewing transformation, looking down -Z axis
	glLoadIdentity();
	gluLookAt(0, 0, -g_fViewDistance, 0, 0, -1, 0, 1, 0);

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
	int width, height;
	int nComponents;
	void* pTextureImage;

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

	shaders[0] = Load("vs.glsl", GL_VERTEX_SHADER_ARB, true);
	shaders[1] = Load("fs.glsl", GL_FRAGMENT_SHADER_ARB, true);

	CompileProgram(gprogram, shaders, 2);

	// uniforms
	uniform_mv = glGetUniformLocation(gprogram,"mv_matrix");
	uniform_view = glGetUniformLocation(gprogram,"view_matrix");
	uniform_proj = glGetUniformLocation(gprogram,"proj_matrix");

	// drawing
	cube0.load("cube.obj");
	cube1.load("cube.obj");
	
	cube0.init_buffer();
	cube1.init_buffer();

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
	glutCreateWindow ("CS248 GLUT example");


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


