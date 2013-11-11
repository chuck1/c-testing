#ifndef _SPACING_H
#define _SPACING_H

namespace PW
{
	class Spacing
	{
	public:
		Spacing( TiXmlElement* element );
		
		void ParseDim(TiXmlElement* dim_element);
		void ParseLength(TiXmlElement* length_element);
		
		string m_name;
		bool m_enabled;
		int* m_dimension[3]; // begin, mid, end
		double m_spacing[3];
		double* m_length;
		map<string,int> map_dim_name;
	};
};

PW::Spacing::Spacing( TiXmlElement* element ) {
	m_dimension[0] = NULL;
	m_dimension[1] = NULL;
	m_dimension[2] = NULL;
	
	
	
	map_dim_name["begin"] = 1;
	map_dim_name["mid"] = 	2;
	map_dim_name["end"] = 	3;
	
	
	const char* c = NULL;
	
	if ( c = element->Attribute("name") )
	{
		m_name = c;
		
		TiXmlElement* dim_element = element->FirstChildElement( "Dim" );
		
		while ( dim_element )
		{
			ParseDim(dim_element);
			dim_element = dim_element->NextSiblingElement( "Dim" );
		}
		
		TiXmlElement* length_element = element->FirstChildElement( "Length" );
		
		while ( length_element )
		{
			ParseLength(length_element);
			length_element = length_element->NextSiblingElement( "Length" );
		}
	}
	
	
	
	
	
	
	if ( !m_dimension[1] )
	{
		cout << "Spacing invalid: m_dimension[1] not set" << endl;
		m_enabled = false;
	}
	else if ( !m_length )
	{
		cout << "Spacing invalid: m_length not set" << endl;
		m_enabled = false;
	}
	else
	{
		cout << "Spacing created" << endl;
		//cout << "    length = " << *m_length << endl;
		//cout << "    begin = " << *m_dimension[0] << endl;
		//cout << "    mid   = " << *m_dimension[1] << endl;
		//cout << "    end   = " << *m_dimension[2] << endl;
		
		
		m_spacing[0] = (*m_length)/(*m_dimension[0]);
		m_spacing[1] = (*m_length)/(*m_dimension[1]);
		m_spacing[2] = (*m_length)/(*m_dimension[2]);
		
		m_enabled = true;
	}
}

void PW::Spacing::ParseDim(TiXmlElement* dim_element)
{
	const char* c = NULL;
	string name, text;
	
	if ( c = dim_element->Attribute("name") )
	{
		name = c;
		//cout << "Dim element name=" << name << endl;
		
		if ( c = dim_element->GetText() )
		{
			text = c;
			
			if ( !text.empty() )
			{
				switch ( map_dim_name[name] )
				{
				case 1:
					m_dimension[0] = new int;
					*m_dimension[0] = atoi(text.c_str());
					break;
				case 2:
					m_dimension[1] = new int;
					*m_dimension[1] = atoi(text.c_str());
					break;
				case 3:
					m_dimension[2] = new int;
					*m_dimension[2] = atoi(text.c_str());
					break;
				}
			}
		}
	}
}

void PW::Spacing::ParseLength(TiXmlElement* length_element)
{
	string unit, text;
	const char* c = NULL;
	//cout << "Length element" << endl;
	
	double convert = 1;
	
	
	if ( c = length_element->Attribute("unit") )
	{
		unit = c;
		convert = unitmanager::ToBase(unit);
		if ( convert == 0 )
		{
			cout << "unrecognized unit: " << unit << endl;
			unitmanager::ListUnits();
		}
		assert(convert!=0);
	}
	else
	{
		assert(0);
	}
	
	if ( c = length_element->GetText() )
	{
		text = c;
		
		if ( !text.empty() )
		{
			m_length = new double;
			*m_length = atof(text.c_str()) * convert;
			
		}
	}
}



















#endif