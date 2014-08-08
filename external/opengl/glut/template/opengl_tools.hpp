#ifndef OPENGL_TOOLS_HPP
#define OPENGL_TOOLS_HPP

#include <vector>

#include <GL/glut.h>

#include <glm/glm.hpp>

using namespace std;

extern float* colorCyan;
extern float* colorWhite;

void		line_strip(vector<glm::vec3> const &);
void		line_loop(vector<glm::vec3> const &);

#endif
