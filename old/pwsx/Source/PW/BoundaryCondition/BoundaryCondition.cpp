#include <PW/BoundaryCondition/BoundaryCondition.h>

void PW::BoundaryCondition::Print(ofstream& ofs)
{
	int PW = PW::NextPW();
	
	ofs << "set _TMP(PW_" << PW << ") [PW::BoundaryCondition create]" << endl;
	ofs << "  PW::Application markUndoLevel {Create BC}" << endl;
	ofs << endl;
	ofs << "  $_TMP(PW_" << PW << ") setName \"" << m_name << "\"" << endl;
	ofs << "  PW::Application markUndoLevel {Name BC}" << endl;
	ofs << endl;
	ofs << "  $_TMP(PW_" << PW << ") setPhysicalType {" << GetBCTypeString(m_type) << "}" << endl;
	ofs << "  PW::Application markUndoLevel {Change BC Type}" << endl;
	ofs << endl;
	
	for ( int a = 0; a < m_pairs.size(); a++ )
	{
		shared_ptr<block> blk = m_pairs.at(a).first;
		shared_ptr<domain> dom = m_pairs.at(a).second;
		
		ofs << "  $_TMP(PW_" << PW << ") apply [list [list $_BL(" << blk->GetBL() << ") $_DM(" << dom->GetDM() << ")]]" << endl;
	}
	
	ofs << "  PW::Application markUndoLevel {Set BC}" << endl;
	ofs << endl;
	ofs << "unset _TMP(PW_" << PW << ")" << endl;
	ofs << endl;
	
	m_BC = PW::NextBC();
	
}



string PW::BoundaryCondition::GetBCTypeString( BCType type )
{
	switch (type)
	{
	/*
	case e_INFLOW:
		return "Inflow";
	case e_OUTFLOW:
		return "Outflow";
	case e_SYMMETRY_PLANE:
		return "Symmetry Plane";
	*/
	case e_MASS_FLOW_INLET:
		return "Mass Flow Inlet";
	case e_PRESSURE_OUTLET:
		return "Pressure Outlet";
	case e_SYMMETRY:
		return "Symmetry";
	case e_WALL:
		return "Wall";
	case e_INTERFACE:
		return "Interface";
	default:
		assert(0);
		return "";
	}
}

void PW::BoundaryCondition::AddPair(shared_ptr<block> blk,shared_ptr<domain> dom)
{
	m_pairs.push_back(make_pair(blk,dom));
}
