#ifndef _ENGR_TF_PROP_H
#define _ENGR_TF_PROP_H





namespace Engr
{
	namespace TF
	{
		class Prop
		{
		public:
					Prop(TiXmlElement* root);
			double 	Get();
			double 	Get(string p,double v);
			double 	Get(string p0,double v0,string p1,double v1);
			void	Print();
			void	WriteFluentDatabase(FILE *pFile);
		private:
			string m_name;
			
			vector<shared_ptr<Piece> > m_vecPiece;
		};
	}
}
		Engr::TF::Prop::Prop(TiXmlElement* root) {
	
	const char* c = NULL;
	if ( c = root->Attribute("name") )
	{
		m_name = c;
	}
	
	TiXmlElement* element = root->FirstChildElement("piece");

	while ( element )
	{
		shared_ptr<Piece> p(new Piece(element));
			
		if ( p->Enabled() )
		{
			m_vecPiece.push_back(p);
		}
		
		element = element->NextSiblingElement("piece");
	}
}
double 	Engr::TF::Prop::Get() {
	
	
}
double 	Engr::TF::Prop::Get(string p,double v) {
	for ( int a = 0; a < m_vecPiece.size(); a++ )
	{
		shared_ptr<Piece> piece = m_vecPiece.at(a);
		
		assert( piece );
		
		if ( piece->Check(p,v) )
		{
			return piece->Get(p,v);
		}
	}
	
	assert(0);
	
	return 0;
}
double 	Engr::TF::Prop::Get(string p0,double v0,string p1,double v1) {
	for ( int a = 0; a < m_vecPiece.size(); a++ )
	{
		shared_ptr<Piece> piece = m_vecPiece.at(a);
		
		assert( piece );
		
		if ( piece->Check(p0,v0,p1,v1) )
		{
			return piece->Get(p0,v0,p1,v1);
		}
	}
	
	cout << p0 << "=" << v0 << " " << p1 << "=" << v1 << "\n";
	
	assert(0);
	
	return 0;
}
void	Engr::TF::Prop::Print() {
	cout << "\t" << m_name << endl;
	
	for ( int a = 0; a < m_vecPiece.size(); a++ )
	{
		m_vecPiece.at(a)->Print();
	}
}
void	Engr::TF::Prop::WriteFluentDatabase(FILE *pFile) {
	fprintf (pFile, "\t\t(%s ", m_name.c_str());
	printf ("\t\t(%s ", m_name.c_str());
	
	for ( int a = 0; a < m_vecPiece.size(); a++ )
	{
		m_vecPiece.at(a)->WriteFluentDatabase(pFile);
	}
	
	fprintf (pFile, ")\n");
	printf (")\n");
}


#endif