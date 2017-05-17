#ifndef _ENGR_TF_PIECE_H
#define _ENGR_TF_PIECE_H


using namespace std;


namespace Engr {
	namespace TF {
		class Range {
		public:
					Range(TiXmlElement* root);
			bool 	Check(double v);
			bool 	Enabled(){ return m_enabled; }
		
			double 	m_min;
			double 	m_max;
		private:
			bool 	m_enabled;
			
		};
		
		class Piece
		{
		public:
					Piece(TiXmlElement* root);
			bool 	Check(string p,double v);
			bool 	Check(string p0,double v0,string p1,double v1);
			bool 	Enabled(){ return m_enabled; }
			double 	Get();
			double 	Get(string p,double v);
			double 	Get(string p0,double v0,string p1,double v1);
			void	Print();
			void	WriteFluentDatabase(FILE *pFile);
		private:
			shared_ptr<Equation> 			m_e;
			bool							m_enabled;
			map<string,shared_ptr<Range> > 	m_mapRange;
		};
	}
}

		Engr::TF::Range::Range(TiXmlElement* root) {
	const char* c = NULL;
	m_enabled = true;
	
	TiXmlElement* element = NULL;
	
	if ( element = root->FirstChildElement("min") )
	{
		if ( c = element->GetText() )
		{
			m_min = atof(c);
		}
		else
		{
			m_enabled = false;
		}
	}
	
	if ( element = root->FirstChildElement("max") )
	{
		if ( c = element->GetText() )
		{
			m_max = atof(c);
		}
		else
		{
			m_enabled = false;
		}
	}
}
bool 	Engr::TF::Range::Check(double v) {
	return ( ( v >= m_min ) && ( v <= m_max ) );
}


		Engr::TF::Piece::Piece(TiXmlElement* root) {
	m_enabled = true;
	
	map<string,int> mapEquationType;
	
	mapEquationType["poly"] = 1;
	mapEquationType["const"]= 2;
	
	const char* c = NULL;
	
	TiXmlElement* element = NULL;
	
	element = root->FirstChildElement("range");
	while ( element )
	{
		shared_ptr<Range> r(new Range(element));
		
		if ( ( c = element->Attribute("name") ) && ( r->Enabled() ) )
		{
			m_mapRange[c] = r;
		}
		
		element = element->NextSiblingElement("range");
	}
	
	element = root->FirstChildElement("equation");
	if ( element )
	{
		if ( c = element->Attribute("type") )
		{
			int a = mapEquationType[c];
			switch ( a )
			{
			case 1:
				m_e.reset(new Polynomial(element));
				break;
			case 2:
				m_e.reset(new Constant(element));
				break;
			default:
				m_enabled = false;
			}
		}
	}
}
bool 	Engr::TF::Piece::Check(string p,double v) {
	shared_ptr<Range> r = m_mapRange[p];
	
	assert( r );
	
	return r->Check(v);
}
bool 	Engr::TF::Piece::Check(string p0,double v0,string p1,double v1) {
	shared_ptr<Range> r0 = m_mapRange[p0];
	
	assert( r0 );
	
	shared_ptr<Range> r1 = m_mapRange[p1];
	
	assert( r1 );
	
	return ( ( r0->Check(v0) ) && ( r1->Check(v1) ) );
}
double 	Engr::TF::Piece::Get() {
	assert( m_e );
	return m_e->Get();
}
double 	Engr::TF::Piece::Get(string p,double v) {
	assert( m_e );
	return m_e->Get(p,v);
}
double 	Engr::TF::Piece::Get(string p0,double v0,string p1,double v1) {
	assert( m_e );
	return m_e->Get(p0,v0,p1,v1);
}
void 	Engr::TF::Piece::Print() {
	cout << "\t\tpiece\n";
	
	map<string,shared_ptr<Range> >::iterator it;
	
	for ( it = m_mapRange.begin(); it!=m_mapRange.end(); ++it )
	{
		cout << "\t\t\trange " << it->first << "\n\t\t\t\tmin=" << it->second->m_min << "\n\t\t\t\tmax=" << it->second->m_max << "\n";
	}
	
	m_e->Print();
}
void 	Engr::TF::Piece::WriteFluentDatabase(FILE *pFile) {
	/*
	map<string,shared_ptr<Range> >::iterator it;
	
	for ( it = m_mapRange.begin(); it!=m_mapRange.end(); ++it )
	{
		cout << "\t\t\trange " << it->first << "\n\t\t\t\tmin=" << it->second->m_min << "\n\t\t\t\tmax=" << it->second->m_max << "\n";
	}
	*/
	m_e->WriteFluentDatabase(pFile);
}

#endif