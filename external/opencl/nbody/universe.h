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
void	print(float * x);

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
		Frame &			operator=(Frame const & f)
		{
			//printf("%s\n", __PRETTY_FUNCTION__);
			bodies_ = f.bodies_;
			return *this;
		}
		Body*			b(unsigned int i)
		{
			assert(bodies_.size() > i);
			return &bodies_[i];
		}
		unsigned int		size() const
		{
			return bodies_.size();
		}
		void			alloc(int n)
		{
			bodies_.resize(n);
		}
		int			try_insert(
				float * x,
				float a0,
				float a1,
				float a2,
				float (*f0)(float),
				float (*f1)(float),
				float (*f2)(float),
				float radius,
				unsigned int idx);
		void			copy(Body* b, int n);
		unsigned int		reduce();
		void			random(float m, float w, float v);
		void			spin(float m, float w);
		void			rings(float m, float w);
		unsigned int	count_dead()
		{
			unsigned int n = 0;
			for(unsigned int i = 0; i < bodies_.size(); i++)
			{
				if(bodies_[i].alive == 0) n++;
			}
			return n;
		}
		unsigned int	count_alive()
		{
			unsigned int n = 0;
			for(unsigned int i = 0; i < bodies_.size(); i++)
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

		}
		void		read(FILE* pf)
		{
			unsigned int n;
			fread(&n, sizeof(unsigned int), 1, pf);
			bodies_.resize(n);
			fread(&bodies_[0], sizeof(Body), n, pf);

			//print();
		}
		void		print();
		glm::vec3	body_max()
		{
			glm::vec3 e(FLT_MIN);

			for(Body & b : bodies_)
			{
				if(b.alive)
				{
					e.x = std::max(e.x, b.x[0]);
					e.y = std::max(e.y, b.x[1]);
					e.z = std::max(e.z, b.x[2]);
				}
			}

			return e;
		}

		glm::vec3	body_min()
		{
			glm::vec3 e(FLT_MAX);

			for(Body & b : bodies_)
			{
				if(b.alive)
				{
					e.x = std::min(e.x, b.x[0]);
					e.y = std::min(e.y, b.x[1]);
					e.z = std::min(e.z, b.x[2]);
				}
			}

			return e;
		}
		int		mass_center(float * x, float * s)
		{
			float temp[3] = {0,0,0};

			float m = 0;

			for(Body & b : bodies_)
			{
				if(b.alive)
				{
					temp[0] += b.x[0] * b.mass;
					temp[1] += b.x[1] * b.mass;
					temp[2] += b.x[2] * b.mass;

					m += b.mass;
				}
			}

			temp[0] /= m;
			temp[1] /= m;
			temp[2] /= m;

			if(x)
			{
				x[0] = temp[0];
				x[1] = temp[1];
				x[2] = temp[2];
			}

			// weighted std

			if(s)
			{
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;

				for(Body & b : bodies_)
				{
					if(b.alive)
					{
						temp[0] += b.mass * pow(b.x[0] - x[0], 2);
						temp[1] += b.mass * pow(b.x[1] - x[1], 2);
						temp[2] += b.mass * pow(b.x[2] - x[2], 2);
					}
				}

				s[0] = sqrt(temp[0] / m);
				s[1] = sqrt(temp[1] / m);
				s[2] = sqrt(temp[2] / m);
			}

			return 0;
		}

	public:	
		std::vector<Body>	bodies_;
};
struct Frames
{
	Frames() {}
	Frames(Frames const & f): frames_(f.frames_)
	{
	}
	Frames &	operator=(Frames const & f)
	{
		frames_ = f.frames_;
		return *this;
	}
	void		write(FILE* pf)
	{
		unsigned int n = frames_.size();
		fwrite(&n, sizeof(unsigned int), 1, pf);
		for(unsigned int i = 0; i < n; i++)
		{
			frames_[i].write(pf);
		}
	}
	void		read(FILE* pf)
	{
		unsigned int n;
		fread(&n, sizeof(unsigned int), 1, pf);
		frames_.resize(n);
		for(unsigned int i = 0; i < n; i++)
		{
			frames_[i].read(pf);
		}
	}

	std::vector<Frame>	frames_;
};
struct Pairs
{
	void			init(Frame const & f)
	{
		assert(f.size() > 0);

		int k = 0;

		unsigned int nb = f.size();



		map_.alloc(nb);

		pairs_.resize(nb * (nb - 1) / 2);

		for(unsigned int i = 0; i < nb; i++)
		{
			for(unsigned int j = i + 1; j < nb; j++)
			{

				pairs_[k].b0 = i;
				pairs_[k].b1 = j;

				map_.pair_[i * nb + j] = k;
				map_.pair_[j * nb + i] = k;

				k++;
			}
		}
	}
	unsigned int		size() const
	{
		return pairs_.size();
	}
	std::vector<Pair>	pairs_;
	Map			map_;
};
struct Universe
{
	public:
		Universe();
		Body*			b(int t);
		Body*			b(int t, int i);
		int			solve();
		void			alloc(int num_bodies, int num_steps);
		int			mass_center(int t, float * x, float * s);
		void			write();
		int			read(std::string fileName = std::string("data.dat"), int num_steps = 0);
		void			rw_header();
		void			operator&(int i);
		void			stats();
		unsigned int		count_alive(int t);
		unsigned int		count_dead(int t);
		void			add_frame(unsigned int n);
		Frame &			get_frame(int t);
		unsigned int		size(unsigned int t);
		std::string		getFilename();


	public:
		Frames			frames_;

		static const unsigned int	NAME_SIZE = 32;

		int			num_steps_;

		int			first_step_;

		char			name_[NAME_SIZE];

		// extra timeseries data
		std::vector<glm::vec3>		mass_center_;

		// read/write
		FILE*		pfile_;
		int		filemode_;
};


#endif
