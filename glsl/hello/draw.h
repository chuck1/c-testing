#ifndef __DRAW_H__
#define __DRAW_H__


#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

static const GLfloat vertex_positions[] = 
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

GLuint Load(const char * filename, GLenum shader_type, bool check_errors);

int isExtensionSupported(const char *extension);
int isSupported(const char *extension);
void CheckExt();
void CompileProgram(GLuint &program, GLuint shaderObjects[], int numShaders);

#endif
