#ifndef _RECTANGULAR_EXTRUSION_H
#define _RECTANGULAR_EXTRUSION_H

namespace PW
{
	
	class RectangularExtrusion
	{
	public:
		RectangularExtrusion(Domain* dom, double length, int i0, int i1, int i2 );
		void Create();
		void Print(ofstream& ofs);
		shared_ptr<Domain> Getd4()
		{
			return m_d4;
		}
		shared_ptr<Domain> Getd5()
		{
			return m_d5;
		}
		shared_ptr<Block> Getb()
		{
			return m_b;
		}
	private:
		int					m_i0;
		int					m_i1;
		int					m_i2;
		
		double				m_length;
		
		shared_ptr<Domain>	m_do;
		
		shared_ptr<Connector>	m_c1;
		shared_ptr<Connector>	m_c2;
		shared_ptr<Connector>	m_c3;
		shared_ptr<Connector>	m_c4;
		shared_ptr<Connector>	m_c5;
		shared_ptr<Connector>	m_c6;
		shared_ptr<Connector>	m_c7;
		shared_ptr<Connector>	m_c8;
		
		shared_ptr<Domain>	m_d1;
		shared_ptr<Domain>	m_d2;
		shared_ptr<Domain>	m_d3;
		shared_ptr<Domain>	m_d4;
		shared_ptr<Domain>	m_d5;
		
		shared_ptr<Block>	m_b;
	};
	
};


#endif



