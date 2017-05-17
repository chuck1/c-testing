#ifndef ORBIT_HPP
#define ORBIT_HPP

#undef TAU
#define TAU (2.0 * M_PI)

#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "opengl_tools.hpp"

using namespace std;


struct orbit {

	virtual void			draw(float time, glm::vec3 center) = 0;
	virtual glm::vec3		X(float time) = 0;
	virtual glm::vec3		V(float time) = 0;

};
struct orbit_line: orbit {
	orbit_line(glm::vec3 x, glm::vec3 v, float epoch): x_(x), v_(v), epoch_(epoch) {}

	virtual void			draw(float time, glm::vec3 center) {
		//abort();
	}
	virtual glm::vec3		X(float time) { return x_ + v_ * (time - epoch_); }
	virtual glm::vec3		V(float time) { return v_; }

	glm::vec3	x_;
	glm::vec3	v_;
	float		epoch_;

};

#endif



