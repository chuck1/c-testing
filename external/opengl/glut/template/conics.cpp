
#include "conics.hpp"

orbit*		orbit::compute(body* b1, glm::vec3 x, glm::vec3 v, float time) {

body b2 = b1->universe_->find_parent(b1);
if(b2 == 0) {
   return new orbit_line(x, v, time);
}

	glm::vec3 v = v - b2.v(time);
	glm::vec3 r = x - b2.x(time);
	h_ = glm::cross(r, v);

	mu_ = 6.67E-11 * (b1.m_ + b2.m_);

	specific_orbital_energy_ = pow(glm::length(v), 2.0) / 2.0 - mu_ / glm::length(r);

	float a = -mu_ / 2.0 / specific_orbital_energy_;

	float tmp = 2.0 * specific_orbital_energy_ * pow(glm::length(h_), 2.0) / pow(mu_, 2.0);
	e_ = sqrt(1.0 + tmp);

	/*
	   cout << "tmp " << tmp << endl;
	   cout << "r   " << glm::length(r) << endl;
	   cout
	   << setw(16) << r[0]
	   << setw(16) << r[1]
	   << setw(16) << r[2]
	   << endl;
	   */

	// eccentricity vector
	glm::vec3 E = glm::cross(v, h_) / mu_ - r / glm::length(r);

	float true_anomaly = acos(glm::dot(E, r) / glm::length(E) / glm::length(r));

	if(glm::dot(r, v) < 0.0) true_anomaly = TAU - true_anomaly;

	// orbital plane x
	glm::vec3 x = glm::rotate(r, -true_anomaly, h_);
	x = glm::normalize(x);

	plane pl(glm::normalize(h_), b2.x_, x);

	if(e_ >= 0.0 && e_ < 1.0) {
		conic_ = new ellipse(pl, a, sqrt(pow(a, 2) * (1.0 - pow(e_, 2))));
	} else if(e_ == 1.0) {
		conic_ = new parabola(pl, a);
	} else if(e_ > 1.0) {
		float b = sqrt(pow(a, 2) * (pow(e_, 2) - 1.0));
		conic_ = new hyperbola(pl, a, b);
	} else {
		abort();
	}

}
void		orbit::draw() {
	assert(conic_);
	conic_->draw();
}
float		body::soi() {
	if(parent_) {
		assert(orbit_);

		return orbit_->conic_->a_ * pow(m_ / parent_->m_, 2.0/5.0);
	} else {
		return numeric_limits<float>::infinity();
	}
}




