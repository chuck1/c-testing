#ifndef CONICS_HPP
#define CONICS_HPP

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
#include "orbit.hpp"

using namespace std;


struct plane {
	plane(glm::vec3 n, glm::vec3 c, glm::vec3 x):
		n_(n), c_(c), x_(x)
	{
		y_ = glm::cross(n_, x_);
	}
	plane(plane const & p):
		n_(p.n_),
		c_(p.c_),
		x_(p.x_),
		y_(p.y_)
	{
	}
	glm::vec3	n_; // normal
	glm::vec3	c_; // center
	glm::vec3	x_;
	glm::vec3	y_;
};

struct body;
struct orbit;
struct conic;
struct universe;

extern universe*	g_universe;
extern body*		g_body_focus;

struct state {
	float true_anomaly;
	float time;
};



struct conic: orbit {
	conic(plane p, float a, float e): plane_(p), a_(a), e_(e) {}

	static conic*		compute(body* b1, body* b2, glm::vec3 x, glm::vec3 v, float time);

	virtual float		x(float) = 0;
	virtual float		y(float) = 0;


	float			mu_;
	float			specific_orbital_energy_;
	glm::vec3		h_;

	float			epoch_;

	body*			b1_;
	body*			b2_;

	state*			state_escape;
	state*			state_encounter;
	orbit*			next_;



	// geometry
	plane			plane_;
	float			a_;
	float			e_; // eccentricity
	float			p_;


	// equations of motion
	virtual float		mean_anomaly_from_time_from_periapsis(float time) = 0;
	virtual float		period() = 0;
	virtual float		eccentric_anomaly_from_mean_anomaly(float M) = 0;
	virtual float		mean_anomaly_from_eccentric_anomaly(float E) = 0;


	void			generate_line(float a, float b) {
		float t = a;
		int n = 100;
		float dt = (b - a) / (float)n; //2.0 * M_PI / (float)n;

		line_.clear();

		for(int i = 0; i < n; i++) {

			glm::vec3 point = x(t) * plane_.x_ + y(t) * plane_.y_;

			line_.push_back(point);

			//cout << setw(8) << point[0] << setw(8) << point[1] << setw(8) << point[2] << endl;

			t += dt;
		}
	}

	virtual void		standard_line() = 0;


	vector<glm::vec3>	line_;
};

struct parabola: conic {
	parabola(plane p, float a, float e):
		conic(p, a, e)
	{
	}
	virtual void		standard_line() {
		generate_line(-1,1);
	}
	virtual void		draw() {
		glColor3fv(colorWhite);
		abort();
		line_strip(line_);
	}
	float		x(float t) {
		return a_ * t * t - a_;
	}
	float		y(float t) {
		return 2.0 * a_ * t;
	}
};
struct hyperbola: conic {
	hyperbola(plane p, float a, float b, float e):
		conic(p, a, e),
		b_(b)
	{
	}
	virtual void		standard_line() {
		generate_line(-1,1);
	}
	float		x(float t) {
		return a_ / cos(t);
	}
	float		y(float t) {
		return b_ * tan(t);
	}
	virtual void	draw() {
		glColor3fv(colorWhite);
		abort();
		line_strip(line_);
	}
	float		b_;
};



#endif



