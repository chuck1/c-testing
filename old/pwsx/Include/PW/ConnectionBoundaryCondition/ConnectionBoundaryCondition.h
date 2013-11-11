#ifndef _CONNECTION_BOUNDARY_CONDITION_H
#define _CONNECTION_BOUNDARY_CONDITION_H


namespace PW
{
	
	class ConnectionBoundaryCondition
	{
	public:
							ConnectionBoundaryCondition(string name, BCType type):
			m_name(name), m_type(type)
		{}
		void				Print(ofstream& ofs);
		string				GetBCTypeString(BCType type);
		void				AddTriple(shared_ptr<Block> same,shared_ptr<Block> opposite,shared_ptr<domain> dom);
	private:
		int					m_BC;
		string				m_name;
		BCType				m_type;
		
		vector<tuple< shared_ptr<Block>, shared_ptr<Block>, shared_ptr<domain> > >	m_triples;
	};	
}


#endif

