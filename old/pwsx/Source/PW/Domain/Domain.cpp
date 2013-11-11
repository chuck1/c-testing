#include <PW/.h>

void PW::domain::Print(ofstream& ofs)
{
	int PW = PW::NextPW();
	
	ofs << "set _TMP(PW_" << PW << ") [PW::DomainStructured createFromConnectors -reject _TMP(unusedCons) -solid [list $_CN(";
	ofs << m_c1->GetCN() << ") $_CN(";
	ofs << m_c2->GetCN() << ") $_CN(";
	ofs << m_c3->GetCN() << ") $_CN(";
	ofs << m_c4->GetCN() << ")]]" << endl;
	ofs << "unset _TMP(unusedCons)" << endl;
	ofs << "unset _TMP(PW_" << PW << ")" << endl;
	ofs << "PW::Application markUndoLevel {Assemble Blocks}" << endl;
	ofs << endl;
	
	m_DM = PW::NextDM();
	ofs << "set _DM(" << m_DM << ") [PW::GridEntity getByName \"dom-" << m_DM << "\"]" << endl;
	ofs << endl;
	
	if ( ( m_DM % 10 ) == 0 )
	{
		ofs << "puts \"domain " << m_DM << "/" << ( PW::s_nb_domain[0] + PW::s_nb_domain[1] + PW::s_nb_domain[2] ) << " created\"" << endl;
		ofs << endl;
	}
}

