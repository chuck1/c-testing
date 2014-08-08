
#include "conics.hpp"

int	main() {
	body earth(glm::vec3(0,0,0), glm::vec3(0,0,0), 5.97219E+24);
	body ship(glm::vec3(6371.0E3 + 417.0E3, 0, 0), glm::vec3(0, 7.65E3, 0), 1000.0);

	orbit o;
	o.compute(ship, earth);

	cout << "e   " << o.e_ << endl;
	cout << "mu  " << o.mu_ << endl;
	cout << "soe " << o.specific_orbital_energy_ << endl;
	cout << "h   " << glm::length(o.h_) << endl;

	cout
		<< setw(16) << earth.x_[0]
		<< setw(16) << earth.x_[1]
		<< setw(16) << earth.x_[2]
		<< endl;
	cout
		<< setw(16) << ship.x_[0]
		<< setw(16) << ship.x_[1]
		<< setw(16) << ship.x_[2]
		<< endl;

	return 0;
}
