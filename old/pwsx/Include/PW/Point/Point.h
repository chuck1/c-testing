#ifndef _POINT_H
#define _POINT_H

namespace PW {
	class Connector;
	class CartSet;
	class Point {
	public:
		friend class Connector;
		friend class CartSet;
		Point()
		{
			m_x[0] = 0.0;
			m_x[1] = 0.0;
			m_x[2] = 0.0;
		}
		Point(const Point& p)
		{
			m_x[0] = p.m_x[0];
			m_x[1] = p.m_x[1];
			m_x[2] = p.m_x[2];
		}
		Point(Point* p)
		{
			assert(p);
			
			m_x[0] = p->m_x[0];
			m_x[1] = p->m_x[1];
			m_x[2] = p->m_x[2];
		}
		void Set( int a, double v )
		{
			m_x[a] = v;
		}
		void Increment( int a, double v )
		{
			m_x[a] += v;
		}
		double Get( int a )
		{
			return m_x[a];
		}
	private:
		double m_x[3];
	};
};

#endif







