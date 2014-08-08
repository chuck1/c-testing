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

struct orbit;
struct conic;

struct body {
	body(glm::vec3 x, glm::vec3 v, float m):
		x_(x), v_(v), m_(m)
	{
	}
	void		draw();
	float		soi();
	glm::vec3	x_;
	glm::vec3	v_;
	float		m_;
	float		radius_;
	body*		parent_;
	orbit*		orbit_;
};
struct universe {
	void		insert(body* b1);
	void		draw();
	vector<body*>	bodies_;
};
struct orbit {
	orbit() {}
	void		compute(body b1, body b2);
	void		draw();
	float		e_;
	float		mu_;
	float		specific_orbital_energy_;
	glm::vec3	h_;
	conic*		conic_;
};



struct conic {
	conic(plane p, float a): p_(p), a_(a) {}
	virtual float		x(float) = 0;
	virtual float		y(float) = 0;
	void			generate_line(float a, float b) {
		float t = a;
		int n = 100;
		float dt = (b - a) / (float)n; //2.0 * M_PI / (float)n;

		line_.clear();

		for(int i = 0; i < n; i++) {

			glm::vec3 point = x(t) * p_.x_ + y(t) * p_.y_;

			line_.push_back(point);

			//cout << setw(8) << point[0] << setw(8) << point[1] << setw(8) << point[2] << endl;

			t += dt;
		}
	}
	virtual void		draw() = 0;
	virtual void		standard_line() = 0;
	plane			p_;
	float			a_;
	vector<glm::vec3>	line_;
};
struct ellipse: conic {
	ellipse(plane p, float a, float b):
		conic(p, a),
		b_(b)
	{
		assert(a_ > b_);

		c_ = sqrt(a_*a_ - b_*b_);
		per_ = a_ - c_;

		cout << c_ << endl;
	}
	virtual void		standard_line() {
		generate_line(0, TAU);
	}
	virtual void		draw() {
		glColor3fv(colorWhite);
		line_loop(line_);
	}
	float		x(float t) {
		return a_ * cos(t) + c_;
	}
	float		y(float t) {
		return b_ * sin(t);
	}

	float			b_;
	float			c_; // linear eccentricity
	float			per_; // periapsis
};
struct parabola: conic {
	parabola(plane p, float a):
		conic(p, a)
	{
	}
	virtual void		standard_line() {
		generate_line(-1,1);
	}
	virtual void		draw() {
		glColor3fv(colorWhite);
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
	hyperbola(plane p, float a, float b):
		conic(p, a),
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
		line_strip(line_);
	}
	float		b_;
};

void		universe::insert(body* b1) {
	// determine parent
	body* p = 0;
	for(auto it = bodies_.cbegin(); it != bodies_.cend(); it++) {
		body* b2 = *it;

		glm::vec3 r = b1->x_ - b2->x_;

		if(glm::length(r) < b2->soi()) {
			if(p) {
				if(b2->soi() > p->soi()) continue;
			}
			p = b2;
		}
	}
	b1->parent_ = p;

	// insert
	bodies_.push_back(b1);
}
void		universe::draw() {
	for(auto it = bodies_.cbegin(); it != bodies_.cend(); it++) {
		body* b = *it;
		b->draw();
	}
}
void		body::draw() {
	glPushMatrix();
	{
		glTranslate3fv(&x_[0]);
		glutSolidSphere(radius_, 10, 10);
	}
	glPopMatrix();
	
	if(orbit_) {
		orbit_->draw();
	}

}

#endif



