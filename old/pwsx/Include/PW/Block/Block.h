#ifndef _BLOCK_H
#define _BLOCK_H

namespace PW
{
	class domain;
	class VolumeCondition;
	
	class Block
	{
	public:
		friend class CartSet;
	public:
		Block()
		{
			m_BL = 0;
		}
		Block(domain* d1,domain* d2,domain* d3,domain* d4,domain* d5,domain* d6)
		{
			m_BL = 0;
			
			m_d1.reset(d1);
			m_d2.reset(d2);
			m_d3.reset(d3);
			m_d4.reset(d4);
			m_d5.reset(d5);
			m_d6.reset(d6);
		}
		int GetBL()
		{
			return m_BL;
		}
		void SetBL(int a)
		{
			m_BL = a;
		}
		void Print(ofstream& ofs);
		void SetVC(VolumeCondition* vc) { m_vc = vc; }
		VolumeCondition* GetVC()
		{
			return m_vc;
		}
	private:
		int					m_BL;
		shared_ptr<domain>	m_d1;
		shared_ptr<domain>	m_d2;
		shared_ptr<domain>	m_d3;
		shared_ptr<domain>	m_d4;
		shared_ptr<domain>	m_d5;
		shared_ptr<domain>	m_d6;
		
		VolumeCondition*	m_vc;
	};
};

#endif