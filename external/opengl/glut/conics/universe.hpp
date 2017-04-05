#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

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


struct body;
struct orbit;
struct conic;


struct universe {
	void			insert(body* b1, glm::vec3 x, glm::vec3 v, float time);
	body*			find_parent(body* b1, float time);
	void			draw(float time, glm::vec3 center);

	vector<body*>		bodies_;
};

extern universe*	g_universe;

#endif



