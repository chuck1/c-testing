#include <stdio.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <cmath>

#include <math/vec3.h>
#include <math/color.h>

static const unsigned char palette[] =
{
	0xFF, 0x00, 0x00, 0xFF, 0x0E, 0x03, 0xFF, 0x1C,
	0x07, 0xFF, 0x2A, 0x0A, 0xFF, 0x38, 0x0E, 0xFF,
	0x46, 0x12, 0xFF, 0x54, 0x15, 0xFF, 0x62, 0x19,
	0xFF, 0x71, 0x1D, 0xFF, 0x7F, 0x20, 0xFF, 0x88,
	0x22, 0xFF, 0x92, 0x25, 0xFF, 0x9C, 0x27, 0xFF,
	0xA6, 0x2A, 0xFF, 0xB0, 0x2C, 0xFF, 0xBA, 0x2F,
	0xFF, 0xC4, 0x31, 0xFF, 0xCE, 0x34, 0xFF, 0xD8,
	0x36, 0xFF, 0xE2, 0x39, 0xFF, 0xEC, 0x3B, 0xFF,
	0xF6, 0x3E, 0xFF, 0xFF, 0x40, 0xF8, 0xFE, 0x40,
	0xF1, 0xFE, 0x40, 0xEA, 0xFE, 0x41, 0xE3, 0xFD,
	0x41, 0xDC, 0xFD, 0x41, 0xD6, 0xFD, 0x42, 0xCF,
	0xFC, 0x42, 0xC8, 0xFC, 0x42, 0xC1, 0xFC, 0x43,
	0xBA, 0xFB, 0x43, 0xB4, 0xFB, 0x43, 0xAD, 0xFB,
	0x44, 0xA6, 0xFA, 0x44, 0x9F, 0xFA, 0x45, 0x98,
	0xFA, 0x45, 0x92, 0xF9, 0x45, 0x8B, 0xF9, 0x46,
	0x84, 0xF9, 0x46, 0x7D, 0xF8, 0x46, 0x76, 0xF8,
	0x46, 0x6F, 0xF8, 0x47, 0x68, 0xF8, 0x47, 0x61,
	0xF7, 0x47, 0x5A, 0xF7, 0x48, 0x53, 0xF7, 0x48,
	0x4C, 0xF6, 0x48, 0x45, 0xF6, 0x49, 0x3E, 0xF6,
	0x49, 0x37, 0xF6, 0x4A, 0x30, 0xF5, 0x4A, 0x29,
	0xF5, 0x4A, 0x22, 0xF5, 0x4B, 0x1B, 0xF5, 0x4B,
	0x14, 0xF4, 0x4B, 0x0D, 0xF4, 0x4C, 0x06, 0xF4,
	0x4D, 0x04, 0xF1, 0x51, 0x0D, 0xE9, 0x55, 0x16,
	0xE1, 0x59, 0x1F, 0xD9, 0x5D, 0x28, 0xD1, 0x61,
	0x31, 0xC9, 0x65, 0x3A, 0xC1, 0x69, 0x42, 0xB9,
	0x6D, 0x4B, 0xB1, 0x71, 0x54, 0xA9, 0x75, 0x5D,
	0xA1, 0x79, 0x66, 0x99, 0x7D, 0x6F, 0x91, 0x81,
	0x78, 0x89, 0x86, 0x80, 0x81, 0x8A, 0x88, 0x7A,
	0x8E, 0x90, 0x72, 0x92, 0x98, 0x6A, 0x96, 0xA1,
	0x62, 0x9A, 0xA9, 0x5A, 0x9E, 0xB1, 0x52, 0xA2,
	0xBA, 0x4A, 0xA6, 0xC2, 0x42, 0xAA, 0xCA, 0x3A,
	0xAE, 0xD3, 0x32, 0xB2, 0xDB, 0x2A, 0xB6, 0xE3,
	0x22, 0xBA, 0xEB, 0x1A, 0xBE, 0xF4, 0x12, 0xC2,
	0xFC, 0x0A, 0xC6, 0xF5, 0x02, 0xCA, 0xE6, 0x09,
	0xCE, 0xD8, 0x18, 0xD1, 0xCA, 0x27, 0xD5, 0xBB,
	0x36, 0xD8, 0xAD, 0x45, 0xDC, 0x9E, 0x54, 0xE0,
	0x90, 0x62, 0xE3, 0x82, 0x6F, 0xE6, 0x71, 0x7C,
	0xEA, 0x61, 0x89, 0xEE, 0x51, 0x96, 0xF2, 0x40,
	0xA3, 0xF5, 0x30, 0xB0, 0xF9, 0x20, 0xBD, 0xFD,
	0x0F, 0xE3, 0xFF, 0x01, 0xE9, 0xFF, 0x01, 0xEE,
	0xFF, 0x01, 0xF4, 0xFF, 0x00, 0xFA, 0xFF, 0x00,
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x0A, 0xFF, 0xFF,
	0x15, 0xFF, 0xFF, 0x20, 0xFF, 0xFF, 0x2B, 0xFF,
	0xFF, 0x36, 0xFF, 0xFF, 0x41, 0xFF, 0xFF, 0x4C,
	0xFF, 0xFF, 0x57, 0xFF, 0xFF, 0x62, 0xFF, 0xFF,
	0x6D, 0xFF, 0xFF, 0x78, 0xFF, 0xFF, 0x81, 0xFF,
	0xFF, 0x8A, 0xFF, 0xFF, 0x92, 0xFF, 0xFF, 0x9A,
	0xFF, 0xFF, 0xA3, 0xFF, 0xFF, 0xAB, 0xFF, 0xFF,
	0xB4, 0xFF, 0xFF, 0xBC, 0xFF, 0xFF, 0xC4, 0xFF,
	0xFF, 0xCD, 0xFF, 0xFF, 0xD5, 0xFF, 0xFF, 0xDD,
	0xFF, 0xFF, 0xE6, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF,
	0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9,
	0xFF, 0xFF, 0xF3, 0xFF, 0xFF, 0xED, 0xFF, 0xFF,
	0xE7, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xDB, 0xFF,
	0xFF, 0xD5, 0xFF, 0xFF, 0xCF, 0xFF, 0xFF, 0xCA,
	0xFF, 0xFF, 0xC4, 0xFF, 0xFF, 0xBE, 0xFF, 0xFF,
	0xB8, 0xFF, 0xFF, 0xB2, 0xFF, 0xFF, 0xAC, 0xFF,
	0xFF, 0xA6, 0xFF, 0xFF, 0xA0, 0xFF, 0xFF, 0x9B,
	0xFF, 0xFF, 0x96, 0xFF, 0xFF, 0x90, 0xFF, 0xFF,
	0x8B, 0xFF, 0xFF, 0x86, 0xFF, 0xFF, 0x81, 0xFF,
	0xFF, 0x7B, 0xFF, 0xFF, 0x76, 0xFF, 0xFF, 0x71,
	0xFF, 0xFF, 0x6B, 0xFF, 0xFF, 0x66, 0xFF, 0xFF,
	0x61, 0xFF, 0xFF, 0x5C, 0xFF, 0xFF, 0x56, 0xFF,
	0xFF, 0x51, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x47,
	0xFF, 0xFF, 0x41, 0xF9, 0xFF, 0x40, 0xF0, 0xFF,
	0x40, 0xE8, 0xFF, 0x40, 0xDF, 0xFF, 0x40, 0xD7,
	0xFF, 0x40, 0xCF, 0xFF, 0x40, 0xC6, 0xFF, 0x40,
	0xBE, 0xFF, 0x40, 0xB5, 0xFF, 0x40, 0xAD, 0xFF,
	0x40, 0xA4, 0xFF, 0x40, 0x9C, 0xFF, 0x40, 0x95,
	0xFF, 0x40, 0x8D, 0xFF, 0x40, 0x86, 0xFF, 0x40,
	0x7E, 0xFF, 0x40, 0x77, 0xFF, 0x40, 0x6F, 0xFF,
	0x40, 0x68, 0xFF, 0x40, 0x60, 0xFF, 0x40, 0x59,
	0xFF, 0x40, 0x51, 0xFF, 0x40, 0x4A, 0xFA, 0x43,
	0x42, 0xF3, 0x48, 0x3E, 0xED, 0x4E, 0x3D, 0xE6,
	0x53, 0x3B, 0xDF, 0x58, 0x39, 0xD8, 0x5E, 0x37,
	0xD2, 0x63, 0x35, 0xCB, 0x68, 0x34, 0xC4, 0x6D,
	0x32, 0xBD, 0x73, 0x30, 0xB7, 0x78, 0x2E, 0xB0,
	0x7D, 0x2D, 0xA9, 0x83, 0x2B, 0xA2, 0x88, 0x29,
	0x9C, 0x8D, 0x27, 0x95, 0x92, 0x25, 0x8E, 0x98,
	0x24, 0x87, 0x9D, 0x22, 0x81, 0xA2, 0x20, 0x7A,
	0xA6, 0x1E, 0x74, 0xAB, 0x1D, 0x6E, 0xB0, 0x1B,
	0x68, 0xB5, 0x1A, 0x61, 0xB9, 0x18, 0x5B, 0xBE,
	0x17, 0x55, 0xC3, 0x15, 0x4F, 0xC8, 0x13, 0x48,
	0xCD, 0x12, 0x42, 0xD1, 0x10, 0x3C, 0xD6, 0x0F,
	0x36, 0xDB, 0x0D, 0x2F, 0xE0, 0x0C, 0x29, 0xE4,
	0x0A, 0x23, 0xE9, 0x08, 0x1D, 0xEE, 0x07, 0x16,
	0xF3, 0x05, 0x10, 0xF7, 0x04, 0x0A, 0xFC, 0x02,
	0x04, 0xFB, 0x01, 0x04, 0xEF, 0x00, 0x12, 0xE4,
	0x00, 0x1F, 0xD9, 0x00, 0x2D, 0xCE, 0x00, 0x3B,
	0xC2, 0x00, 0x48, 0xB7, 0x00, 0x56, 0xAC, 0x00,
	0x64, 0xA0, 0x00, 0x72, 0x95, 0x00, 0x7F, 0x8A,
	0x00, 0x88, 0x7F, 0x00, 0x92, 0x75, 0x00, 0x9C,
	0x6B, 0x00, 0xA6, 0x61, 0x00, 0xB0, 0x57, 0x00,
	0xBA, 0x4E, 0x00, 0xC4, 0x44, 0x00, 0xCE, 0x3A,
	0x00, 0xD8, 0x30, 0x00, 0xE2, 0x27, 0x00, 0xEC,
	0x1D, 0x00, 0xF6, 0x13, 0x00, 0xFF, 0x09, 0x00,
};
void	link(GLint o)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	// Link The Program Object
	glLinkProgram(o);
	
	GLint blen = 0; 
	GLsizei slen = 0;
	
	glGetProgramiv(o, GL_INFO_LOG_LENGTH , &blen);
	
	
	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);

		glGetInfoLogARB(o, blen, &slen, compiler_log);
		printf("compiler_log:%s\n", compiler_log);
		free (compiler_log);
	}

	printf("program=%i\n",o);

}
GLuint	load(const char * filename, GLenum shader_type)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	printf("loading %s\n",filename);

	FILE * fp;
	size_t filesize;
	char * data;

	fp = fopen(filename, "rb");

	if (!fp)
	{
		perror("fopen");
		exit(0);
	}

	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	data = new char [filesize + 1];

	if (!data) exit(0);

	fread(data, 1, filesize, fp);
	data[filesize] = 0;
	fclose(fp);

	GLuint o = glCreateShader(shader_type);

	if (!o) exit(0);

	glShaderSource(o, 1, (const GLchar**)&data, NULL);

	delete [] data;

	glCompileShader(o);

	GLint status = 0;
	glGetShaderiv(o, GL_COMPILE_STATUS, &status);

	char buffer[4096];
	int len;
	glGetShaderInfoLog(o, 4096, &len, buffer);

	if(len>0)
	{
		fprintf(stderr, "%s: %s\n", filename, buffer);
	}

	if(!status)
	{
		printf("compile failed\n");
		glDeleteShader(o);
		exit(0);
	}


	printf("shader file '%s' loaded\n",filename);
	return o;
}


float currentTime = 9.370f;
bool paused = true;
float time_offset = 0.0f;
float x_offset = 0.0f;
float y_offset = 0.0f;
double zoom = 1;
int w,h;
float screen[2];
GLuint      program;
GLuint      vao;
GLuint      palette_texture;

struct UNIFORMS
{
	GLint	screen;
	GLint	num_spheres;
	GLint	num_planes;
	GLint	num_trace;
	struct sphere
	{
		GLint center;
		GLint radius;
		GLint color;
	} S[128];
	GLint	P[128];
} uniforms;

void startup()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	printf("create program\n");

	program = glCreateProgram();

	printf("create shader\n");
	/*
	   GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	   glShaderSource(fs, 1, fs_source, NULL);
	   glCompileShader(fs);
	   */
	GLuint fs = load("fs.glsl", GL_FRAGMENT_SHADER);

	printf("create shader\n");
	/*
	   GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	   glShaderSource(vs, 1, vs_source, NULL);
	   glCompileShader(vs);
	   */
	GLuint vs = load("vs.glsl", GL_VERTEX_SHADER);

	printf("attach shaders\n");

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	link(program);

	printf("locate uniforms\n");

	uniforms.screen = glGetUniformLocation(program, "screen");
	uniforms.num_spheres = glGetUniformLocation(program, "num_spheres");
	uniforms.num_planes = glGetUniformLocation(program, "num_planes");
	uniforms.num_trace = glGetUniformLocation(program, "num_trace");
	uniforms.S[0].center = glGetUniformLocation(program, "SPHERES.S[0].center");
	uniforms.S[0].radius = glGetUniformLocation(program, "S[0].radius");
	uniforms.S[0].color = glGetUniformLocation(program, "S[0].color");

	

	printf("screen = %i\n", uniforms.screen);
	printf("%i\n", uniforms.num_spheres);
	printf("%i\n", uniforms.num_planes);
	printf("%i\n", uniforms.num_trace);
	printf("%i\n", uniforms.S[0].center);
	printf("%i\n", uniforms.S[0].radius);
	printf("%i\n", uniforms.S[0].color);


	printf("%i\n", glGetUniformLocation(program, "S[0]"));
	printf("%i\n", glGetUniformLocation(program, "S"));
	printf("%i\n", glGetUniformLocation(program, "SPHERES.S[0]"));
	printf("%i\n", glGetUniformLocation(program, "SPHERES"));

	
	//uniforms.P[0] = glGetUniformLocation(program, "P[0]");	

	printf("delete shaders\n");

	glDeleteShader(vs);
	glDeleteShader(fs);

	printf("gen texture\n");

	glGenTextures(1, &palette_texture);
	glBindTexture(GL_TEXTURE_1D, palette_texture);

	glTexImage1D(
			GL_TEXTURE_1D,
			0,
			GL_RGB,
			256,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE_3_3_2,
			NULL);

	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, 256, GL_RGB, GL_UNSIGNED_BYTE, palette);
	glGenerateMipmap(GL_TEXTURE_1D);
}
void render(/*double currentTime*/)
{
	printf("render\n");

	static const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// rendering part
	glClearBufferfv(GL_COLOR, 0, color);

	glUseProgram(program);

	// uniforms
	glUniform2fv(uniforms.screen, 1, screen);
	glUniform3fv(uniforms.S[0].center, 1, math::vec3(0.0,0.0,-2.0));
	glUniform1f(uniforms.S[0].radius, 1.0);
	glUniform4fv(uniforms.S[0].color, 1, math::blue);

	glUniform1i(uniforms.num_spheres, 1);
	glUniform1i(uniforms.num_planes, 0);
	glUniform1i(uniforms.num_trace, 1);


	// draw full screen quad
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glutSwapBuffers();
}
void onKey(unsigned char key, int, int)
{
	//if (action == 1)
	{
		switch (key)
		{
			case 27:
				exit(0);
			case ' ':
				render();
				break;
			default:
				break;
		};
	}
}
void onResize(int nw, int nh)
{
	w = nw;h = nh;

	screen[0] = float(w);
	screen[1] = float(h);

	glViewport(0, 0, w, h);
}
void shutdown()
{
	glDeleteTextures(1, &palette_texture);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(program);
}

int main(int argc, char ** argv)
{	
	w = 1000;
	h = 1000;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(2300, 200);
	glutCreateWindow("julia");
	glutKeyboardFunc(onKey);

	printf("glewinit\n");

	glewInit();
	printf("startup\n");


	screen[0] = float(w);
	screen[1] = float(h);


	startup();

	printf("mainloop\n");

	glutMainLoop();

	return 0;
}


