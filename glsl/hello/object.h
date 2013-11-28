#ifndef __OBJECT_H__
#define __OBJECT_H__


struct file_header
{
	GLint len_positions_;
	GLint len_normals_;
	GLint len_texcoor_;

	GLint len_indices_;

};

class object
{
public:
	GLint location_position_;
	GLint location_normal_;
	GLint location_texcoor_;
	
	GLint location_image_;

	GLuint texture_image_;

	GLuint buffer_position_;
	GLuint buffer_normal_;
	GLuint buffer_texcoor_;

	GLuint buffer_indices_;

	file_header	fh_;

	GLfloat*	vertex_positions_;
	GLfloat*	vertex_normals_;
	GLfloat*	vertex_texcoor_;

	GLushort*	vertex_indices_;

	int	save(char const *);
	int	load(char const *);
	void	init_buffer(GLint);
	void	draw();
};

#endif
