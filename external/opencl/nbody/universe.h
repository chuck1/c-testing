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
		Frame()
		{
		}
		Frame(Frame const & f): bodies_(f.bodies_)
		{
			//printf("%s\n", __PRETTY_FUNCTION__);
		}
		Frame &		operator=(Frame const & f)
		{
			//printf("%s\n", __PRETTY_FUNCTION__);
			bodies_ = f.bodies_;
			return *this;
		}
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
		unsigned int	count_dead()
		{
			unsigned int n = 0;
			for(int i = 0; i < bodies_.size(); i++)
			{
				if(bodies_[i].alive == 0) n++;
			}
			return n;
		}
		unsigned int	count_alive()
		{
			unsigned int n = 0;
			for(int i = 0; i < bodies_.size(); i++)
			{
				if(bodies_[i].alive == 1) n++;
			}
			return n;
		}
		void		write(FILE* pf)
		{
			unsigned int n = bodies_.size();
			fwrite(&n, sizeof(unsigned int), 1, pf);
			fwrite(&bodies_[0], sizeof(Body), n, pf);

			for(int i = 0; i < n; i++)
			{

				printf("%f %f %f\n",
						bodies_[i].x[0],
						bodies_[i].x[1],
						bodies_[i].x[2]);
						
			}
		}
		void		read(FILE* pf)
		{
			unsigned int n;
			fread(&n, sizeof(unsigned int), 1, pf);
			bodies_.resize(n);
			fread(&bodies_[0], sizeof(Body), n, pf);

			for(int i = 0; i < n; i++)
			{
/*
				printf("%f %f %f\n",
						bodies_[i].x[0],
						bodies_[i].x[1],
						bodies_[i].x[2]);
						*/
			}
		}
	public:	
		std::vector<Body>	bodies_;
};
struct Frames
{
	void		write(FILE* pf)
	{
		unsigned int n = frames_.size();
		fwrite(&n, sizeof(unsigned int), 1, pf);
		for(int i = 0; i < n; i++)
		{
			frames_[i].write(pf);
		}
	}
	void		read(FILE* pf)
	{
		unsigned int n;
		fread(&n, sizeof(unsigned int), 1, pf);
		frames_.resize(n);
		for(int i = 0; i < n; i++)
		{
			frames_[i].read(pf);
		}
	}

	std::vector<Frame>	frames_;
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
		unsigned int	count_dead(int t);
		void		add_frame(unsigned int n);
		Frame &		get_frame(int t);
		unsigned int	size(unsigned int t);
		//Body*		bodies_;

		Frames			frames_;

		//std::vector<Body>	_M_bodies;

		std::vector<Pair>	pairs_;

		Map			map_;

		//int			num_bodies_;
		int			num_pairs_;
		int			num_steps_;

		int			first_step_;

		char			name_[32];

		// extra timeseries data
		std::vector<glm::vec3>		mass_center_;

		// read/write
		FILE*		pfile_;
		int		filemode_;
};


#endif
