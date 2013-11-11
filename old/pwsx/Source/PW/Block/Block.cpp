#include <PW/Block/Block.h>

void PW::block::Print(ofstream& ofs)
{
	int PW = PW::NextPW();
	
	ofs << "set _TMP(PW_" << PW << ") [PW::BlockStructured createFromDomains -poleDomains _TMP(poleDoms) -reject _TMP(unusedDoms) [list $_DM(";
	ofs << m_d1->GetDM() << ") $_DM(";
	ofs << m_d2->GetDM() << ") $_DM(";
	ofs << m_d3->GetDM() << ") $_DM(";
	ofs << m_d4->GetDM() << ") $_DM(";
	ofs << m_d5->GetDM() << ") $_DM(";
	ofs << m_d6->GetDM() << ")]]" << endl;
	ofs << "unset _TMP(unusedDoms)" << endl;
	ofs << "unset _TMP(poleDoms)" << endl;
	ofs << "unset _TMP(PW_" << PW << ")" << endl;
	ofs << "PW::Application markUndoLevel {Assemble Blocks}" << endl;
	ofs << endl;
	
	m_BL = PW::NextBL();
	
	ofs << "set _BL(" << m_BL << ") [PW::GridEntity getByName \"blk-" << m_BL << "\"]" << endl;
	ofs << endl;
	
	if ( ( m_BL % 10 ) == 0 )
	{
		ofs << "puts \"block " << m_BL << "/" << PW::s_nb_block << " created\"" << endl;
		ofs << endl;
	}
	
}


