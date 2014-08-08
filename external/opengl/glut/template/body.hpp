#ifndef BODY_HPP
#define BODY_HPP

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

struct orbit;
struct conic;
struct universe;

struct body {
	body(universe* u, string name, float m, float radius):
		universe_(u), name_(name), m_(m), radius_(radius)
	{}

	glm::vec3	v(float time);
	glm::vec3	x(float time);
	body*		find_parent(body* b1, float time);
	void		draw(float time);
	float		soi();

	universe*	universe_;
	string		name_;

	float		m_;
	float		radius_;
	orbit*		orbit_;
	vector<body*>	children_;
};

extern body*		g_body_focus;

#endif

