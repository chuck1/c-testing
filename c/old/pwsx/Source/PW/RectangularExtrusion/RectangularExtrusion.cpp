#include <PW/.h>

PW::RectangularExtrusion::RectangularExtrusion(domain* dom, double length, int i0, int i1, int i2):
	m_length(length), m_i0(i0), m_i1(i1), m_i2(i2)
{
	assert(dom);
	m_do.reset(dom);
}

void PW::RectangularExtrusion::Create()
{
	/*
	connector* 	co1 = m_do->m_c1.get();
	connector* 	co2 = m_do->m_c2.get();
	connector* 	co3 = m_do->m_c3.get();
	connector* 	co4 = m_do->m_c4.get();
	
	point*		po1 = co1->m_begin.get();
	point*		po2 = co1->m_end.get();
	point*		po3 = co3->m_begin.get();
	point*		po4 = co3->m_end.get();
	
	point*		pn1 = new point(po1);
	point*		pn2 = new point(po2);
	point*		pn3 = new point(po3);
	point*		pn4 = new point(po4);
	
	pn1->Increment(m_direction,m_length);
	pn2->Increment(m_direction,m_length);
	pn3->Increment(m_direction,m_length);
	pn4->Increment(m_direction,m_length);
	
	double s = abs(m_length/20.0);
	
	connector* 	cn1 = NULL;
	connector* 	cn2 = NULL;
	connector* 	cn3 = NULL;
	connector* 	cn4 = NULL;
	
	if (m_length>0)
	{
		cn1 = new connector(po1,pn1,s,s,s);
		cn2 = new connector(po2,pn2,s,s,s);
		cn3 = new connector(po3,pn3,s,s,s);
		cn4 = new connector(po4,pn4,s,s,s);
	}
	else
	{
		cn1 = new connector(pn1,po1,s,s,s);
		cn2 = new connector(pn2,po2,s,s,s);
		cn3 = new connector(pn3,po3,s,s,s);
		cn4 = new connector(pn4,po4,s,s,s);
	}
	
	connector* 	cn5 = new connector(pn1,pn2,co1);
	connector* 	cn6 = new connector(pn2,pn4,co2);
	connector* 	cn7 = new connector(pn3,pn4,co3);
	connector* 	cn8 = new connector(pn1,pn3,co4);
	
	domain* 	dn1 = new domain(co1,cn1,cn5,cn2);
	domain* 	dn2 = new domain(co2,cn2,cn6,cn4);
	domain* 	dn3 = new domain(co3,cn3,cn7,cn4);
	domain* 	dn4 = new domain(co4,cn1,cn8,cn3);
	
	domain* 	dn5 = new domain(cn5,cn6,cn7,cn8);
	
	block*		blk = new block(m_do.get(),dn1,dn2,dn3,dn4,dn5);
	*/
	
	m_c1.reset(new connector());
	m_c2.reset(new connector());
	m_c3.reset(new connector());
	m_c4.reset(new connector());
	m_c5.reset(new connector());
	m_c6.reset(new connector());
	m_c7.reset(new connector());
	m_c8.reset(new connector());
	
	m_d1.reset(new domain());
	m_d2.reset(new domain());
	m_d3.reset(new domain());
	m_d4.reset(new domain());
	m_d5.reset(new domain());
	
	m_b.reset(new block());
}

void PW::RectangularExtrusion::Print(ofstream& ofs)
{
	
	int n = 40;
	
	int mode = PW::NextMode();
	int PW = PW::NextPW();
	
	ofs << "set _TMP(mode_" << mode << ") [PW::Application begin Create]" << endl;
	ofs << "  set _TMP(PW_" << PW << ") [PW::FaceStructured createFromDomains [list $_DM(" << m_do->GetDM() << ")]]" << endl;
	ofs << "  set _TMP(face_1) [lindex $_TMP(PW_" << PW << ") 0]" << endl;
	ofs << "  unset _TMP(PW_" << PW << ")" << endl;
	ofs << "  set _TMP(extStrBlock_1) [PW::BlockStructured create]" << endl;
	ofs << "  $_TMP(extStrBlock_1) addFace $_TMP(face_1)" << endl;
	ofs << "$_TMP(mode_" << mode << ") end" << endl;
	ofs << "unset _TMP(mode_" << mode << ")" << endl;
	
	mode = PW::NextMode();
	
	ofs << "set _TMP(mode_" << mode << ") [PW::Application begin ExtrusionSolver [list $_TMP(extStrBlock_1)]]" << endl;
	ofs << "  $_TMP(mode_" << mode << ") setKeepFailingStep true" << endl;
	ofs << "  $_TMP(extStrBlock_1) setExtrusionSolverAttribute Mode Translate" << endl;
	ofs << "  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDirection {" << m_i0 << " " << m_i1 << " " << m_i2 << "}" << endl;
	ofs << "  $_TMP(extStrBlock_1) setExtrusionSolverAttribute TranslateDistance " << m_length << endl;
	ofs << "  $_TMP(mode_" << mode << ") run " << n << endl;
	ofs << "$_TMP(mode_" << mode << ") end" << endl;
	ofs << "unset _TMP(mode_" << mode << ")" << endl;
	ofs << "unset _TMP(extStrBlock_1)" << endl;
	ofs << "unset _TMP(face_1)" << endl;
	ofs << "PW::Application markUndoLevel {Extrude, Translate}" << endl;
	ofs << "" << endl;
	
	m_d1->SetDM(PW::NextDM());
	m_d2->SetDM(PW::NextDM());
	m_d3->SetDM(PW::NextDM());
	m_d4->SetDM(PW::NextDM());
	m_d5->SetDM(PW::NextDM());
	
	m_b->SetBL(PW::NextBL());
	
	ofs << "set _DM(" << m_d1->GetDM() << ") [PW::GridEntity getByName \"dom-" << m_d1->GetDM() << "\"]" << endl;
	ofs << "set _DM(" << m_d2->GetDM() << ") [PW::GridEntity getByName \"dom-" << m_d2->GetDM() << "\"]" << endl;
	ofs << "set _DM(" << m_d3->GetDM() << ") [PW::GridEntity getByName \"dom-" << m_d3->GetDM() << "\"]" << endl;
	ofs << "set _DM(" << m_d4->GetDM() << ") [PW::GridEntity getByName \"dom-" << m_d4->GetDM() << "\"]" << endl;
	ofs << "set _DM(" << m_d5->GetDM() << ") [PW::GridEntity getByName \"dom-" << m_d5->GetDM() << "\"]" << endl;
	
	ofs << "set _BL(" << m_b->GetBL() << ") [PW::GridEntity getByName \"blk-" << m_b->GetBL() << "\"]" << endl;
	ofs << "" << endl;
	
	/*
	m_c1->Print(ofs);
	m_c2->Print(ofs);
	m_c3->Print(ofs);
	m_c4->Print(ofs);
	m_c5->Print(ofs);
	m_c6->Print(ofs);
	m_c7->Print(ofs);
	m_c8->Print(ofs);
	
	m_d1->Print(ofs);
	m_d2->Print(ofs);
	m_d3->Print(ofs);
	m_d4->Print(ofs);
	m_d5->Print(ofs);
	
	m_b->Print(ofs);
	*/
}

