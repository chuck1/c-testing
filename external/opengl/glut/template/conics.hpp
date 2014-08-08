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
struct universe {
	void		insert(body* b1, glm::vec3 x, glm::vec3 v, float time);
	body*		find_parent(body* b1, float time);
	void		draw(float time);
	vector<body*>	bodies_;
};
struct orbit {

	virtual void			draw(float time) = 0;
	virtual glm::vec3		X(float time) = 0;
	virtual glm::vec3		V(float time) = 0;

};
struct orbit_line: orbit {
	orbit_line(glm::vec3 x, glm::vec3 v, float epoch): x_(x), v_(v), epoch_(epoch) {}

	virtual void			draw(float time) {
		//abort();
	}
	virtual glm::vec3		X(float time) { return x_ + v_ * (time - epoch_); }
	virtual glm::vec3		V(float time) { return v_; }

	glm::vec3	x_;
	glm::vec3	v_;
	float		epoch_;

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
struct ellipse: conic {
	ellipse(plane p, float a, float b, float e):
		conic(p, a, e),
		b_(b)
	{
		assert(a_ > b_);

		c_ = sqrt(a_*a_ - b_*b_);
		per_ = a_ - c_;

		p_ = a_ * (1 - pow(e,2));

	}
	virtual void		standard_line() {
		generate_line(0, TAU);
	}
	virtual void		draw(float time) {
		//cout << "draw ellipse" << endl;
		glColor3fv(colorWhite);
		if(line_.empty()) {
			standard_line();
		}
		
		glm::vec3 x = b2_->x(time);
		
		glPushMatrix();
		glTranslatef(x[0], x[1], x[2]);
		line_loop(line_);
		glPopMatrix();
		
	}
	float		x(float t) {
		return a_ * cos(t) + c_;
	}
	float		y(float t) {
		return b_ * sin(t);
	}
	glm::vec3	X(float time) {

		float ta = true_anomaly_from_time(time);

		float r = p_ / (1.0 + e_ * cos(ta));

		glm::vec3 R = glm::rotate(plane_.x_, ta, plane_.n_) * r + plane_.c_;

		return R;
	}
	glm::vec3	V(float time) {

		float ta = true_anomaly_from_time(time);

		float aov = atan(e_ * sin(ta) / (1.0 + e_ * cos(ta)));
	
		//float tmp = (mu_/p_)*(1.0 + pow(e_,2) - 2.0 * cos(ta));
		
		float r = p_ / (1.0 + e_ * cos(ta));

		float tmp = mu_ * (2.0 / r - 1.0 / a_);

		float v = sqrt(tmp);
		
		glm::vec3 V =  glm::rotate(plane_.x_, (float)(ta + TAU / 4.0 + aov), plane_.n_) * v;
		
/*		cout << "(mu_/p_) = " << (mu_/p_) << endl;
		cout << "cos(ta) = " << cos(ta) << endl;
		cout << "tmp = " << tmp << endl;
		cout << "ta = " << ta << endl;
		cout << "aov = " << aov << endl;
		cout << "v = " << v << endl;
		cout << "mu = " << mu_ << endl;
		cout << "p = " << p_ << endl;
		cout << "e = " << e_ << endl;
*/
		assert(!glm::any(glm::isnan(V)));
		
		return V;
	}

	virtual float		time_from_periapsis(float time) {
		float tfp = time - epoch_;
		while(tfp > period()) tfp -= period();
		return tfp;
	}
	virtual float		mean_anomaly_from_time_from_periapsis(float time_from_periapsis) {
		return (time_from_periapsis * TAU) / period();
	}
	virtual float		period() {
		return TAU *pow(pow(a_, 3) / mu_, 0.5);
	}
	virtual float		mean_anomaly_from_eccentric_anomaly(float E) {
		return E - e_ * sin(E);
	}
	virtual float		eccentric_anomaly_from_mean_anomaly(float M) {
		float E = M + e_ * sin(M);
		E = M + e_ * sin(E);
		E = M + e_ * sin(E);
		return E;
	}
	virtual float		true_anomaly_from_eccentric_anomaly(float E) {
		return atan2(sqrt(1+e_) * sin(E/2.0), sqrt(1-e_) * cos(E/2.0));
	}
	virtual float		true_anomaly_from_time(float time) {
		float M = mean_anomaly_from_time_from_periapsis(time_from_periapsis(time));
		float E = eccentric_anomaly_from_mean_anomaly(M);
		float true_anomaly = true_anomaly_from_eccentric_anomaly(E);
		return true_anomaly;
	}

	float			b_;
	float			c_; // linear eccentricity
	float			per_; // periapsis
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



