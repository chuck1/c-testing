#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cassert>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "body.h"

#define FILEMODE_WRITE 0
#define FILEMODE_READ 0

float radius(float m);


struct Universe
{
	Universe();
	Body*		b(int t);
	Body*		b(int t, int i);
	int		solve();
	void		alloc(int num_bodies, int num_steps);
	void		random(float m);
	int		mass_center(int t, float * x, float * s);
	void		spin(float m);
	void		free()
	{
		//delete[] bodies_;
		delete[] pairs_;
	}
	void		write();
	int		read(std::string fileName = std::string("data.dat"), int num_steps = 0);
	void		rw_header();
	void		operator&(int i);
	void		stats();

	//Body*		bodies_;
	std::vector<Body>	bodies_;
	Map		map_;
	Pair*		pairs_;

	int		num_bodies_;
	int		num_pairs_;
	int		num_steps_;

	int		first_step_;

	char		name_[32];

	// extra timeseries data
	std::vector<glm::vec3>		mass_center_;

	// read/write
	FILE*		pfile_;
	int		filemode_;
};


#endif
