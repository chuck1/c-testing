#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>

#include <cmath>
#include <float.h>

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
static const char * vs_source[] =
{
	"// Julia set renderer - Vertex Shader                                          \n"
		"// Graham Sellers                                                   \n"
		"// OpenGL SuperBible                                                  \n"
		"#version 150 core                                                     \n"
		"                                                                   \n"
		"                                                                    \n"
		"void main(void)                                                \n"
		"{                                                                    \n"
		"    const vec4 vertices[4] = vec4[4](vec4(-1.0, -1.0, 0.5, 1.0),      \n"
		"                                     vec4( 1.0, -1.0, 0.5, 1.0),      \n"
		"                                     vec4( 1.0,  1.0, 0.5, 1.0),      \n"
		"                                     vec4(-1.0,  1.0, 0.5, 1.0));     \n"
		"    gl_Position = vertices[gl_VertexID];                              \n"
		"}                                                                     \n"
};

static const char * fs_source[] =
{
	"// Julia set renderer - Fragment Shader                               \n"
		"// Graham Sellers                                             \n"
		"// OpenGL SuperBible                                          \n"
		"#version 150 core                                             \n"

		"out vec4 color;                                               \n"
		"uniform float zoom;                                           \n"
		"uniform sampler1D tex_gradient;                               \n"
		"uniform vec2 C;                                               \n"
		"uniform vec2 offset;\n"
		"uniform vec2 screen;\n"
		"uniform int max_iterations;\n"
		"uniform int mode;\n"
		"uniform float damp;\n"
		"uniform float log_a_min;\n"
		"uniform float log_a_max;\n"

		"float scale(float x, float x0, float x1, float y0, float y1)\n"
		"{\n"
		"    float a = (y1-y0)/(x1-x0);\n"
		"    float b = y0 - a * x0;\n"
		"    return (a * x + b);\n"
		"}\n"

		"void main(void)\n"
		"{                                                                             \n"
		"    float zoo = zoom;\n"
		"    vec2 f;\n"
		"    f.x = (gl_FragCoord.x) / screen.x - 0.5;\n"
		"    f.y = (gl_FragCoord.y) / screen.y - 0.5;\n"
		"    //Z -= vec2(0.5,0.5);\n"
		"    //Z *= zoo;\n"
		"    //Z -= offset;\n"
		"    vec2 Z; \n"
		"    Z.x = offset.x + f.x * zoo * screen.x / screen.y;\n"
		"    Z.y = offset.y + f.y * zoo;\n"
		"\n"
		"    int iterations = 0;\n"
		"    const float threshold_squared = 16.0;                           \n"
		"    const float color_divisor = 128.0;               \n"
		"\n"
		"    float a0 = dot(Z,Z);\n"


		"    while(true) {\n"
		"        vec2 Z_squared;                                                \n"
		"        Z_squared.x = Z.x * Z.x - Z.y * Z.y;                           \n"
		"        Z_squared.y = 2.0 * Z.x * Z.y;                                 \n"
		"        Z = (Z_squared + C)*(1-damp) + Z*(damp);                        \n"
		"        iterations++;                                                  \n"

		"        if(iterations >= max_iterations) break;\n"

		"        if(mode==0) {\n"
		"            if(dot(Z, Z) >= threshold_squared) break;\n"
		"        }\n"

		"    }                                                                  \n"

		"    if(mode==0) {\n"
		"    if (iterations == max_iterations) {                                \n"
		"        color = vec4(0.0, 0.0, 0.0, 1.0);                              \n"
		"    } else {                                                           \n"
		"        color = texture(tex_gradient, float(iterations) / color_divisor);\n"
		"    }\n"
		"    }\n"

		"    if(mode==1) {\n"
		"    if(true) {\n"
		"    if(dot(Z,Z) < a0) {\n"
		"        color = vec4(0.0, 0.0, 0.0, 1.0);             \n"
		"    } else {                                          \n"
		"        color = texture(tex_gradient, scale(log(dot(Z,Z)), 0.0, log_a_max, 0, 1));\n"
		"        //color = texture(tex_gradient, scale(log(dot(Z,Z)), log_a_min, log_a_max, 0, 1));\n"
		"        //color = texture(tex_gradient, log(dot(Z,Z)));\n"
		"        //color = texture(tex_gradient, dot(Z,Z));\n"
		"    }\n"
		"    }\n"
		"    }\n"

		"    //color = texture(tex_gradient, (f.x + 0.5)/screen.x + (f.y + 0.5)/screen.y);\n"
		"}\n"
};

//float currentTime = 9.370f;
//float c = glm::dot(Z,Z);
//
//        if(debug) {
//                        printf("%6i%6i%12.2e%12.2e%12.2e%12.2e%12.2e%6i%12.2e%12.2e\n",
//                                                        p.x, p.y, zoom, f.x, f.y, Z0.x, Z0.y, iterations,
//                                                                                        a,
//                                                                                                                        log(a),
//                                                                                                                                                        a0);
//                                                                                                                                                                }
//
//                                                                                                                                                                        return iterations;
//                                                                                                                                                                                }
//                                                                                                                                                                                        void check_shader(GLuint shader)
//                                                                                                                                                                                                {
//                                                                                                                                                                                                urrentTime = 2.0f;
//float currentTime = 163.417374f;
float currentTime = 0.0f;

bool		paused = true;
float		time_offset = 0.0f;
float		x_offset = 0.0f;
float		y_offset = 0.0f;
double		zoom = 10; //0.002037;

int		max_iterations = 8;
const int	mode = 1;
float		damp = 0.0f;

const int	debug = 0;

float		log_a_min = 0;
float		log_a_max = 1;

glm::ivec2	iscreen;
glm::vec2	screen;

GLuint		program;
GLuint		vao;
GLuint		palette_texture;

struct UNIFORMS
{
	GLint	screen;
	GLint   zoom;
	GLint   offset;
	GLint   C;
	GLint   iter;
	GLint   mode;
	GLint   damp;
	GLint	log_a_min;
	GLint	log_a_max;
} uniforms;

class Stats
{
public:
	float			avg()
	{
		float y = 0;
		for(auto x : _M_vec) {
			assert(!isinf(x));
			assert(!isnan(x));


			y += x;

			assert(!isinf(y));
			assert(!isnan(y));
		}
		y /= (float)_M_vec.size();
		return y;
	}
	float			min()
	{
		float y = FLT_MAX;
		for(auto x: _M_vec) {
			if(x<y) y=x;
		}
		return y;
	}
	float			max()
	{
		float y = FLT_MIN;
		for(float x: _M_vec) {
			if(isinf(x)) x=FLT_MAX;
			if(x>y) y=x;
		}
		return y;
	}
	float			std()
	{
		float a = avg();
		assert(!isinf(a));
		assert(!isnan(a));

		float y = 0;
		for(auto x : _M_vec) {
			y += (x-a)*(x-a);
		
			//printf("std: y=%f\n",y);
			assert(!isinf(y));
			assert(!isnan(y));
		}
		y /= (float)_M_vec.size();
		y = sqrt(y);
		return y;
	}
	void			push(float x)
	{
		//if(isinf(x)) x = FLT_MAX;

		if(isnan(x)) return;

		if(isinf(x)) x = 1e10;

		assert(!isinf(x));
		assert(!isnan(x));

		_M_vec.push_back(x);
	}
	void			clear()
	{
		_M_vec.clear();
	}
	std::vector<float>	_M_vec;
};

Stats	stat_a;
Stats	stat_log_a;

int		solve(glm::ivec2 p, glm::vec2 C, float& a)
{
	//float x = -0.5 + (float)px/(float)w;
	//float y = -0.5 + (float)py/(float)h;

	glm::vec2 f;

	f.x = -0.5f + (float)(p.x)/(float)(iscreen.x);
	f.y = -0.5f + (float)(p.y)/(float)(iscreen.y);

	glm::vec2 Z;

	Z.x = x_offset + f.x * zoom * screen.x / screen.y;
	Z.y = y_offset + f.y * zoom;

	glm::vec2 Z0 = Z;

	//glm::vec2 Z(x,y);

	//Z.x /= screen[0];
	//Z.y /= screen[1];

	//Z /= screen;
	//Z -= glm::vec2(0.5,0.5);


	float a0 = glm::dot(Z,Z);

	int iterations = 0;
	const float threshold_squared = 16.0;
	while(true) {
		//while(iterations < max_iterations) {
		glm::vec2 Z_squared;
		Z_squared.x = Z.x * Z.x - Z.y * Z.y;        
		Z_squared.y = 2.0 * Z.x * Z.y;                 
		Z = Z_squared + C;           
		iterations++;

		if(iterations >= max_iterations) break;

		if(mode == 0) {
			if(glm::dot(Z, Z) >= threshold_squared) break;
		}
	}                                                                             

	a = glm::dot(Z,Z);

	if(debug) {
		printf("%6i%6i%12.2e%12.2e%12.2e%12.2e%12.2e%6i%12.2e%12.2e%12.2e\n",
				p.x, p.y, zoom, f.x, f.y, Z0.x, Z0.y, iterations,
				a,
				log(a),
				a0);
	}

	return iterations;
	}
	void check_shader(GLuint shader)
	{
		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if(isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			//We don't need the shader anymore.
			glDeleteShader(shader);

			//Use the infoLog as you see fit.
			printf("%s\n", &infoLog[0]);

			//In this simple program, we'll just leave
			return;
		}
	}
	void startup()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		printf("create program\n");

		program = glCreateProgram();
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, fs_source, NULL);
		glCompileShader(fs);
		check_shader(fs);

		printf("create shader\n");

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, vs_source, NULL);
		glCompileShader(vs);
		check_shader(vs);

		printf("attach shaders\n");

		glAttachShader(program, vs);
		glAttachShader(program, fs);

		glLinkProgram(program);

		printf("locate uniforms\n");

		uniforms.zoom   = glGetUniformLocation(program, "zoom");
		uniforms.offset = glGetUniformLocation(program, "offset");
		uniforms.C      = glGetUniformLocation(program, "C");
		uniforms.screen = glGetUniformLocation(program, "screen");
		uniforms.iter   = glGetUniformLocation(program, "max_iterations");
		uniforms.mode   = glGetUniformLocation(program, "mode");
		uniforms.damp   = glGetUniformLocation(program, "damp");
		uniforms.log_a_min = glGetUniformLocation(program, "log_a_min");
		uniforms.log_a_max = glGetUniformLocation(program, "log_a_max");

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
	int i = 0;
	void render(/*double currentTime*/)
	{
		currentTime += time_offset;


		static const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		float r = 0.0f;

		float t = (float)currentTime;

		r = t + time_offset;

		glm::vec2 C(
				(sinf(r * 0.1f) + cosf(r * 0.53f)) * 2.5f,
				(cosf(r * 0.13f) + sinf(r * 0.21f)) * 0.5f
			   );


		i++;
		if((i % 100) == 0) {

			if(1) {
				int total = 0;
				int count = 0;
				int it_max = -1;
				int it_min = max_iterations + 1;
				int skip = 10;
				float a;
				float log_a_min = FLT_MAX;
				float log_a_max = FLT_MIN;

				stat_a.clear();

				for(int px = 0; px < iscreen.x; px+=skip) {
					for(int py = 0; py < iscreen.y; py+=skip) {
						if(debug) {
							if((count%10)==0) {
								printf("%6s%6s%12s%12s%12s%12s%12s%6s%12s%12s%12s\n", 
										"px", "py",
										"zoom",
										"f", "f",
										"x", "y",
										"it",
										"a",
										"log(a)",
										"a0");
							}}

						int it = solve(glm::ivec2(px,py), C, a);

						count++;
						total += it;
						if(it > it_max) it_max = it;
						if(it < it_min) it_min = it;

						//printf("%f\n",a);
						stat_a.push(a);
						//printf("%f\n",a);
						if(isinf(a)) {
							stat_log_a.push((float)FLT_MAX_EXP);
						} else {
							stat_log_a.push(log(a));
						}
					}
				}

				log_a_min = stat_log_a.min();
				log_a_max = stat_log_a.max();
				if(isinf(log_a_max)) {
					printf("inf log %f\n", (float)FLT_MAX_EXP);
					log_a_max = FLT_MAX_EXP;
				}

				printf("%8s%8s%8s%8s%8s%12s%12s%12s%12s%12s%12s\n",
						"count",
						"total",
						"avg",
						"it_min",
						"it_max",
						"a_min",
						"a_max",
						"log a_min",
						"log a_max",
						"avg log_a",
						"std log_a"
				      );
				printf("%8i%8i%8.2f%8i%8i%12.2e%12.2e%12.2e%12.2e%12.2e%12.2e\n",
						count,
						total,
						(float)total/(float)count,
						it_min,
						it_max,
						stat_a.min(),
						stat_a.max(),
						log_a_min,
						log_a_max,
						stat_log_a.avg(),
						stat_log_a.std());
			}



			printf("%12s%12s\n","zoom","time");
			printf("%12.2e%12.2f\n",zoom,currentTime);
		}

		float offset[2] = { x_offset, y_offset };

		// rendering part
		glClearBufferfv(GL_COLOR, 0, color);

		glUseProgram(program);

		glUniform2fv(uniforms.C, 1, &C[0]);
		glUniform2fv(uniforms.offset, 1, offset);
		glUniform2fv(uniforms.screen, 1, &screen.x);
		glUniform1f(uniforms.zoom, zoom);
		glUniform1i(uniforms.iter, max_iterations);
		glUniform1i(uniforms.mode, mode);
		glUniform1f(uniforms.damp, damp);
		glUniform1f(uniforms.log_a_min, log_a_min);
		glUniform1f(uniforms.log_a_max, log_a_max);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glutSwapBuffers();
	}
	enum {
		KEY_ZOOM_OUT = ']',
		KEY_ITER_UP = 'x',
		KEY_ITER_DN = 'z',
		KEY_DAMP_UP = 'v',
		KEY_DAMP_DN = 'c'
	};
	void	print_help()
	{
		printf("%32s%c\n", "zoom in", KEY_ZOOM_OUT);
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
					paused = !paused;
					printf("pause\n");
					break;
				case KEY_DAMP_UP:
					damp += 0.1;
					break;
				case KEY_DAMP_DN:
					damp -= 0.1;
					break;
				case KEY_ITER_UP:
					max_iterations++;
					break;
				case KEY_ITER_DN:
					max_iterations--;
					break;
				case 'r': time_offset += 0.00001f;
					  break;
				case 'f': time_offset -= 0.00001f;
					  break;
				case 't': time_offset += 0.0001f;
					  break;
				case 'g': time_offset -= 0.0001f;
					  break;
				case 'y': time_offset += 0.01f;
					  break;
				case 'h': time_offset -= 0.01f;
					  break;
				case 'u': time_offset += 1.0f;
					  break;
				case 'j': time_offset -= 1.0f;
					  break;
				case KEY_ZOOM_OUT:
					  zoom *= 1.05;
					  printf("zoom = %f\n",zoom);
					  break;
				case '[':
					  zoom /= 1.05;
					  printf("zoom = %f\n",zoom);
					  break;
				case 'w':
					  y_offset += zoom * 0.02f;
					  break;
				case 's':
					  y_offset -= zoom * 0.02f;
					  break;
				case 'a':
					  x_offset -= zoom * 0.02f;
					  break;
				case 'd':
					  x_offset += zoom * 0.02f;
					  break;
				default:
					  break;
			};
		}
	}
	void onResize(int nw, int nh)
	{
		iscreen.x = nw;
		iscreen.y = nh;

		screen[0] = float(nw);
		screen[1] = float(nh);

		glViewport(0, 0, nw, nh);
	}
	void shutdown()
	{
		glDeleteTextures(1, &palette_texture);
		glDeleteVertexArrays(1, &vao);
		glDeleteProgram(program);
	}

	int main(int argc, char ** argv)
	{	
		printf("%f %f\n", FLT_MAX, log(FLT_MAX));

		iscreen.x = 500;
		iscreen.y = 500;

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(iscreen.x, iscreen.y);
		glutInitWindowPosition(300, 200);
		glutCreateWindow("julia");
		glutDisplayFunc(render);
		glutIdleFunc(render);
		glutKeyboardFunc(onKey);

		printf("glewinit\n");

		glewInit();
		printf("startup\n");

		//screen[0] = float(w);
		//screen[1] = float(h);

		screen = glm::vec2(iscreen);

		startup();

		printf("mainloop\n");

		glutMainLoop();

		return 0;
	}


