

#include <GL/glut.h>

#include "universe.hpp"
#include "body.hpp"
#include "conics.hpp"
#include "ellipse.hpp"

universe* g_universe = new universe;
body* g_body_focus = 0;



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


