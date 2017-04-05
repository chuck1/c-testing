#include <PW/.h>

void 	PW::ConnectionBoundaryCondition::Print(ofstream& ofs) {
	int PW = PW::NextPW();
	
	
	ofs << "set _TMP(PW_" << PW << ") [PW::BoundaryCondition create]" << endl;
	ofs << "  PW::Application markUndoLevel {Create BC}" << endl;
	ofs << "" << endl;
	ofs << "  $_TMP(PW_" << PW << ") setName \"" << m_name << "\"" << endl;
	ofs << "  PW::Application markUndoLevel {Name BC}" << endl;
	ofs << "" << endl;
	ofs << "  $_TMP(PW_" << PW << ") setPhysicalType {" << GetBCTypeString(m_type) << "}" << endl;
	ofs << "  PW::Application markUndoLevel {Change BC Type}" << endl;
	ofs << "" << endl;
	
	for ( int a = 0; a < m_triples.size(); a++ )
	{
		shared_ptr<block> same = 		get<0>(m_triples.at(a));
		shared_ptr<block> opposite = 	get<1>(m_triples.at(a));
		shared_ptr<domain> dom = 		get<2>(m_triples.at(a));
		
		ofs << "  $_TMP(PW_" << PW << ") apply [list [list $_BL(" << same->GetBL() << ") $_DM(" << dom->GetDM() << ") Same] [list $_BL(" << opposite->GetBL() << ") $_DM(" << dom->GetDM() << ") Opposite]]" << endl;
	}
	
	ofs << "  PW::Application markUndoLevel {Set BC}" << endl;
	ofs << "" << endl;
	ofs << "unset _TMP(PW_" << PW << ")" << endl;
	ofs << "" << endl;
	
	m_BC = PW::NextBC();
}
string 	PW::ConnectionBoundaryCondition::GetBCTypeString( BCType type ) {
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
void 	PW::ConnectionBoundaryCondition::AddTriple(shared_ptr<block> same, shared_ptr<block> opposite, shared_ptr<domain> dom) {
	m_triples.push_back(make_tuple(same,opposite,dom));
}











