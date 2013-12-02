
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include <glutpp/vertex.h>

#include "../hello/object.h"

vertex vertices[] = 
{
	{vec3(-0.5f, -0.5f, -0.5f),vec3( 0.0f,  0.0f, -1.0f),vec2(1.0f, 0.0f)},
	{vec3(-0.5f,  0.5f, -0.5f),vec3( 0.0f,  0.0f, -1.0f),vec2(1.0f, 1.0f)},
	{vec3( 0.5f, -0.5f, -0.5f),vec3( 0.0f,  0.0f, -1.0f),vec2(0.0f, 0.0f)},
	{vec3( 0.5f,  0.5f, -0.5f),vec3( 0.0f,  0.0f, -1.0f),vec2(0.0f, 1.0f)},
	{vec3( 0.5f, -0.5f, -0.5f),vec3( 1.0f,  0.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3( 0.5f,  0.5f, -0.5f),vec3( 1.0f,  0.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3( 0.5f, -0.5f,  0.5f),vec3( 1.0f,  0.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3( 0.5f,  0.5f,  0.5f),vec3( 1.0f,  0.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3( 0.5f, -0.5f,  0.5f),vec3( 0.0f,  0.0f,  1.0f),vec2(0.0f, 0.0f)},
	{vec3( 0.5f,  0.5f,  0.5f),vec3( 0.0f,  0.0f,  1.0f),vec2(0.0f, 0.0f)},
	{vec3(-0.5f, -0.5f,  0.5f),vec3( 0.0f,  0.0f,  1.0f),vec2(0.0f, 0.0f)},
	{vec3(-0.5f,  0.5f,  0.5f),vec3( 0.0f,  0.0f,  1.0f),vec2(0.0f, 0.0f)},
	{vec3(-0.5f, -0.5f,  0.5f),vec3(-1.0f,  0.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3(-0.5f,  0.5f,  0.5f),vec3(-1.0f,  0.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3(-0.5f, -0.5f, -0.5f),vec3(-1.0f,  0.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3(-0.5f,  0.5f, -0.5f),vec3(-1.0f,  0.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3(-0.5f, -0.5f, -0.5f),vec3( 0.0f, -1.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3( 0.5f, -0.5f, -0.5f),vec3( 0.0f, -1.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3( 0.5f, -0.5f,  0.5f),vec3( 0.0f, -1.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3(-0.5f, -0.5f,  0.5f),vec3( 0.0f, -1.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3(-0.5f,  0.5f, -0.5f),vec3( 0.0f,  1.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3( 0.5f,  0.5f, -0.5f),vec3( 0.0f,  1.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3( 0.5f,  0.5f,  0.5f),vec3( 0.0f,  1.0f,  0.0f),vec2(0.0f, 0.0f)},
	{vec3(-0.5f,  0.5f,  0.5f),vec3( 0.0f,  1.0f,  0.0f),vec2(0.0f, 0.0f)}
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
	object cube;
	
	cube.vertex_positions_ = vertex_positions;
	cube.vertex_normals_ = vertex_normals;
	cube.vertex_indices_ = vertex_indices;
	cube.vertex_texcoor_ = vertex_texcoor;
	
	cube.fh_.len_vertices = 24;
	cube.fh_.len_indices_ = 36;
	
	cube.save("../hello/cube.obj");
	
}



