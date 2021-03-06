
struct Body
{
	public:
		glm::vec3	p;
		glm::vec3	v;
		float		m;
		float		r;
<<<<<<< HEAD
		bool		alive;
};

struct Pair
{
	public:
		Pair(int a, int b): a_(a), b_(b) {}
		int a_;
		int b_;
};

struct Universe
{
	public:
		void alloc()
		{
			bodies = new Body[num_step * num_bodies];
		}
		void write()
		{
			FILE* fp = fopen("bodies.dat", "w");

			fwrite(&num_bodies, sizeof(int), 1, fp);
			fwrite(&num_step, sizeof(int), 1, fp);

			fwrite(bodies, sizeof(Body), num_step * num_bodies, fp);

			fclose(fp);
		}
		void read()
		{
			FILE* fp = fopen("bodies.dat", "r");

			fread(&num_bodies, sizeof(int), 1, fp);
			fread(&num_step, sizeof(int), 1, fp);

			alloc();

			fread(bodies, sizeof(Body), num_step * num_bodies, fp);

			fclose(fp);

		}


		void list(int t)
		{
			for(int i = 0; i < num_bodies; i++)
			{
				printf("%4i alive = %i, r = %f, x = %f %f %f\n",
						i,
						alive(t, i),
						r(t, i),
						p(t, i).x,
						p(t, i).y,
						p(t, i).z);
			}
		}




		Body*			body(int t, int i)
		{
			return &bodies[t * num_bodies + i];
		}

		glm::vec3 const &	p(int t, int i) const
		{
			return bodies[t * num_bodies + i].p;
		}
		glm::vec3 const &	v(int t, int i) const
		{
			return bodies[t * num_bodies + i].v;
		}
		float const &		m(int t, int i) const
		{
			return bodies[t * num_bodies + i].m;
		}
		float const &		r(int t, int i) const
		{
			return bodies[t * num_bodies + i].r;
		}
		bool const &		alive(int t, int i) const
		{
			return bodies[t * num_bodies + i].alive;
		}
		glm::vec3 &		p(int t, int i)
		{
			return bodies[t * num_bodies + i].p;
		}
		glm::vec3 &		v(int t, int i)
		{
			return bodies[t * num_bodies + i].v;
		}
		float &			m(int t, int i)
		{
			return bodies[t * num_bodies + i].m;
		}
		float &			r(int t, int i)
		{
			return bodies[t * num_bodies + i].r;
		}
		bool &			alive(int t, int i)
		{
			return bodies[t * num_bodies + i].alive;
		}

	private:
		Body*		bodies;	
	public:
		int		num_bodies;
		int		num_step;

};

