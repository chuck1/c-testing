#include <GL/glew.h>
#include <GL/gl.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

GLFWwindow* window;

float ratio;
int width, height;


// program
GLint p;
GLint loc_tex1;
GLint loc_tex2;

int mode = 0;

struct FBO {

	FBO() {}
	void	create() {

		w = width;
		h = height;
		r = (float)w / (float)h;

		//RGBA8 2D texture, 24 bit depth texture, 256x256
		std::cout << "gen tex" << std::endl;

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex); // in order to set parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//NULL means reserve texture memory, but texels are undefined
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL); // allocate data

		//-------------------------
		std::cout << "gen fbo" << std::endl;
		glGenFramebuffersEXT(1, &fb);
		std::cout << "fbo = " << fb << std::endl;
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
		//Attach 2D texture to this FBO
		std::cout << "attach tex to fbo" << std::endl;
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tex, 0);
		//-------------------------
		std::cout << "gen rbo" << std::endl;
		glGenRenderbuffersEXT(1, &depth_rb);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_rb);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, w, h);
		//-------------------------
		//Attach depth buffer to FBO
		std::cout << "attach depth buffer to fbo" << std::endl;
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_rb);
		//-------------------------
		//Does the GPU support current FBO configuration?
		GLenum status;
		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		switch(status)
		{
			case GL_FRAMEBUFFER_COMPLETE_EXT:
				std::cout << "good" << std::endl;
				break;
			default:
				//HANDLE_THE_ERROR;
				std::cout << "error" << std::endl;
				abort();
		}
	}
	void		prep_ortho() {

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-r, r, -1.f, 1.f, 1.f, -1.f); 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	void		cleanup() {
		//Delete resources
		glDeleteTextures(1, &tex);
		glDeleteRenderbuffersEXT(1, &depth_rb);
		//Bind 0, which means render to back buffer, as a result, fb is unbound
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glDeleteFramebuffersEXT(1, &fb);
	}
	void		draw(void(*draw_fun)()) {
		//-------------------------
		//and now you can render to GL_TEXTURE_2D
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
		//-------------------------
		//std::cout << "prepare to render" << std::endl;

		prep_ortho();

		//-------------------------
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		//-------------------------
		
		draw_fun();
		//render_tri();

		//Bind 0, which means render to back buffer
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	}
	float r;
	int w, h;

	// FBO
	GLuint tex;
	GLuint fb;
	GLuint depth_rb;

};

FBO fbo1;
FBO fbo2;

static const char * vs_source[] = {
	"#version 150 core                                                                      \n"
		"                                                                                       \n"
		"out vec2 coord;                                                                        \n"
		"void main(void)                                                                        \n"
		"{                                                                                      \n"
		"    const vec4 vertices[4] = vec4[4](vec4(-1.0, -1.0, 0.5, 1.0),                       \n"
		"                                     vec4( 1.0, -1.0, 0.5, 1.0),                       \n"
		"                                     vec4( 1.0,  1.0, 0.5, 1.0),                       \n"
		"                                     vec4(-1.0,  1.0, 0.5, 1.0));                      \n"
		"    coord.x = vertices[gl_VertexID].x;                 \n"
		"    coord.y = vertices[gl_VertexID].y;                 \n"
		"    gl_Position = vertices[gl_VertexID];                                               \n"
		"}                                                                                      \n"
};
static const char * fs_source[] =
{
	"// Julia set renderer - Fragment Shader                                                \n"
		"// Graham Sellers                                                                      \n"
		"// OpenGL SuperBible                                                                   \n"
		"#version 150 core                                                                      \n"
		"in vec2 coord;                                                                         \n"
		"out vec4 color;                                                                        \n"
		"uniform sampler2D tex1;                                                        \n"
		"uniform sampler2D tex2;                                                        \n"
		"void main(void)\n"
		"{                                                                                      \n"
		"    vec2 c = coord;                                        \n"
		"    c += vec2(1.0);                                \n"
		"    c *= 0.5;                                                \n"
		"    float x = c.x - 0.5;                                  \n"
		"    if(c.y > (x*x*x + x*x + 0.5)) {                                          \n"
		"        color = texture(tex1, c);                      \n"
		"    } else {                                                \n"
		"        color = texture(tex2, c);                      \n"
		"    }                                                         \n"
		"}                                                                                      \n"
};





static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_1:
				mode = 1;
				break;
			case GLFW_KEY_2:
				mode = 2;
				break;
			case GLFW_KEY_3:
				mode = 3;
				break;
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
		}
	}
}
static void size_callback(GLFWwindow* window, int w, int h) {

	std::cout << "width height" << std::endl;
	std::cout << width << " " << height << std::endl;

	width = w;
	height = h;
	ratio = (float)width / (float)height;
}
void		render_tri() {
	double time = glfwGetTime();

	std::cout << "time = " << time << std::endl;

	glRotatef((float)time  * 50.f, 0.f, 0.f, 1.f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
}
void		render_quad() {
	double time = glfwGetTime();

	std::cout << "time = " << time << std::endl;

	glRotatef(-(float)time  * 50.f, 0.f, 0.f, 1.f);
	glBegin(GL_QUADS);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(-0.5f, 0.5f, 0.f);
	glEnd();
}
void		render_from_texture() {

	glUseProgram(p);

	// tex1
	glUniform1i(loc_tex2, 0);

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, fbo1.tex);
	//glBindSampler(0, linearFiltering);

	// tex2
	glUniform1i(loc_tex2, 1);

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, fbo2.tex);
	//glBindSampler(0, linearFiltering);




	// draw
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);	


	glUseProgram(0);
}
void		init() {



	// FBO
	fbo1.create();
	fbo2.create();


}
void		init_shaders() {
	char *vs,*fs;

	std::cout << "create shaders" << std::endl;
	GLint shader_v = glCreateShader(GL_VERTEX_SHADER);
	GLint shader_f = glCreateShader(GL_FRAGMENT_SHADER);	

	//vs = textFileRead("test.vert");
	//fs = textFileRead("test.frag");

	std::cout << "shader source" << std::endl;
	glShaderSource(shader_v, 1, vs_source,NULL);
	glShaderSource(shader_f, 1, fs_source,NULL);

	std::cout << "compile shaders" << std::endl;
	glCompileShader(shader_v);
	glCompileShader(shader_f);

	p = glCreateProgram();

	glAttachShader(p,shader_v);
	glAttachShader(p,shader_f);

	glLinkProgram(p);
	glUseProgram(p);

	loc_tex1 = glGetUniformLocation(p, "tex1");
	loc_tex2 = glGetUniformLocation(p, "tex2");

	std::cout << "loc tex1 = " << loc_tex1 << std::endl;
	std::cout << "loc tex2 = " << loc_tex2 << std::endl;

	glUseProgram(0);

}

void		prep_ortho() {


	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void		draw() {

	fbo1.draw(render_tri);
	fbo2.draw(render_quad);

	// render to screen

	prep_ortho();

	//render();

	switch(mode) {
		case 1:
			render_tri();
			break;
		case 2:
			render_quad();
			break;
		case 3:
			render_from_texture();
			break;
	}

	glfwSwapBuffers(window);
	glfwPollEvents();

}


int main(void) {



	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if(!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, size_callback);

	int err = glewInit();
	if(err != GLEW_OK) {
		abort();
	}

	glfwGetFramebufferSize(window, &width, &height);
	ratio = (float)width / (float)height;

	init();
	init_shaders();

	while (!glfwWindowShouldClose(window)) draw();

	fbo1.cleanup();
	fbo2.cleanup();


	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


