#include <PW/.h>

PW::connector::connector(point* p_begin, point* p_end, double s1, double s2, double s3)
{
	m_CN = 0;
	
	m_space[0] = s1;
	m_space[1] = s2;
	m_space[2] = s3;
	
	m_begin.reset(p_begin);
	m_end.reset(p_end);
}

PW::connector::connector(point* p_begin, point* p_end, connector* con)
{
	m_CN = 0;
	
	m_space[0] = con->m_space[0];
	m_space[1] = con->m_space[1];
	m_space[2] = con->m_space[2];
	
	m_begin.reset(p_begin);
	m_end.reset(p_end);
}


void PW::connector::Print(ofstream& ofs)
{
	int mode = PW::NextMode();
	int PW = PW::NextPW();
	int con = 1;
	
	double x1 = m_begin->Get(0);
	double y1 = m_begin->Get(1);
	double z1 = m_begin->Get(2);
	double x2 = m_end->Get(0);
	double y2 = m_end->Get(1);
	double z2 = m_end->Get(2);
	
	if ( m_space[1] != PW::PW::s_space )
	{
		PW::PW::s_space = m_space[1];
		
		ofs << "PW::Connector setCalculateDimensionMethod Spacing" << endl;
		ofs << "PW::Connector setCalculateDimensionSpacing " << PW::PW::s_space << endl;
		ofs << endl;
	}
	
	ofs << "set _TMP(mode_" << mode << ") [PW::Application begin Create]" << endl;
	ofs << "  set _TMP(PW_" << PW << ") [PW::SegmentSpline create]" << endl;
	ofs << "  $_TMP(PW_" << PW << ") addPoint {" << x1 << " " << y1 << " " << z1 << "}" << endl;
	ofs << "  $_TMP(PW_" << PW << ") addPoint {" << x2 << " " << y2 << " " << z2 << "}" << endl;
	ofs << "  set _TMP(con_" << con << ") [PW::Connector create]" << endl;
	ofs << "  $_TMP(con_" << con << ") addSegment $_TMP(PW_" << PW << ")" << endl;
	ofs << "  unset _TMP(PW_" << PW << ")" << endl;
	ofs << "  $_TMP(con_" << con << ") calculateDimension" << endl;
	ofs << "$_TMP(mode_" << mode << ") end" << endl;
	ofs << "unset _TMP(mode_" << mode << ")" << endl;
	ofs << "PW::Application markUndoLevel {Create 2 Point Connector}" << endl;
	ofs << "unset _TMP(con_" << con << ")" << endl;
	ofs << endl;
	
	m_CN = PW::NextCN();
	ofs << "set _CN(" << m_CN << ") [PW::GridEntity getByName \"con-" << m_CN << "\"]" << endl;
	ofs << endl;
	
	mode = PW::NextMode();
	PW = PW::NextPW();
	
	ofs << "set _TMP(mode_" << mode << ") [PW::Application begin Modify [list $_CN(" << m_CN << ")]]" << endl;
	ofs << "  set _TMP(PW_" << PW << ") [$_CN(" << m_CN << ") getDistribution 1]" << endl;
	ofs << "  $_TMP(PW_" << PW << ") setBeginSpacing " << m_space[0] << endl;
	ofs << "  unset _TMP(PW_" << PW << ")" << endl;
	ofs << "$_TMP(mode_" << mode << ") end" << endl;
	ofs << "unset _TMP(mode_" << mode << ")" << endl;
	ofs << "PW::Application markUndoLevel {Change Spacing(s)}" << endl;
	ofs << endl;
	
	PW = PW::NextPW();
	
	ofs << "set _TMP(mode_" << mode << ") [PW::Application begin Modify [list $_CN(" << m_CN << ")]]" << endl;
	ofs << "  set _TMP(PW_" << PW << ") [$_CN(" << m_CN << ") getDistribution 1]" << endl;
	ofs << "  $_TMP(PW_" << PW << ") setEndSpacing " << m_space[2] << endl;
	ofs << "  unset _TMP(PW_" << PW << ")" << endl;
	ofs << "$_TMP(mode_" << mode << ") end" << endl;
	ofs << "unset _TMP(mode_" << mode << ")" << endl;
	ofs << "PW::Application markUndoLevel {Change Spacing(s)}" << endl;
	ofs << endl;
	
	
	
	if ( ( m_CN % 10 ) == 0 )
	{
		ofs << "puts \"connector " << m_CN << "/" << (PW::s_nb_connector[0]+PW::s_nb_connector[1]+PW::s_nb_connector[2]) << " created\"" << endl;
		ofs << endl;
	}
	
}












