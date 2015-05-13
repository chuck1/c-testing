#ifndef _PATTERN_H
#define _PATTERN_H


namespace PW
{
	class Pattern
	{
	public:
		enum Type
		{
			e_NONE = 0,
			e_EXPLICIT,
			e_MOD_ENDS
		};
		
		Pattern()
		{
			m_enabled = false;
			m_dimension = -1;
		}
		
		void Parse(TiXmlElement*);
		
		bool m_enabled;
		int m_dimension;
		string m_name;
		vector<shared_ptr<Spacing> > 		m_vecSpacings;
		map<string,shared_ptr<Spacing> > 	m_mapSpacings;
		Type m_type;
		// various data
		int m_n;
	};
}

void PW::Pattern::Parse(TiXmlElement* element)
{
	map<string,int> mapDirection;
	mapDirection["x"] = 0;
	mapDirection["y"] = 1;
	mapDirection["z"] = 2;
	
	map<string,Type> mapType;
	mapType["explicit"] = e_EXPLICIT;
	mapType["mod ends"] = e_MOD_ENDS;
	
	
	
	
	
	const char* c = NULL;
	const char* d = NULL;
	
	
	TiXmlElement* spacing_element = NULL;
	
	if ( c = element->Attribute("direction") )
	{
		m_dimension = mapDirection[c];
		
		if ( d = element->Attribute("type") )
		{
			m_type = mapType[d];
			
			
			
			spacing_element = element->FirstChildElement( "Spacing" );
				
			while ( spacing_element )
			{
				shared_ptr<Spacing> s(new Spacing(spacing_element));
				
				if ( s->m_enabled )
				{
					m_vecSpacings.push_back(s);
					m_mapSpacings[s->m_name] = s;
				}
				
				spacing_element = spacing_element->NextSiblingElement( "Spacing" );
			}
			
			
			
			
			
			switch ( m_type )
			{
			case e_EXPLICIT:
			
				
				
				cout << "created pattern dimension=" << m_dimension << " type=" << d << endl;
				
				m_enabled = true;
			
				break;
			
			case e_MOD_ENDS:
				
				if ( c = element->Attribute("n") )
				{
					m_n = atoi(c);
					
					cout << "created pattern dimension=" << m_dimension << " type=" << d << " n=" << m_n << endl;
					
					m_enabled = true;
				}
				
				
				
				
				break;
			case e_NONE:
				assert(0);
			default:
				assert(0);
			}
		}
	}
}



#endif