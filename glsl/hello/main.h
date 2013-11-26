
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include <object.h>
#include <draw.h>

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

static object cube0;
static object cube1;


static GLuint gprogram = 0;
static float matrix_mv[16];
static float matrix_view[16];
static float matrix_proj[16];
static GLint uniform_mv;
static GLint uniform_view;
static GLint uniform_proj;

void RenderObjects();
void display();
void reshape(GLint width, GLint height);
void InitGraphics();
void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void AnimateScene(void);
void SelectFromMenu(int idCommand);
void Keyboard(unsigned char key, int x, int y);
int BuildPopupMenu();

