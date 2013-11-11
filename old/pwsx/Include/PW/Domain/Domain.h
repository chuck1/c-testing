#ifndef _DOMAIN_H
#define _DOMAIN_H

namespace PW
{
	
	class domain
	{
	public:
		friend class CartSet;
		friend class RectangularExtrusion;
	public:
		domain()
		{
			m_DM = 0;
		}
		domain(Connector* c1,Connector* c2,Connector* c3,Connector* c4)
		{
			m_DM = 0;
			
			m_c1.reset(c1);
			m_c2.reset(c2);
			m_c3.reset(c3);
			m_c4.reset(c4);
		}
		int GetDM()
		{
			return m_DM;
		}
		void SetDM(int a)
		{
			m_DM = a;
		}
		void Print(ofstream& ofs);
	private:
		int						m_DM;
		shared_ptr<Connector>	m_c1;
		shared_ptr<Connector>	m_c2;
		shared_ptr<Connector>	m_c3;
		shared_ptr<Connector>	m_c4;
	};
	
};


#endif

