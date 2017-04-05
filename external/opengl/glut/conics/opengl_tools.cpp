#include "opengl_tools.hpp"

void		line_strip(vector<glm::vec3> const & v) {
	bool l = glIsEnabled(GL_LIGHTING);
	if(l) glDisable(GL_LIGHTING);
	
	glBegin(GL_LINE_STRIP);
	for(auto it = v.cbegin(); it != v.cend(); it++) glVertex3fv(&(*it)[0]);
	glEnd();
	
	if(l) glEnable(GL_LIGHTING);
}
void		line_loop(vector<glm::vec3> const & v) {
	bool l = glIsEnabled(GL_LIGHTING);
	if(l) glDisable(GL_LIGHTING);

	glBegin(GL_LINE_LOOP);
	for(auto it = v.cbegin(); it != v.cend(); it++) glVertex3fv(&(*it)[0]);
	glEnd();

	if(l) glEnable(GL_LIGHTING);
}
