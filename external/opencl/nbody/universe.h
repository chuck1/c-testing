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

struct Frame
{
	public:
		Body*		b(int i)
		{
			assert(bodies_.size() > i);
			return &bodies_[0];

		}
		void		alloc(int n)
		{
			bodies_.resize(n);
		}
		void		copy(Body* b, int n);
		void		reduce();

	private:	
		std::vector<Body>	bodies_;
};

struct Universe
{
	public:
		Universe();
		Body*		b(int t);
		Body*		b(int t, int i);
		int		solve();
		void		alloc(int num_bodies, int num_steps);
		void		random(float m);
		int		mass_center(int t, float * x, float * s);
		void		spin(float m);
		void		write();
		int		read(std::string fileName = std::string("data.dat"), int num_steps = 0);
		void		rw_header();
		void		operator&(int i);
		void		stats();
		unsigned int	count_alive(int t);
		void		add_frame(unsigned int n);

		//Body*		bodies_;

		std::vector<Frame>	frames_;

		//std::vector<Body>	_M_bodies;

		std::vector<Pair>	pairs_;

		Map			map_;

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
