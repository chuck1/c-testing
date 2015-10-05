#include <PW/Point/Point.h>

		Point::point() {
	m_x[0] = 0.0;
	m_x[1] = 0.0;
	m_x[2] = 0.0;
}
		Point::point(const point& p) {
	m_x[0] = p.m_x[0];
	m_x[1] = p.m_x[1];
	m_x[2] = p.m_x[2];
}
		Point::point(point* p) {
	assert(p);
	
	m_x[0] = p->m_x[0];
	m_x[1] = p->m_x[1];
	m_x[2] = p->m_x[2];
}
void 	Point::Set( int a, double v ) {
	m_x[a] = v;
}
void 	Point::Increment( int a, double v ) {
	m_x[a] += v;
}
double 	Point::Get( int a ) {
	return m_x[a];
}









