#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TAU (2.0 * M_PI)

#include <cmath>
#include <vector>

using namespace std;

#include <glm/glm.hpp>

#include "conics.hpp"
#include "glut.hpp"

static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;

static float g_lightPos[4] = {0, 0, 0, 1};  // Position of light

float* colorCyan = new float[4] {0.0, 1.0, 1.0, 1.0};
float* colorWhite = new float[4] {1.0, 1.0, 1.0, 1.0};

void	draw();

void	display(void) {
	// Clear frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up viewing transformation, looking down -Z axis
	glLoadIdentity();
	
	gluLookAt(
			0.0, g_view_dist, 0.0,
			0.0, 0.0, 0,
			0.0, 0.0, 1);

	if(g_body_focus) {
		cout << "focus: " << g_body_focus->name_ << endl;

		glm::vec3 x = g_body_focus->x(g_time);
		glTranslatef(x[0], x[1], x[2]);
	}

	glRotatef(g_view_yaw/M_PI*180.0,   0, 0, 1);
	
	glRotatef(-g_view_pitch/M_PI*180.0, cos(g_view_yaw), -sin(g_view_yaw), 0);
	
	glPushMatrix();
	{
		// Set up the stationary light
		glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);

		// Render the scene
		draw();
	}
	glPopMatrix();

	// Make sure changes appear onscreen
	glutSwapBuffers();
}

void		animate() {
	float dt;

	// Figure out time elapsed since last call to idle function
	struct timeval time_now;
	gettimeofday(&time_now, NULL);
	dt = (float)(time_now.tv_sec  - last_idle_time.tv_sec) +
		1.0e-6*(time_now.tv_usec - last_idle_time.tv_usec);

	g_time += dt;

	// Animate the teapot by updating its angles
	g_fTeapotAngle += dt * 30.0;
	g_fTeapotAngle2 += dt * 100.0;

	// Save time_now for next time
	last_idle_time = time_now;

	// Force redraw
	glutPostRedisplay();
}

void		init_scene() {

	// bodies
	body* sun = new body(g_universe, "sun", 1.98855E30, 696342E3);
	body* earth = new body(g_universe, "earth", 5.97219E+24, 6371.0E3);
	body* ship = new body(g_universe, "ship", 1000.0, 10.0);

	g_universe = new universe();
	
	
	g_universe->insert(
			sun,
			glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 0),
			0);

	
	glm::vec3 x_e(0,	150E9,	0);
	glm::vec3 v_e(29.78E3,	0,	0);

	g_universe->insert(earth, x_e, v_e, 0);
	
	glm::vec3 x_s(0,	6371.0E3 + 417.0E3,	0);
	glm::vec3 v_s(7.65E3, 	0, 			0);

	g_universe->insert(ship, x_e + x_s, v_e+ v_s, 0);


	g_body_focus = earth;
}

void		draw()
{
	//float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
	//float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };


	glm::mat4x4 m;

	// arms
	//float xa[] = {1,-1,0, 0};
	//float ya[] = {0, 0,1,-1};
	//float L = 1.0;

	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();
	{
		glTranslatef(-g_view_x, -g_view_y, 0.0);

		// Main object (cube) ... transform to its coordinates, and render
		glMultMatrixf(&m[0][0]);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, colorCyan);
		glMaterialfv(GL_FRONT, GL_SPECULAR, colorWhite);
		glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

		//glutSolidSphere(0.5,20,20);


		g_universe->draw(g_time);


	}
	glPopMatrix();

}

