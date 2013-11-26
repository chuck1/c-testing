
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

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
static BOOL g_bShader = FALSE;


static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static int g_yClick = 0;
static float g_lightPos[4] = { 10, 10, -100, 1 };  // Position of light
static struct timeval last_idle_time;

GLuint gprogram = 0;
float mv_matrix[16];
float view_matrix[16];
float proj_matrix[16];
GLint mvUniform;
GLint viewUniform;
GLint projUniform;

/*
const char* shader_source_vertex =
"#version 330\n"
"in vec4 position;\n"
"in vec3 normal;\n"
"uniform mat4 modelview;\n"
"uniform mat4 projection;\n"
"out vec4 vs_color;\n"
"out VS_OUT\n"
"{
"    vec3 N;
"    vec3 L;
"    vec3 V;
} vs_out;
"void main()\n"
"{\n"
"vs_color = vec4(0.8,0.4,0.4,1.0);"
"gl_Position = projection * modelview * position;\n"
"}\n";

const char* shader_source_fragment = 
"#version 330\n"
"in vec4 vs_color;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vs_color;\n"
"}\n";
*/
GLuint Load(const char * filename, GLenum shader_type, bool check_errors)
{
	GLuint result = 0;
	FILE * fp;
	size_t filesize;
	char * data;

	fp = fopen(filename, "rb");

	if (!fp)
		return 0;

	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	data = new char [filesize + 1];
	if (!data)
		return 0;

	fread(data, 1, filesize, fp);
	data[filesize] = 0;
	fclose(fp);

	result = glCreateShader(shader_type);
	if (!result)
		return result;
	
	glShaderSource(result, 1, (const GLchar**)&data, NULL);

	delete [] data;

	glCompileShader(result);

	if (check_errors)
	{
		GLint status = 0;
		glGetShaderiv(result, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			char buffer[4096];
			glGetShaderInfoLog(result, 4096, NULL, buffer);
			fprintf(stderr, "%s: %s\n", filename, buffer);
			glDeleteShader(result);
			return 0;
		}
	}

	return result;
}

int isExtensionSupported(const char *extension)
{
	const GLubyte *extensions = NULL;
	const GLubyte *start;
	GLubyte *where, *terminator;

	/* Extension names should not have spaces. */
	where = (GLubyte *) strchr(extension, ' ');
	if (where || *extension == '\0')
		return 0;
	extensions = glGetString(GL_EXTENSIONS);
	/* It takes a bit of care to be fool-proof about parsing the
	   OpenGL extensions string. Don't be fooled by sub-strings,
	   etc. */
	start = extensions;
	for (;;)
	{
		//printf("%s\n",start);

		where = (GLubyte *) strstr((const char *) start, extension);
		if (!where)
			break;
		terminator = where + strlen(extension);
		if (where == start || *(where - 1) == ' ')
			if (*terminator == ' ' || *terminator == '\0')
				return 1;
		start = terminator;
	}
	return 0;
}
int isSupported(const char *extension)
{
	if(isExtensionSupported(extension))
	{
		printf("%s is supported\n",extension);
	}
	else
	{
		printf("%s is not supported\n",extension);
		exit(0);
	}


}

void CheckExt()
{
	isSupported("GL_ARB_vertex_shader");
	isSupported("GL_ARB_fragment_shader");
	//isSupported("GL_NV_fragment_shader");

}

/*
void CompileShader(GLuint& shaderObject, char const** shaderSource, GLuint shaderType)
{
	//int length;


	shaderObject = glCreateShaderObjectARB(shaderType);
	printf("%i\n",shaderObject);

	glShaderSourceARB(shaderObject, 1, shaderSource, NULL);

	//printf("length=%i\n",length);


	glCompileShaderARB(shaderObject);

	GLint compiled;

	glGetObjectParameterivARB(shaderObject, GL_COMPILE_STATUS, &compiled);

	if (compiled)
	{
		printf("shader loaded\n");
	}

	GLint blen = 0;	
	GLsizei slen = 0;

	glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH , &blen);       

	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);

		glGetInfoLogARB(shaderObject, blen, &slen, compiler_log);
		printf("compiler_log:%s\n", compiler_log);
		free (compiler_log);
	}
}
*/

void CompileProgram(GLuint &program, GLuint shaderObjects[], int numShaders)
{
	program = glCreateProgramObjectARB();

	for(int a=0; a<numShaders; a++)
	{
		// Attach The Shader Objects To The Program Object
		glAttachObjectARB(program, shaderObjects[a]);
	}

	// Link The Program Object
	glLinkProgramARB(program);

	GLint blen = 0;	
	GLsizei slen = 0;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH , &blen);       

	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);

		glGetInfoLogARB(program, blen, &slen, compiler_log);
		printf("compiler_log:%s\n", compiler_log);
		free (compiler_log);
	}

	printf("program=%i\n",program);

}

void DrawCubeFace(float fSize)
{
	fSize /= 2.0;
	glBegin(GL_QUADS);
	glVertex3f(-fSize, -fSize, fSize);    glTexCoord2f (0, 0);
	glVertex3f(fSize, -fSize, fSize);     glTexCoord2f (1, 0);
	glVertex3f(fSize, fSize, fSize);      glTexCoord2f (1, 1);
	glVertex3f(-fSize, fSize, fSize);     glTexCoord2f (0, 1);
	glEnd();
}

static const GLfloat vertex_positions[] = 
{
	-0.5f, -0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f
	-0.5f, -0.5f,  0.5f, 1.0f, //12
	-0.5f,  0.5f,  0.5f, 1.0f  //13
	-0.5f, -0.5f, -0.5f, 1.0f, //14
	-0.5f,  0.5f, -0.5f, 1.0f, //15
	-0.5f, -0.5f, -0.5f, 1.0f, //16
	 0.5f, -0.5f, -0.5f, 1.0f, //17
	 0.5f, -0.5f,  0.5f, 1.0f, //18
	-0.5f, -0.5f,  0.5f, 1.0f, //19
	-0.5f,  0.5f, -0.5f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f
};
static const GLfloat vertex_normals[] = 
{
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f
};


static const GLushort vertex_indices[] = 
{
	 0, 1, 2,
	 2, 1, 3,
	 4, 5, 6,
	 6, 5, 7,
	 8, 9,10,
	10, 9,11,
	12,13,14,
	14,13,15,
	19,16,17,
	17,18,19,
	23,22,21,
	23,21,20
};

void InitCube()
{
	// position
	GLuint position_buffer;
	GLuint position_location = 0;

	glGenBuffers(1, &position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER,
			sizeof(vertex_positions),
			vertex_positions,
			GL_STATIC_DRAW);
	glVertexAttribPointer(position_location, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(position_location);

	// normal
	GLuint normal_buffer;
	GLuint normal_location = 1;

	glGenBuffers(1, &normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glBufferData(GL_ARRAY_BUFFER,
			sizeof(vertex_normals),
			vertex_normals,
			GL_STATIC_DRAW);
	glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(normal_location);

	// index
	GLuint index_buffer;

	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(vertex_indices),
			vertex_indices,
			GL_STATIC_DRAW);
	

}
void DrawCube()
{
	glGetFloatv(GL_MODELVIEW_MATRIX,mv_matrix);

	glUniformMatrix4fv(mvUniform,1,GL_FALSE,mv_matrix);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}


void DrawCubeWithTextureCoords (float fSize)
{
	glPushMatrix();
	DrawCubeFace (fSize);
	glRotatef (90, 1, 0, 0);
	DrawCubeFace (fSize);
	glRotatef (90, 1, 0, 0);
	DrawCubeFace (fSize);
	glRotatef (90, 1, 0, 0);
	DrawCubeFace (fSize);
	glRotatef (90, 0, 1, 0);
	DrawCubeFace (fSize);
	glRotatef (180, 0, 1, 0);
	DrawCubeFace (fSize);
	glPopMatrix();
}

void DrawTeapot()
{
	glGetFloatv(GL_MODELVIEW_MATRIX,mv_matrix);

	glUniformMatrix4fv(mvUniform,1,GL_FALSE,mv_matrix);

	glutSolidTeapot(0.3);
}

void RenderObjects(void)
{
	float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
	float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
	float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
	float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };

	// get projection matrix
	glGetFloatv(GL_PROJECTION_MATRIX,proj_matrix);
	glUniformMatrix4fv(projUniform,1,GL_FALSE,proj_matrix);

	glGetFloatv(GL_MODELVIEW_MATRIX,view_matrix);
	glUniformMatrix4fv(viewUniform,1,GL_FALSE,view_matrix);

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


		DrawCube();
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

			DrawCube();
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
	mvUniform = glGetUniformLocation(gprogram,"mv_matrix");
	viewUniform = glGetUniformLocation(gprogram,"view_matrix");
	projUniform = glGetUniformLocation(gprogram,"proj_matrix");

	// drawing
	InitCube();
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


