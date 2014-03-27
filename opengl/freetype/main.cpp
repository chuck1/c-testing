
#include <GL/glew.h>
#include <GL/glut.h>

#include <ft2build.h>
#include FT_FREETYPE_H



FT_Library ft;
FT_Face face;
FT_GlyphSlot g;


GLint program;
GLint uniform_color;

void printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		free(infoLog);
	}
}

void printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		free(infoLog);
	}
}
int init_shader()
{
	char const * vs_source[] = {
		"#version 330\n",
		"\n",
		"layout (location = 0) in vec4 coord;\n",
		"out vec2 texcoord;\n",
		"\n",
		"void main(void) {\n",
		"  gl_Position = vec4(coord.xy, 0, 1);\n",
		"  texcoord = coord.zw;\n",
		"}\n"};

	char const * fs_source[] = {
		"#version 330\n",
		"\n",
		"in vec2 texcoord;\n",
		"out vec4 ocolor;\n",
		"uniform sampler2D tex;\n",
		"uniform vec4 color;\n",
		" \n",
		"void main(void) {\n",
		"  ocolor = vec4(1, 1, 1, texture2D(tex, texcoord).a) * color;\n",
		"// a ocolor = vec4(1,0,1,1);\n",
		"}\n",
		"\n"};


	GLenum vs = glCreateShaderObjectARB(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vs_source, NULL);
	glCompileShader(vs);
	glAttachShader(program, vs);



	GLenum fs = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fs_source, NULL);
	glCompileShader(fs);
	glAttachShader(program, fs);


	glLinkProgram(program);

	printShaderInfoLog(vs);
	printShaderInfoLog(fs);
	printProgramInfoLog(program);

	glUseProgram(program);






}
int init()
{
	if(FT_Init_FreeType(&ft))
	{
		fprintf(stderr, "Could not init freetype library\n");
		return 1;
	}

	if(FT_New_Face(ft, "/usr/share/vlc/skins2/fonts/FreeSans.ttf", 0, &face))
	{
		fprintf(stderr, "Could not open font\n");
		return 1;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	if(FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		fprintf(stderr, "Could not load character 'X'\n");
		return 1;
	}

	g = face->glyph;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	GLint uniform_tex = glGetUniformLocation(program, "tex");
	uniform_tex = glGetUniformLocation(program, "tex");
	GLint attribute_coord = glGetAttribLocation(program, "coord");


	if(uniform_tex == -1)
	{
		printf("tex not found\n");
		return 1;
	}
	if(uniform_color == -1)
	{
		printf("color not found\n");
		return 1;
	}
	if(attribute_coord == -1)
	{
		printf("coord not found\n");
		return 1;
	}

	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(uniform_tex, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
}
void render_text(const char *text, float x, float y, float sx, float sy)
{
	const char *p;

	for(p = text; *p; p++) {
		if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
			continue;

		printf("write %c\n",*p);

		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_ALPHA,
				g->bitmap.width,
				g->bitmap.rows,
				0,
				GL_ALPHA,
				GL_UNSIGNED_BYTE,
				g->bitmap.buffer
			    );

		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{x2,     -y2    , 0, 0},
			{x2 + w, -y2    , 1, 0},
			{x2,     -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (g->advance.x >> 6) * sx;
		y += (g->advance.y >> 6) * sy;
	}
}
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat black[4] = {0, 0, 0, 1};
	glUniform4fv(uniform_color, 1, black);

	float sx = 2.0 / glutGet(GLUT_WINDOW_WIDTH);
	float sy = 2.0 / glutGet(GLUT_WINDOW_HEIGHT);

	render_text("The Quick Brown Fox Jumps Over The Lazy Dog",
			-1 + 8 * sx,   1 - 50 * sy,    sx, sy);
	render_text("The Misaligned Fox Jumps Over The Lazy Dog",
			-1 + 8.5 * sx, 1 - 100.5 * sy, sx, sy);

	glutSwapBuffers();
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}
void idle(void)
{
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);

	(void)glutCreateWindow("GLUT Program");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);


	glewInit();

	if(init_shader()) return 1;
	if(init()) return 1;

	glutMainLoop();

	return EXIT_SUCCESS;
}



