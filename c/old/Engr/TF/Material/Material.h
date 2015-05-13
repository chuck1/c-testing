#ifndef _ENGR_TF_MATERIAL_H
#define _ENGR_TF_MATERIAL_H

#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
#include <map>
#include <memory>
#include <boost/regex.hpp>

using namespace std;

#include "Equation.h"
#include "Piece.h"
#include "Prop.h"


namespace Engr {
	namespace TF {
		class Material {
		public:
					Material(string XMLFile);
					~Material(){}
			
			double 	Get(string s);
			double 	Get(string s,string p,double v);
			double 	Get(string s,string p0,double v0,string p1,double v1);
			void	Print();
			void	WriteFluentDatabase();
			
			double	EnthalpyChange(double T0,double T1,double p0);
		private:
			string 							m_name;
			bool 							m_enabled;
			map<string,shared_ptr<Prop> > 	m_mapProp;
		};
	}
}

double 	Engr::TF::Material::Get(string s) {
	shared_ptr<Prop> prop = m_mapProp[s];
	
	assert ( prop );
	
	return prop->Get();
}
double 	Engr::TF::Material::Get(string s,string p,double v) {
	shared_ptr<Prop> prop = m_mapProp[s];
	
	assert ( prop );
	
	return prop->Get(p,v);
}
double 	Engr::TF::Material::Get(string s, string p0, double v0, string p1, double v1 ) {
	shared_ptr<Prop> prop = m_mapProp[s];
	
	if (!prop) {
		printf ("property '%s' not found in '%s'\n",s.c_str(),m_name.c_str());
		return 0;
	}
	
	return prop->Get(p0,v0,p1,v1);
}
		Engr::TF::Material::Material(string XMLFile) {
	m_enabled = false;
	
	XMLFile = "/nfs/stak/students/r/rymalc/cfs/code/cpp/sunshot/data/material/" + XMLFile + ".xml";
	
	TiXmlDocument document( XMLFile.c_str() );
	if ( !document.LoadFile() )
	{
		printf ("XML file '%s' not found",XMLFile.c_str());
		assert(0);
		return;
	}
	
	const char* c = NULL;
	
	if ( TiXmlElement* root = document.FirstChildElement( "material" ) )
	{
		if ( c = root->Attribute("name") )
		{
			m_name = c;
			m_enabled = true;
			
			TiXmlElement* element = root->FirstChildElement("prop");
			
			while ( element )
			{
				if ( c = element->Attribute("name") )
				{
					shared_ptr<Prop> p(new Prop(element));
					m_mapProp[c] = p;
				}
				
				element = element->NextSiblingElement("prop");
			}
		}
	}
}
void	Engr::TF::Material::Print() {
	cout << m_name << endl;
	
	map<string,shared_ptr<Prop> >::iterator it;
	
	for ( it = m_mapProp.begin(); it!=m_mapProp.end(); ++it )
	{
		it->second->Print();
	}
}
double	Engr::TF::Material::EnthalpyChange(double T0,double T1,double p0) {
	double dh = 0;
	int n = 1000;
	
	matrixD T;
	T.LinSpace(T0,T1,n);
	
	for ( int a = 0; a < n-1; a++ )
	{
		double cp0 = Get( "specific heat", "T", T[a], "p", p0 );
		double cp1 = Get( "specific heat", "T", T[a+1], "p", p0 );
		dh += ( cp0 + cp1 ) / 2 * ( T[a+1] - T[a] );
	}
	
	return dh;
}
void	Engr::TF::Material::WriteFluentDatabase() {
	string filename =
		"/nfs/stak/students/r/rymalc/cfs/code/cpp/sunshot/data/material/"+
		m_name + ".scm";
	
	
	
	FILE *pFile = fopen (filename.c_str(),"w");
	if (!pFile) {
		printf ("error!\n");
		return;
	}
	
	
	
	
	fprintf (pFile, "(\n");
	fprintf (pFile, "\t(%s fluid\n",m_name.c_str());
	fprintf (pFile, "\t\t(chemical-formula . #f)\n");
	printf ("(\n");
	printf ("\t(%s fluid\n",m_name.c_str());
	printf ("\t\t(chemical-formula . #f)\n");
	
	map<string,shared_ptr<Prop> >::iterator it;
	for ( it = m_mapProp.begin(); it!=m_mapProp.end(); ++it ) {
		it->second->WriteFluentDatabase(pFile);
	}
	
	fprintf (pFile, "\t)\n");
	fprintf (pFile, ")\n");
	printf ("\t)\n");
	printf (")\n");
	
	
	fclose (pFile);
}


#endif