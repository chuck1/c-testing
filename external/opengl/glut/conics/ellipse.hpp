#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#undef TAU
#define TAU (2.0 * M_PI)

#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "conics.hpp"

using namespace std;

struct ellipse: conic {
	ellipse(plane p, float a, float b, float e);

	virtual void		standard_line();
	virtual void		draw(float time, glm::vec3 center);
	float			x(float t);
	float			y(float t);
	glm::vec3		X(float time);
	glm::vec3		V(float time);

	virtual float		time_from_periapsis(float time);
	virtual float		mean_anomaly_from_time_from_periapsis(float time_from_periapsis);
	virtual float		period();
	virtual float		mean_anomaly_from_eccentric_anomaly(float E);
	virtual float		eccentric_anomaly_from_mean_anomaly(float M);
	virtual float		true_anomaly_from_eccentric_anomaly(float E);
	virtual float		true_anomaly_from_time(float time);

	float			b_;
	float			c_; // linear eccentricity
	float			per_; // periapsis
};

#endif

