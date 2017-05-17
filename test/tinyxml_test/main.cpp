#include <iostream>
#include <map>
#include <string>

#include "../../tinyxml_2_6_2/tinyxml/tinyxml.cpp"
#include "../../tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "../../tinyxml_2_6_2/tinyxml/tinyxmlerror.cpp"
#include "../../tinyxml_2_6_2/tinyxml/tinyxmlparser.cpp"
#include "../../tinyxml_2_6_2/tinyxml/tinystr.cpp"
#include "../../tinyxml_2_6_2/tinyxml/tinystr.h"

using namespace std;

enum ParameterName
{
	e_INVALID = 0,
	e_CHANNEL_HEIGHT,
	e_NB_PARAMETER_NAMES
};


class Attribute
{
public:
	string m_name;
	string m_value;
	
}

class Element
{
public:
	
	Element* parent;
	
	string m_name;
	
	vector<Attribute> m_attributes;
	
	vector<Element*> m_children;
}


int main()
{
	
	
	
	
	map<string,ParameterName> mapParamName;
	
	mapParamName["x wall"] = 					e_X_WALL;
	mapParamName["x channel"] = 				e_X_CHANNEL;
	
	cout << mapParamName["invalid"] << endl;
	
	int condition = (
		e_X_CHANNEL | e_X_WALL | e_X_HEATED | e_X_HEADER_INLET_EXT | e_X_HEADER_OUTLET_EXT | 
		e_Y_HEATED | e_Y_HEADER_INLET | e_Y_HEADER_OUTLET | e_Y_HEADER_INLET_2 | e_Y_HEADER_OUTLET_2 | 
		e_Z_FLUX_PLATE | e_Z_CHANNEL | e_Z_HEADER | 
		e_NB_OF_CHANNELS | e_NB_OF_HEADER_PLATES | 
		e_TITLE | e_ROOT | e_Y_NEG_SYM );
	
	int state = 0;
	
	TiXmlDocument document( "option_2_a_7.xml" );
	if ( !document.LoadFile() )
	{
		cout << "XML file not found" << endl;
		return false;
	}
	
	
	
	TiXmlElement* root = document.FirstChildElement();
	if ( root )
	{
		root->Value();
		
		TiXmlElement* element = root->FirstChildElement();
		
		while ( element )
		{
			
			
			
		}
	}
	
	
	
	
	
	
	
	
	
	TiXmlElement* root = document.FirstChildElement( "Case" );
	if ( root )
	{
		TiXmlElement* element = root->FirstChildElement( "Parameter" );
		
		while ( element )
		{
			string value = element->Value();
			string name, unit, text;
			
			double convert = 1;
			
			const char* c = NULL;
			
			if ( c = element->Attribute("name") )
			{
				name = c;
			}
			if ( c = element->Attribute("unit") )
			{
				unit = c;
				convert = UnitManager::ToBase(unit);
				if ( convert == 0 )
				{
					cout << "unrecognized unit: " << unit << endl;
					UnitManager::ListUnits();
				}
				assert(convert!=0);
			}
			if ( c = element->GetText() )
			{
				text = c;
			}
			
			if ( mapParamName[name] == e_INVALID )
			{
				cout << "Invalid parameter: " << name << endl;
			}
			else
			{
				cout << name << ": " << text << " " << unit << endl;
			}
			
			if ( !text.empty() )
			{
				state = state | mapParamName[name];
				
				switch ( mapParamName[name] )
				{
				case e_NB_OF_HEADER_PLATES:
					m_nb_header_plates = atoi(text.c_str());
					break;
				case e_TITLE:
					m_title = text;
					break;
				case e_ROOT:
					m_root = text;
					break;
				case e_Y_NEG_SYM:
					m_y_neg_sym = atoi(text.c_str());
					break;
				case e_INVALID:
					
					break;
				}
			}
			
			element = element->NextSiblingElement();
		}
	}
	
	if ( ( state & condition ) == condition )
	{
		return true;
	}
	else
	{
		cout << "state = " << state << " does not equal condition = " << condition << endl;
		return false;
	}
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
