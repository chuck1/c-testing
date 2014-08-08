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
static float g_lightPos[4] = { 0, 10, 10, 1 };  // Position of light

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

	// Animate the teapot by updating its angles
	g_fTeapotAngle += dt * 30.0;
	g_fTeapotAngle2 += dt * 100.0;

	// Save time_now for next time
	last_idle_time = time_now;

	// Force redraw
	glutPostRedisplay();
}

void		line_strip(vector<glm::vec3> const & v) {
	glDisable(GL_LIGHTING);

	glBegin(GL_LINE_STRIP);
	for(auto it = v.cbegin(); it != v.cend(); it++) glVertex3fv(&(*it)[0]);
	glEnd();

	glEnable(GL_LIGHTING);
}
void		line_loop(vector<glm::vec3> const & v) {
	glDisable(GL_LIGHTING);

	glBegin(GL_LINE_LOOP);
	for(auto it = v.cbegin(); it != v.cend(); it++) glVertex3fv(&(*it)[0]);
	glEnd();

	glEnable(GL_LIGHTING);
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
		

		// bodies
		body earth(glm::vec3(0,0,0), glm::vec3(0,0,0), 5.97219E+24);
		body ship(glm::vec3(6371.0E3 + 417.0E3, 0, 0), glm::vec3(0, 0, 7.65E3), 1000.0);

		orbit o;
		o.compute(ship, earth);

		o.conic_->standard_line();

		o.draw();

		
	}
	glPopMatrix();

}

