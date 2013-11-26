
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "../hello/object.h"

GLfloat vertex_positions[] = 
{
	-0.5f, -0.5f, -0.5f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, //12
	-0.5f,  0.5f,  0.5f, 1.0f, //13
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
GLfloat vertex_normals[] = 
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
GLushort vertex_indices[] = 
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

int main()
{
	object cube;
	
	cube.vertex_positions_ = vertex_positions;
	cube.vertex_normals_ = vertex_normals;
	cube.vertex_indices_ = vertex_indices;

}



