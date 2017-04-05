#ifndef _ENGR_TF_EQUATION_H
#define _ENGR_TF_EQUATION_H

using namespace std;

namespace Engr {
	namespace TF {
		class Equation {
		public:
			virtual double 	Get() = 0;
			virtual double 	Get(string p,double v) = 0;
			virtual double 	Get(string p0,double v0,string p1,double v1) = 0;
			virtual void 	Print() = 0;
			virtual void 	WriteFluentDatabase(FILE *pFile) = 0;
		};
		class Polynomial: public Equation
		{
		public:
					Polynomial(TiXmlElement* root);
			double 	Get();
			double 	Get(string p,double v);
			double 	Get(string p0,double v0,string p1,double v1);
			void 	Print();
			void 	WriteFluentDatabase(FILE *pFile);
		private:
			string 	m_p;
			bool 	m_enabled;
			double* m_a;
			int 	m_n;
		};
		class Constant: public Equation
		{
		public:
					Constant(TiXmlElement* root);
			double 	Get() { return *m_a; }
			double 	Get(string p,double v) { return *m_a; }
			double 	Get(string p0,double v0,string p1,double v1) { return *m_a; }
			void 	Print();
			void 	WriteFluentDatabase(FILE *pFile);
		private:
			bool 	m_enabled;
			double  *m_a;
		};
	}
}

		Engr::TF::Polynomial::Polynomial(TiXmlElement* root) {
	const char* c = NULL;
	m_enabled = true;
	m_n = 0;
	
	if ( c = root->Attribute("prop") )
	{
		m_p = c;
	}
	else
	{
		m_enabled = false;
	}
	
	TiXmlElement* element = NULL;
	
	vector<double> v;
	
	element = root->FirstChildElement("el");
	while ( element )
	{
		if ( ( c = element->GetText() ) )
		{
			v.push_back(atof(c));
			m_n++;
		}
		
		element = element->NextSiblingElement("el");
	}
	
	if ( m_n )
	{
		m_a = new double[m_n];
		
		for ( int a = 0; a < m_n; a++ )
		{
			m_a[a] = v.at(a);
		}
	}
	else
	{
		m_enabled = false;
	}
	
}
double 	Engr::TF::Polynomial::Get() {
	assert(0);
	return 0;
}
double 	Engr::TF::Polynomial::Get(string p,double v) {
	double ret = 0;
	
	for ( int a = 0; a < m_n; a++ )
	{
		ret += m_a[a] * pow( v, a );
	}
}
double 	Engr::TF::Polynomial::Get(string p0,double v0,string p1,double v1) {
	double v = 0;
	if ( strcmp( m_p.c_str(), p0.c_str() ) == 0 )
	{
		v = v0;
	}
	else if ( strcmp( m_p.c_str(), p1.c_str() ) == 0 )
	{
		v = v1;
	}
	else
	{
		assert( 0 );
	}
	
	double ret = 0;
	
	
	for ( int a = 0; a < m_n; a++ )
	{
		ret += m_a[a] * pow( v, a );
	}
}
void 	Engr::TF::Polynomial::Print() {
	for ( int a = 0; a < m_n; a++ )
	{
		cout << "\t\t\t\tm_a[" << a << "]=" << m_a[a] << "\n";
	}
}
void 	Engr::TF::Polynomial::WriteFluentDatabase(FILE *pFile) {
	fprintf (pFile, "(polynomial ");
	printf ("(polynomial ");
	
	for ( int a = 0; a < m_n; a++ )
	{
		fprintf (pFile, "%E",m_a[a]);
		printf ("%E",m_a[a]);
		//cout << "\t\t\t\tm_a[" << a << "]=" << m_a[a] << "\n";
		if (a < (m_n-1)) {
			fprintf (pFile, " ");
			printf (" ");
		}
	}
	
	fprintf (pFile, ")");
	printf (")");
}

		Engr::TF::Constant::Constant(TiXmlElement* root) {
	const char* c = NULL;
	m_enabled = false;
	m_a = 0;
	
	TiXmlElement* element = NULL;
	
	element = root->FirstChildElement("el");
	if ( element ) {
		if ( ( c = element->GetText() ) )
		{
			m_a = new double(atof(c));
			m_enabled = false;
		}
	}
	
}
void 	Engr::TF::Constant::Print() {
	cout << "\t\t\t\tm_a=" << *m_a << "\n";
}
void 	Engr::TF::Constant::WriteFluentDatabase(FILE *pFile) {
	fprintf (pFile, "(constant . %E)",*m_a);
	printf ("(constant . %E)",*m_a);
}

#endif