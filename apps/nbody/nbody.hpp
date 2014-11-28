
struct Body
{
	public:
		glm::vec3	p;
		glm::vec3	v;
		float		m;
		float		r;
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

		void			setp(int t, int i, glm::vec3 && x)
		{
			bodies[t * num_bodies + i].p = x;
		}
		void			setv(int t, int i, glm::vec3 && x)
		{
			bodies[t * num_bodies + i].v = x;
		}
		void			setm(int t, int i, float && x)
		{
			bodies[t * num_bodies + i].m = x;
		}
		void			setr(int t, int i, float && x)
		{
			bodies[t * num_bodies + i].r = x;
		}
		void			setp(int t, int i, glm::vec3 const & x)
		{
			bodies[t * num_bodies + i].p = x;
		}
		void			setv(int t, int i, glm::vec3 const & x)
		{
			bodies[t * num_bodies + i].v = x;
		}
		void			setm(int t, int i, float const & x)
		{
			bodies[t * num_bodies + i].m = x;
		}
		void			setr(int t, int i, float const & x)
		{
			bodies[t * num_bodies + i].r = x;
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

	private:
		Body*		bodies;	
/*		glm::vec3*	bodies;
		glm::vec3*	bodies;
		float*		bodies;
		float*		radius;*/
	public:
		int		num_bodies;
		int		num_step;

};

