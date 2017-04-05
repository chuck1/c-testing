
#include <glm/glm.hpp>

struct Line
{
	glm::vec3	p1;
	glm::vec3	p2;
};
struct Ray
{
	glm::vec3	at(float f)
	{
		return p + d * f;
	}
	glm::vec3	p;
	glm::vec3	d;
};
Line		closest(Ray r1, Ray r2)
{
	glm::vec3 w0 = r1.p - r2.p;

	float a = glm::dot(r1.d, r1.d);
	float b = glm::dot(r1.d, r2.d);
	float c = glm::dot(r2.d, r2.d);
	float d = glm::dot(r1.d, w0);
	float e = glm::dot(r2.d, w0);
	
	float sc = (b*e - c*d)/(a*c - b*b);
	float tc = (a*e - b*d)/(a*c - b*b);
	
	Line l;
	l.p1 = r1.at(sc);
	l.p2 = r2.at(tc);

	return l;
}

struct Camera
{
	Ray		get_ray(glm::vec2 p1);
	glm::vec3	pos;
	// normalized axes corresponding to opengl convention
	glm::vec3	x;
	glm::vec3	y;
	glm::vec3	z;
};
struct Pose
{
	glm::vec3	p;
	glm::quat	q;
};
struct Frame
{
	// this frame is composed of three points fixed relative to each other
	// one point is defined as at the frame's origin
	// one is defined as along the -z axis
	// the relative position of the other is stored in the 'p' data member
	
	// get global pose of the frame based on the global position of the three points
	Pose		get_pose(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	{

		Pose pose;

		return pose;
	}
	glm::vec3	p;
};
struct Mocap
{
	void		calibrate(glm::vec2 p1[3], glm::vec2 p2[3])
	{

	}
	glm::vec3	get_position(glm::vec2 p1, glm::vec2 p2)
	{
		Ray r1 = cam1.get_ray(p1);
		Ray r2 = cam2.get_ray(p2);
	}

	Camera cam1;
	Camera cam2;
};



int main()
{
	Mocap mocap;

	// calibrate camera positions using 3 points
	// points from cam1
	glm::vec2 p1[3];
	// points from cam2
	glm::vec2 p2[3];
	
	mocap.calibrate(p1,p2);
	
	
	return 0;
}


