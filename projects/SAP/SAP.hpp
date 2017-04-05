#ifndef SAP_HPP
#define SAP_HPP

#include <glm/glm.hpp>

class Edge;

class EdgeCompare
{
	public:
		bool	operator()(Edge* a, Edge* b)
}

class SAP
{
	public:
		std::set<Edge*, EdgeCompare>	_M_x;
		std::set<Edge*, EdgeCompare>	_M_y;
		std::set<Edge*, EdgeCompare>	_M_z;
};

class Object
{
	public:
		glm::vec3	_M_x;
}

class AABB
{
	public:
		Object*		_M_parent;
};

/**
 * the edge of a bonding box
 */
class Edge
{
	public:
		virtual float	value() = 0;
		SAP*		_M_parent;
		AABB*		_M_box;
};

class EdgeX
{
	public:
		virtual float	value();
};
class EdgeY
{
	public:
		virtual float	value();
};
class EdgeZ
{
	public:
		virtual float	value();
};

float	EdgeX::value()
{
	return _M_box->_M_parent
bool	EdgeCompare::operator()(Edge* a, Edge* b)
{
	return a->x < b->_M_x;
}

#endif

