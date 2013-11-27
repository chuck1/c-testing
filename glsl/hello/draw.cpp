
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

GLuint Load(const char * filename, GLenum shader_type, bool check_errors)
{
	GLuint result = 0;
	FILE * fp;
	size_t filesize;
	char * data;

	fp = fopen(filename, "rb");

	if (!fp)
		return 0;

	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	data = new char [filesize + 1];
	if (!data)
		return 0;

	fread(data, 1, filesize, fp);
	data[filesize] = 0;
	fclose(fp);

	result = glCreateShader(shader_type);
	if (!result)
		return result;

	glShaderSource(result, 1, (const GLchar**)&data, NULL);

	delete [] data;

	glCompileShader(result);

	if(check_errors)
	{
		GLint status = 0;
		glGetShaderiv(result, GL_COMPILE_STATUS, &status);

		char buffer[4096];
		int len;
		glGetShaderInfoLog(result, 4096, &len, buffer);

		if(len>0)
		{
			fprintf(stderr, "%s: %s\n", filename, buffer);
		}

		if(!status)
		{
			glDeleteShader(result);
			return 0;
		}

	}

	printf("shader file '%s' loaded\n",filename);

	return result;
}

int isExtensionSupported(const char *extension)
{
	const GLubyte *extensions = NULL;
	const GLubyte *start;
	GLubyte *where, *terminator;

	/* Extension names should not have spaces. */
	where = (GLubyte *) strchr(extension, ' ');
	if (where || *extension == '\0')
		return 0;
	extensions = glGetString(GL_EXTENSIONS);
	/* It takes a bit of care to be fool-proof about parsing the
	   OpenGL extensions string. Don't be fooled by sub-strings,
	   etc. */
	start = extensions;
	for (;;)
	{
		//printf("%s\n",start);

		where = (GLubyte *) strstr((const char *) start, extension);
		if (!where)
			break;
		terminator = where + strlen(extension);
		if (where == start || *(where - 1) == ' ')
			if (*terminator == ' ' || *terminator == '\0')
				return 1;
		start = terminator;
	}
	return 0;
}
int isSupported(const char *extension)
{
	if(isExtensionSupported(extension))
	{
		printf("%s is supported\n",extension);
		return 1;
	}
	
	printf("%s is not supported\n",extension);
	exit(0);
		
}
void CheckExt()
{
	isSupported("GL_ARB_vertex_shader");
	isSupported("GL_ARB_fragment_shader");
}
void CompileProgram(GLuint &program, GLuint shaderObjects[], int numShaders)
{
	program = glCreateProgram();

	for(int a=0; a<numShaders; a++)
	{
		// Attach The Shader Objects To The Program Object
		glAttachShader(program, shaderObjects[a]);
	}

	// Link The Program Object
	glLinkProgram(program);

	GLint blen = 0;	
	GLsizei slen = 0;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH , &blen);       

	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);

		glGetInfoLogARB(program, blen, &slen, compiler_log);
		printf("compiler_log:%s\n", compiler_log);
		free (compiler_log);
	}

	printf("program=%i\n",program);

}

