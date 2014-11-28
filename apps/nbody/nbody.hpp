
struct Universe
{
	public:
		void alloc()
		{
			position = new glm::vec3[num_step * num_bodies];
			velocity = new glm::vec3[num_step * num_bodies];
			mass = new float[num_step * num_bodies];
		}
		void write()
		{
			FILE* fp = fopen("bodies.dat", "w");

			fwrite(&num_bodies, sizeof(int), 1, fp);
			fwrite(&num_step, sizeof(int), 1, fp);

			fwrite(position, sizeof(glm::vec3), num_step * num_bodies, fp);
			fwrite(velocity, sizeof(glm::vec3), num_step * num_bodies, fp);
			fwrite(mass, sizeof(float), num_step * num_bodies, fp);

			fclose(fp);
		}
		void read()
		{
			FILE* fp = fopen("bodies.dat", "r");

			fread(&num_bodies, sizeof(int), 1, fp);
			fread(&num_step, sizeof(int), 1, fp);

			alloc();

			fread(position, sizeof(glm::vec3), num_step * num_bodies, fp);
			fread(velocity, sizeof(glm::vec3), num_step * num_bodies, fp);
			fread(mass, sizeof(float), num_step * num_bodies, fp);

			fclose(fp);
		}

		glm::vec3&	p(int t, int i)
		{
			return position[t * num_bodies + i];
		}
		glm::vec3&	v(int t, int i)
		{
			return velocity[t * num_bodies + i];
		}
		float&		m(int t, int i)
		{
			return mass[t * num_bodies + i];
		}

	private:	
		glm::vec3*	position;
		glm::vec3*	velocity;
		float*		mass;
	public:
		int		num_bodies;
		int		num_step;

};

