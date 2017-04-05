#include "body.hpp"
#include "conics.hpp"
#include "orbit.hpp"

float		body::soi() {
	conic* c = dynamic_cast<conic*>(orbit_);
	if(c) {
		return c->a_ * pow(m_ / c->b2_->m_, 2.0/5.0);
	} else {
		return numeric_limits<float>::infinity();
	}
}
body*		body::find_parent(body* b1, float time) {
	// determine parent

	for(auto it = children_.cbegin(); it != children_.cend(); it++) {
		body* b2 = *it;

		glm::vec3 r = b1->x(time) - b2->x(time);

		cout << "check " << b1->name_ << " orbiting " << b2->name_ << endl;
		cout << "r = " << glm::length(r) << " soi = " << b2->soi() << endl;

		if(glm::length(r) < b2->soi()) {
			// for now, assume that all bodies at this level (contained in universe::children_) do not overlap soi
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
void		body::draw(float time, glm::vec3 center) {

	glm::vec3 X(x(time) - center);
	
	//cout << "body radius = " << radius_ << endl;
	
	glPushMatrix();
	{
		glTranslatef(X[0], X[1], X[2]);
		glutSolidSphere(radius_, 100, 100);
	}
	glPopMatrix();

	if(orbit_) {
		orbit_->draw(time, center);
	}

	for(auto it = children_.cbegin(); it != children_.cend(); it++) {
		body* b = *it;
		b->draw(time, center);
	}

}
glm::vec3	body::x(float time) {
	if(orbit_) {
		return orbit_->X(time);
	}
	cout << "no orbit" << endl;
	abort();
	return glm::vec3();
}
glm::vec3	body::v(float time) {
	if(orbit_) {
		return orbit_->V(time);
	}
	cout << "no orbit" << endl;
	abort();
	return glm::vec3();
}



