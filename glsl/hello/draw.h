#ifndef __DRAW_H__
#define __DRAW_H__


#include <GL/glew.h>
#include <GL/glut.h>

GLuint Load(const char * filename, GLenum shader_type, bool check_errors);
int isExtensionSupported(const char *extension);
int isSupported(const char *extension);
void CheckExt();
void CompileProgram(GLuint &program, GLuint shaderObjects[], int numShaders);

#endif
