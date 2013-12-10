
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include <glutpp/window.h>
#include <glutpp/object.h>

#include <math/vec2.h>

glutpp::vertex vertices[] = 
{
	{ math::vec3(-0.5f, -0.5f, -0.5f), math::vec3( 0.0f,  0.0f, -1.0f), math::vec2(1.0f, 0.0f) },
	{ math::vec3(-0.5f,  0.5f, -0.5f), math::vec3( 0.0f,  0.0f, -1.0f), math::vec2(1.0f, 1.0f) },
	{ math::vec3( 0.5f, -0.5f, -0.5f), math::vec3( 0.0f,  0.0f, -1.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3( 0.5f,  0.5f, -0.5f), math::vec3( 0.0f,  0.0f, -1.0f), math::vec2(0.0f, 1.0f) },
	{ math::vec3( 0.5f, -0.5f, -0.5f), math::vec3( 1.0f,  0.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3( 0.5f,  0.5f, -0.5f), math::vec3( 1.0f,  0.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3( 0.5f, -0.5f,  0.5f), math::vec3( 1.0f,  0.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3( 0.5f,  0.5f,  0.5f), math::vec3( 1.0f,  0.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3( 0.5f, -0.5f,  0.5f), math::vec3( 0.0f,  0.0f,  1.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3( 0.5f,  0.5f,  0.5f), math::vec3( 0.0f,  0.0f,  1.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3(-0.5f, -0.5f,  0.5f), math::vec3( 0.0f,  0.0f,  1.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3(-0.5f,  0.5f,  0.5f), math::vec3( 0.0f,  0.0f,  1.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3(-0.5f, -0.5f,  0.5f), math::vec3(-1.0f,  0.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3(-0.5f,  0.5f,  0.5f), math::vec3(-1.0f,  0.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3(-0.5f, -0.5f, -0.5f), math::vec3(-1.0f,  0.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3(-0.5f,  0.5f, -0.5f), math::vec3(-1.0f,  0.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3(-0.5f, -0.5f, -0.5f), math::vec3( 0.0f, -1.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3( 0.5f, -0.5f, -0.5f), math::vec3( 0.0f, -1.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3( 0.5f, -0.5f,  0.5f), math::vec3( 0.0f, -1.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3(-0.5f, -0.5f,  0.5f), math::vec3( 0.0f, -1.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3(-0.5f,  0.5f, -0.5f), math::vec3( 0.0f,  1.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3( 0.5f,  0.5f, -0.5f), math::vec3( 0.0f,  1.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3( 0.5f,  0.5f,  0.5f), math::vec3( 0.0f,  1.0f,  0.0f), math::vec2(0.0f, 0.0f) },
	{ math::vec3(-0.5f,  0.5f,  0.5f), math::vec3( 0.0f,  1.0f,  0.0f), math::vec2(0.0f, 0.0f) }
};

GLushort indices[] = 
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
	glutpp::window w(10,10,0,0,"cube");
	
	glutpp::object cube(&w);
	
	cube.vertices_ = vertices;
	cube.indices_ = indices;
	
	cube.fh_.len_vertices_ = 24;
	cube.fh_.len_indices_ = 36;
	
	cube.save("cube.obj");

	
}



