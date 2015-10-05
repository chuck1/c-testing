#include <GL/glew.h>
#include <GL/glut.h>

#include <math/mat44.h>
#include <math/vec3.h>
#include <math/vec4.h>

bool pnt = false;

//#include <sb6.h>
//#include <vmath.h>

//#include <object.h>
//#include <sb6ktx.h>
//#include <shader.h>
GLint	create_program(GLuint* s, int c, bool b)
{
        printf("%s\n",__PRETTY_FUNCTION__);

        GLint o = glCreateProgram();
	
        for(int i = 0; i < c; ++i )
        {
                printf("shader %i attached to program %i\n",s[i],o);

                glAttachShader(o, s[i]);
        }

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

static const GLenum draw_buffers[] =
{
	GL_COLOR_ATTACHMENT0,
	GL_COLOR_ATTACHMENT1,
	GL_COLOR_ATTACHMENT2,
	GL_COLOR_ATTACHMENT3,
	GL_COLOR_ATTACHMENT4,
	GL_COLOR_ATTACHMENT5
};
class raytracer_app //: public sb6::application
{
	public:
		raytracer_app():
			prepare_program(0),
			trace_program(0),
			blit_program(0),
			max_depth(1),
			debug_depth(0),
			debug_mode(DEBUG_NONE),
			paused(false)
	{
	}

	public:
		void init()
		{
			static const char title[] = "OpenGL SuperBible - Ray Tracing";

			//sb6::application::init();

			memcpy(info.title, title, sizeof(title));

			info.windowWidth = 400;
			info.windowHeight = 400;
		}
		struct INFO
		{
			int	windowWidth;
			int	windowHeight;
			char	title[256];
		} info;

		void startup();
		void render(double currentTime);
		void onKey(int key, int action);

		/*
		   void init()
		   {
		   sb6::application::init();
		   info.windowWidth = 0;
		   info.windowHeight = 0;
		   info.flags.fullscreen = 1;
		   }
		   */
		void load_shaders();

		GLuint          prepare_program;
		GLuint          trace_program;
		GLuint          blit_program;

		struct uniforms_block
		{
			math::mat44     mv_matrix;
			math::mat44     view_matrix;
			math::mat44     proj_matrix;
		};

		GLuint          uniforms_buffer;
		GLuint          sphere_buffer;
		GLuint          plane_buffer;
		GLuint          light_buffer;

		struct
		{
			GLint           ray_origin;
			GLint           ray_lookat;
			GLint           aspect;
		} uniforms;

		GLuint          vao;

		struct sphere
		{
			math::vec3     center;
			float           radius;
			// unsigned int    : 32; // pad
			math::vec4     color;
		};

		struct plane
		{
			math::vec3     normal;
			float           d;
		};

		struct light
		{
			math::vec3     position;
			unsigned int    : 32;       // pad
		};

		enum
		{
			MAX_RECURSION_DEPTH     = 5,
			MAX_FB_WIDTH            = 2048,
			MAX_FB_HEIGHT           = 1024
		};

		enum DEBUG_MODE
		{
			DEBUG_NONE,
			DEBUG_REFLECTED,
			DEBUG_REFRACTED,
			DEBUG_REFLECTED_COLOR,
			DEBUG_REFRACTED_COLOR
		};

		GLuint              tex_composite;
		GLuint              ray_fbo[MAX_RECURSION_DEPTH];
		GLuint              tex_position[MAX_RECURSION_DEPTH];
		GLuint              tex_reflected[MAX_RECURSION_DEPTH];
		GLuint              tex_reflection_intensity[MAX_RECURSION_DEPTH];
		GLuint              tex_refracted[MAX_RECURSION_DEPTH];
		GLuint              tex_refraction_intensity[MAX_RECURSION_DEPTH];

		int                 max_depth;
		int                 debug_depth;
		DEBUG_MODE          debug_mode;
		bool                paused;

		void                recurse(int depth);
};

void raytracer_app::startup()
{
	int i;

	load_shaders();

	glGenBuffers(1, &uniforms_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, uniforms_buffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(uniforms_block), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &sphere_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, sphere_buffer);
	glBufferData(GL_UNIFORM_BUFFER, 128 * sizeof(sphere), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &plane_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, plane_buffer);
	glBufferData(GL_UNIFORM_BUFFER, 128 * sizeof(plane), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &light_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, light_buffer);
	glBufferData(GL_UNIFORM_BUFFER, 128 * sizeof(sphere), NULL, GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenFramebuffers(MAX_RECURSION_DEPTH, ray_fbo);
	glGenTextures(1, &tex_composite);
	glGenTextures(MAX_RECURSION_DEPTH, tex_position);
	glGenTextures(MAX_RECURSION_DEPTH, tex_reflected);
	glGenTextures(MAX_RECURSION_DEPTH, tex_refracted);
	glGenTextures(MAX_RECURSION_DEPTH, tex_reflection_intensity);
	glGenTextures(MAX_RECURSION_DEPTH, tex_refraction_intensity);

	glBindTexture(GL_TEXTURE_2D, tex_composite);
	glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);

	for (i = 0; i < MAX_RECURSION_DEPTH; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ray_fbo[i]);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex_composite, 0);

		glBindTexture(GL_TEXTURE_2D, tex_position[i]);
		glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, tex_position[i], 0);

		glBindTexture(GL_TEXTURE_2D, tex_reflected[i]);
		glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, tex_reflected[i], 0);

		glBindTexture(GL_TEXTURE_2D, tex_refracted[i]);
		glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, tex_refracted[i], 0);

		glBindTexture(GL_TEXTURE_2D, tex_reflection_intensity[i]);
		glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, tex_reflection_intensity[i], 0);

		glBindTexture(GL_TEXTURE_2D, tex_refraction_intensity[i]);
		glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB16F, MAX_FB_WIDTH, MAX_FB_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, tex_refraction_intensity[i], 0);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	printf("max_depth=%i\n",max_depth);
}

void raytracer_app::render(double currentTime)
{
	printf("render\n");

	static const GLfloat zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const GLfloat gray[] = { 0.1f, 0.1f, 0.1f, 0.0f };
	static const GLfloat ones[] = { 1.0f };
	static double last_time = 0.0;
	static double total_time = 0.0;

	if (!paused)
		total_time += (currentTime - last_time);
	last_time = currentTime;

	float f = (float)total_time;

	// matricies
	math::vec3 view_position(
			sinf(f * 0.3234f) * 28.0f,
			cosf(f * 0.4234f) * 28.0f,
			cosf(f * 0.1234f) * 28.0f); // sinf(f * 0.2341f) * 20.0f - 8.0f);

	math::vec3 lookat_point(sinf(f * 0.214f) * 8.0f, cosf(f * 0.153f) * 8.0f, sinf(f * 0.734f) * 8.0f);
	math::mat44 view_matrix = math::lookat(view_position,
			lookat_point,
			math::vec3(0.0f, 1.0f, 0.0f));

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniforms_buffer);
	uniforms_block * block = (uniforms_block *)glMapBufferRange(GL_UNIFORM_BUFFER,
			0,
			sizeof(uniforms_block),
			GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	math::mat44 model_matrix;
	model_matrix.SetScale(math::vec3(7.0f,7.0f,7.0f));

	// f = 0.0f;

	block->mv_matrix = view_matrix * model_matrix;
	block->view_matrix = view_matrix;
	block->proj_matrix.SetPerspective(50.0f,
			(float)info.windowWidth / (float)info.windowHeight,
			0.1f,
			1000.0f);

	glUnmapBuffer(GL_UNIFORM_BUFFER);

	// sphere
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, sphere_buffer);
	sphere * s = (sphere *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, 128 * sizeof(sphere), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	int i;

	for (i = 0; i < 128; i++)
	{
		// float f = 0.0f;
		float fi = (float)i / 128.0f;
		s[i].center = math::vec3(
				sinf(fi * 123.0f + f) * 15.75f,
				cosf(fi * 456.0f + f) * 15.75f,
				(sinf(fi * 300.0f + f) * cosf(fi * 200.0f + f)) * 20.0f);

		s[i].radius = fi * 2.3f + 3.5f;
		float r = fi * 61.0f;
		float g = r + 0.25f;
		float b = g + 0.25f;
		r = (r - floorf(r)) * 0.8f + 0.2f;
		g = (g - floorf(g)) * 0.8f + 0.2f;
		b = (b - floorf(b)) * 0.8f + 0.2f;
		s[i].color = math::vec4(r, g, b, 1.0f);
	}

	glUnmapBuffer(GL_UNIFORM_BUFFER);

	// plane
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, plane_buffer);
	plane * p = (plane *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, 128 * sizeof(plane), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	//for (i = 0; i < 1; i++)
	{
		p[0].normal = math::vec3(0.0f, 0.0f, -1.0f);
		p[0].d = 30.0f;

		p[1].normal = math::vec3(0.0f, 0.0f, 1.0f);
		p[1].d = 30.0f;

		p[2].normal = math::vec3(-1.0f, 0.0f, 0.0f);
		p[2].d = 30.0f;

		p[3].normal = math::vec3(1.0f, 0.0f, 0.0f);
		p[3].d = 30.0f;

		p[4].normal = math::vec3(0.0f, -1.0f, 0.0f);
		p[4].d = 30.0f;

		p[5].normal = math::vec3(0.0f, 1.0f, 0.0f);
		p[5].d = 30.0f;
	}

	glUnmapBuffer(GL_UNIFORM_BUFFER);

	// lights
	if(pnt) printf("lights\n");
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, light_buffer);
	light * l = (light *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, 128 * sizeof(light), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	f *= 1.0f;

	for (i = 0; i < 128; i++)
	{
		float fi = 3.33f - (float)i; //  / 35.0f;
		l[i].position = math::vec3(sinf(fi * 2.0f - f) * 15.75f,
				cosf(fi * 5.0f - f) * 5.75f,
				(sinf(fi * 3.0f - f) * cosf(fi * 2.5f - f)) * 19.4f);
	}

	glUnmapBuffer(GL_UNIFORM_BUFFER);

	// prepare
	if(pnt) printf("prepare\n");
	glBindVertexArray(vao);
	glViewport(0, 0, info.windowWidth, info.windowHeight);

	glUseProgram(prepare_program);
	glUniformMatrix4fv(uniforms.ray_lookat, 1, GL_FALSE, view_matrix);
	glUniform3fv(uniforms.ray_origin, 1, view_position);
	glUniform1f(uniforms.aspect, (float)info.windowHeight / (float)info.windowWidth);
	glBindFramebuffer(GL_FRAMEBUFFER, ray_fbo[0]);

	glDrawBuffers(6, draw_buffers);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// trace
	if(pnt) printf("trace\n");
	glUseProgram(trace_program);
	recurse(0);

	// blit
	if(pnt) printf("blit\n");
	glUseProgram(blit_program);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffer(GL_BACK);

	glActiveTexture(GL_TEXTURE0);
	switch (debug_mode)
	{
		case DEBUG_NONE:
			glBindTexture(GL_TEXTURE_2D, tex_composite);
			break;
		case DEBUG_REFLECTED:
			glBindTexture(GL_TEXTURE_2D, tex_reflected[debug_depth]);
			break;
		case DEBUG_REFRACTED:
			glBindTexture(GL_TEXTURE_2D, tex_refracted[debug_depth]);
			break;
		case DEBUG_REFLECTED_COLOR:
			glBindTexture(GL_TEXTURE_2D, tex_reflection_intensity[debug_depth]);
			break;
		case DEBUG_REFRACTED_COLOR:
			glBindTexture(GL_TEXTURE_2D, tex_refraction_intensity[debug_depth]);
			break;
	}
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	/*
	   glClearBufferfv(GL_COLOR, 0, gray);
	   glClearBufferfv(GL_DEPTH, 0, ones);


	   glBindVertexArray(vao);
	   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	   */

	glutSwapBuffers();
}

void raytracer_app::recurse(int depth)
{
	printf("recuse\n");

	glBindFramebuffer(GL_FRAMEBUFFER, ray_fbo[depth + 1]);

	if(pnt) printf("draw buffers\n");

	glDrawBuffers(6, draw_buffers);

	if(pnt) printf("blend\n");

	glEnablei(GL_BLEND, 0);
	//glEnablei(GL_BLEND, draw_buffers[0]);

	if(pnt) printf("blend\n");

	glBlendFunc(GL_ONE, GL_ONE);
	//glBlendFunci(0, GL_ONE, GL_ONE);
	//glBlendFunci(draw_buffers[0], GL_ONE, GL_ONE);

	// static const float zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	// glClearBufferfv(GL_COLOR, 0, zeros);

	if(pnt) printf("tex_position\n");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_position[depth]);

	if(pnt) printf("tex_reflected\n");
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_reflected[depth]);

	if(pnt) printf("tex_reflection_intensity\n");
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, tex_reflection_intensity[depth]);

	// Render
	if(pnt) printf("render\n");
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (depth != (max_depth - 1))
	{
		recurse(depth + 1);
	}

	/*
	   if (depth != 0)
	   {
	   glBindTexture(GL_TEXTURE_2D, tex_refracted[depth]);
	   glActiveTexture(GL_TEXTURE2);
	   glBindTexture(GL_TEXTURE_2D, tex_refraction_intensity[depth]);

	// Render
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (depth != (max_depth - 1))
	{
	recurse(depth + 1);
	}
	}
	*/

	glDisablei(GL_BLEND, 0);
	//glDisablei(GL_BLEND, draw_buffers[0]);

}

void raytracer_app::onKey(int key, int action)
{
	if (action)
	{
		switch (key)
		{
			case 27:
				exit(0);
			case '1'://GLFW_KEY_KP_ADD:
				max_depth++;
				if (max_depth > MAX_RECURSION_DEPTH)
					max_depth = MAX_RECURSION_DEPTH;
				break;
			case '2'://GLFW_KEY_KP_SUBTRACT:
				max_depth--;
				if (max_depth < 1)
					max_depth = 1;
				break;
			case 'P':
				paused = !paused;
				break;
			case 'R':
				load_shaders();
				break;
			case 'Q':
				debug_mode = DEBUG_NONE;
				break;
			case 'W':
				debug_mode = DEBUG_REFLECTED;
				break;
			case 'E':
				debug_mode = DEBUG_REFRACTED;
				break;
			case 'S':
				debug_mode = DEBUG_REFLECTED_COLOR;
				break;
			case 'D':
				debug_mode = DEBUG_REFRACTED_COLOR;
				break;
			case 'A':
				debug_depth++;
				if (debug_depth > MAX_RECURSION_DEPTH)
					debug_depth = MAX_RECURSION_DEPTH;
				break;
			case 'Z':
				debug_depth--;
				if (debug_depth < 0)
					debug_depth = 0;
				break;
		}
	}
}

void raytracer_app::load_shaders()
{
	GLuint      shaders[2];

	shaders[0] = load("shaders/trace-prepare.vs.glsl", GL_VERTEX_SHADER);
	shaders[1] = load("shaders/trace-prepare.fs.glsl", GL_FRAGMENT_SHADER);

	if (prepare_program != 0)
		glDeleteProgram(prepare_program);

	prepare_program = create_program(shaders, 2, true);

	// uniforms
	uniforms.ray_origin = glGetUniformLocation(prepare_program, "ray_origin");
	uniforms.ray_lookat = glGetUniformLocation(prepare_program, "ray_lookat");
	uniforms.aspect = glGetUniformLocation(prepare_program, "aspect");

	// trace program
	shaders[0] = load("shaders/raytracer.vs.glsl", GL_VERTEX_SHADER);
	shaders[1] = load("shaders/raytracer.fs.glsl", GL_FRAGMENT_SHADER);

	if (trace_program)
		glDeleteProgram(trace_program);

	trace_program = create_program(shaders, 2, true);

	shaders[0] = load("shaders/blit.vs.glsl", GL_VERTEX_SHADER);
	shaders[1] = load("shaders/blit.fs.glsl", GL_FRAGMENT_SHADER);

	if (blit_program)
		glDeleteProgram(blit_program);

	blit_program = create_program(shaders, 2, true);
}

raytracer_app app;

void	render()
{
	app.render(1.0);
}
void	onKey(unsigned char c, int x, int y)
{
	app.onKey(c,1);
}

int main(int argc, char ** argv)
{	
	app.init();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(app.info.windowWidth, app.info.windowHeight);
	glutInitWindowPosition(2300, 200);
	glutCreateWindow(app.info.title);
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutKeyboardFunc(onKey);

	printf("glewinit\n");

	glewInit();
	printf("startup\n");


	app.startup();

	printf("mainloop\n");

	glutMainLoop();

	return 0;
}








