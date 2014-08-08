

#include <GL/glut.h>

#include "universe.hpp"
#include "body.hpp"
#include "conics.hpp"
#include "ellipse.hpp"

universe* g_universe = new universe;
body* g_body_focus = 0;

conic*		conic::compute(body* b1, body* b2, glm::vec3 x1, glm::vec3 v1, float time) {

	cout << "compute orbit of " << b1->name_ << " around " << b2->name_ << endl;

	glm::vec3 v = v1 - b2->v(time);
	glm::vec3 r = x1 - b2->x(time);
	
	glm::vec3 x2 = b2->x(time);
	
	cout << "b1->x"
		<< setw(16) << x1[0]
		<< setw(16) << x1[1]
		<< setw(16) << x1[2]
		<< endl;
	cout << "b2->x"
		<< setw(16) << x2[0]
		<< setw(16) << x2[1]
		<< setw(16) << x2[2]
		<< endl;

	glm::vec3 h = glm::cross(r, v);

	float mu = 6.67E-11 * (b1->m_ + b2->m_);

	float specific_orbital_energy = pow(glm::length(v), 2.0) / 2.0 - mu / glm::length(r);

	float a = -mu / 2.0 / specific_orbital_energy;

	float tmp = 2.0 * specific_orbital_energy * pow(glm::length(h), 2.0) / pow(mu, 2.0);
	float e = sqrt(1.0 + tmp);

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
	glm::vec3 E = glm::cross(v, h) / mu - r / glm::length(r);

	float true_anomaly = acos(glm::dot(E, r) / glm::length(E) / glm::length(r));

	if(glm::dot(r, v) < 0.0) true_anomaly = TAU - true_anomaly;

	// orbital plane x
	glm::vec3 x = glm::rotate(r, -true_anomaly, h);
	x = glm::normalize(x);

	plane pl(glm::normalize(h), b2->x(time), x);

	conic* o = 0;

	cout << "v " << glm::length(v) << endl;
	cout << "r " << glm::length(r) << endl;
	cout << "e " << e << endl;

	if(e >= 0.0 && e < 1.0) {
		o = new ellipse(pl, a, sqrt(pow(a, 2) * (1.0 - pow(e, 2))), e);
	} else if(e == 1.0) {
		//o = new parabola(pl, a, e);
	} else if(e > 1.0) {
		//float b = sqrt(pow(a, 2) * (pow(e, 2) - 1.0));
		//o = new hyperbola(pl, a, b, e);
	} else {
		abort();
	}

	assert(o);

	o->b1_ = b1;
	o->b2_ = b2;
	o->h_ = h;
	o->mu_ = mu;
	o->specific_orbital_energy_ = specific_orbital_energy;

	return o;
}

body*		universe::find_parent(body* b1, float time) {
	// determine parent

	for(auto it = bodies_.cbegin(); it != bodies_.cend(); it++) {
		body* b2 = *it;

		glm::vec3 r = b1->x(time) - b2->x(time);

		cout << "check " << b1->name_ << " orbiting " << b2->name_ << endl;
		cout << "r = " << glm::length(r) << " soi = " << b2->soi() << endl;

		if(glm::length(r) < b2->soi()) {
			// for now, assume that all bodies at this level (contained in universe::bodies_) do not overlap soi
			//if(b1->parent_) {
			//	if(b2->soi() > b1->parent_->soi()) continue;
			//}

			// check if b1 is in soi of one of b2's children
			body* b3 = b2->find_parent(b1, time);

			if(b3) return b3;

			return b2;
		}
	}


	return 0;
}
void		universe::insert(body* b1, glm::vec3 x, glm::vec3 v, float time) {

	// in order to calculate position and velocity	
	b1->orbit_ = new orbit_line(x, v, time);


	body* b2 = find_parent(b1, time);

	if(b2) {
		b1->orbit_ = conic::compute(b1, b2, x, v, time);

		cout << b1->name_ << " is orbiting " << b2->name_ << endl;

		b2->children_.push_back(b1);
	} else {
		bodies_.push_back(b1);
	}
}
void		universe::draw(float time) {
	for(auto it = bodies_.cbegin(); it != bodies_.cend(); it++) {
		body* b = *it;
		b->draw(time);
	}
}


