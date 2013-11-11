#ifndef _BOUNDARY_CONDITION_H
#define _BOUNDARY_CONDITION_H

namespace PW
{
	
	
	class BoundaryCondition
	{
	public:
							BoundaryCondition(string name, BCType type):
			m_name(name), m_type(type)
		{}
		void				Print(ofstream& ofs);
		string				GetBCTypeString(BCType type);
		void				AddPair(shared_ptr<Block> blk,shared_ptr<domain> dom);
	private:
		int					m_BC;
		string				m_name;
		BCType				m_type;
		
		vector<pair< shared_ptr<Block>, shared_ptr<domain> > >	m_pairs;
	};
	
};


#endif

