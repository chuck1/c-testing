#ifndef _CONNECTOR_H
#define _CONNECTOR_H


namespace PW
{
	
	class Connector
	{
	public:
		friend class CartSet;
		friend class RectangularExtrusion;
	public:
		Connector(){m_CN = 0;}
		Connector(Point* p_begin, Point* p_end, double s1, double s2, double s3);
		Connector(Point* p_begin, Point* p_end, Connector* con);
		
		int GetCN(){ return m_CN; }
	private:
		
	public:
		void 				Print(ofstream& ofs);
	private:
		int					m_CN;
		string				m_name;
		
		shared_ptr<Point>	m_begin;
		shared_ptr<Point>	m_end;
		
		double				m_space[3];
		
		static int			s_CN;
	};
	
};



#endif



