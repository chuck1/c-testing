#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include <object.h>
void checkerror(char const * msg)
{
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		unsigned char const * str = gluErrorString(err);
		printf("%s: %s\n",msg,str);
		exit(0);
	}
	
	
}

void readbuffer(GLuint buffer)
{
	GLfloat data[24*4];

	glBindBuffer(GL_ARRAY_BUFFER, buffer);	
	checkerror("glBindBuffer");

	glGetBufferSubData(GL_ARRAY_BUFFER, 0, 1*4*sizeof(GLfloat), data);
	checkerror("glGetBufferSubData");
}

int object::load(const char * filename)
{
	FILE * fp;

	printf("load file '%s'\n",filename);

	fp = fopen(filename, "rb");
	
	if (fp <= 0) 
	{
		perror("fopen");
		return 0;
	}

	// read header
	fread(&fh_, sizeof(file_header), 1, fp);

	printf("positions: %i elements, %i vectors\n",fh_.len_positions_,fh_.len_positions_/4);
	printf("normals:   %i elements, %i vectors\n",fh_.len_normals_,fh_.len_normals_/3);
	printf("indices:   %i elements\n",fh_.len_indices_);

	// allocate
	vertex_positions_ = new GLfloat[fh_.len_positions_];
	vertex_normals_ = new GLfloat[fh_.len_normals_];
	vertex_indices_ = new GLushort[fh_.len_indices_];


	// read positions
	fread(vertex_positions_, sizeof(GLfloat), fh_.len_positions_, fp);

	// read normals
	fread(vertex_normals_, sizeof(GLfloat), fh_.len_normals_, fp);

	// read indices
	fread(vertex_indices_, sizeof(GLushort), fh_.len_indices_, fp);

	fclose(fp);


	for(unsigned int a=0;a<(fh_.len_positions_/4);++a)
	{
		for(int b = 0; b < 4; ++b)
		{
			printf("% .2f ",vertex_positions_[(a*4)+b]);
		}
		printf("\n");
	}
	for(unsigned int a=0;a<(fh_.len_normals_/3);++a)
	{
		for(int b = 0; b < 3; ++b)
		{
			printf("% .2f ",vertex_normals_[(a*3)+b]);
		}
		printf("\n");
	}
	for(size_t a=0;a<(fh_.len_indices_);++a)
	{
		printf("%i ",vertex_indices_[a]);
	}
	printf("\n");

	return 0;
}
int object::save(const char * filename)
{
	FILE * fp;

	fp = fopen(filename, "wb");

	if (!fp) 
	{
		perror("fopen");
		return 0;
	}

	printf("positions: %i elements, %i vectors\n",fh_.len_positions_,fh_.len_positions_/4);
	printf("normals:   %i elements, %i vectors\n",fh_.len_normals_,fh_.len_normals_/3);
	printf("indices:   %i elements\n",fh_.len_indices_);


	// read header
	fwrite(&fh_, sizeof(file_header), 1, fp);





	// read positions
	fwrite(vertex_positions_, sizeof(GLfloat), fh_.len_positions_, fp);

	// read normals
	fwrite(vertex_normals_, sizeof(GLfloat), fh_.len_normals_, fp);

	// read indices
	fwrite(vertex_indices_, sizeof(GLushort), fh_.len_indices_, fp);

	fclose(fp);

	return 0;
}

void object::init_buffer(GLint program)
{
	char const * attribute_name = "position";
	location_position_ = glGetAttribLocation(program, attribute_name);
	if(location_position_==-1)
	{
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		exit(0);
	}
	
	attribute_name = "normal";
	location_normal_ = glGetAttribLocation(program, attribute_name);
	if(location_normal_==-1)
	{
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		exit(0);
	}

	// position
	GLsizeiptr size = fh_.len_positions_ * sizeof(GLfloat);// sizeof(vertex_positions_);

	glGenBuffers(1, &buffer_position_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_position_);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			vertex_positions_,
			GL_DYNAMIC_DRAW);

	printf("size: %i\n",(int)size);


	checkerror("glBufferData");

	// normal
	size = fh_.len_normals_ * sizeof(GLfloat);

	glGenBuffers(1, &buffer_normal_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_normal_);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			vertex_normals_,
			GL_STATIC_DRAW);


	// index
	size = fh_.len_indices_ * sizeof(GLushort);

	glGenBuffers(1, &buffer_indices_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices_);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			size,
			vertex_indices_,
			GL_STATIC_DRAW);

	checkerror("glBufferData");

	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);


	printf("buffer positions: %i\n",buffer_position_);
	printf("buffer normals:   %i\n",buffer_normal_);
	printf("buffer indices:   %i\n",buffer_indices_);

}
void object::draw()
{
	printf("draw\n");

	glEnableVertexAttribArray(location_position_);
	glEnableVertexAttribArray(location_normal_);

	printf("draw\n");


	glBindBuffer(GL_ARRAY_BUFFER, buffer_position_);

	checkerror("glBindBuffer");

	glVertexAttribPointer(location_position_, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//checkerror();

	printf("draw\n");

	glBindBuffer(GL_ARRAY_BUFFER, buffer_normal_);
	glVertexAttribPointer(location_normal_, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices_);

	//checkerror();

	//readbuffer(buffer_position_);

	printf("draw\n");

	glDrawElements(GL_TRIANGLES, fh_.len_indices_, GL_UNSIGNED_SHORT, 0);

	//checkerror();

	printf("draw\n");

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	printf("draw\n");

	glDisableVertexAttribArray(location_position_);
	glDisableVertexAttribArray(location_normal_);

	printf("draw\n");


}




