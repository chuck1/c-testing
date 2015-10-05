#include <stdio.h>

#include "../external/tinyxml.h"

namespace myxml {
struct attr {
	const char	*value;
	
	int			null;
	int			type;
	void*		text;
};
struct el {
	const char 	*value;
	
	attr 		*attrv;
	int 		attrc;
	
	el 			*childv;
	int 		childc;
	
	el 			*reschildv;
	int 		reschildc;
	
	int			null;
	int			type;
	void*		text;
};


enum datatype {
	e_DOUBLE,
	e_INT,
	e_CHARSTR,
	e_CHAR
};

int proc_at (TiXmlElement *element,attr *a) {
	const char* c = 0;
	
	c = element->Attribute(a->value);
	if (c) {
		switch (a->type) {
		case e_DOUBLE:
			a->text = new double(atof(c));
			break;
		case e_INT:
			a->text = new int(atoi(c));
			break;
		case e_CHARSTR:
			a->text = new char[strlen(c)+1];
			memcpy(a->text,c,strlen(c)+1);
			
			printf ("\t\t'%s', %i bytes\n",a->text,strlen(c));
			break;
		default:
			printf ("invalid type for attribute text conversion\n");
			break;
		}
	}
	else {
		if (!a->null)
		{
			printf ("attribute '%s' not specified\n", a->value);
		}
	}
}
int proc_el (TiXmlElement *element,el *e) {
	const char* c = 0;
	
	e->reschildv = new el[20];
	e->reschildc = 0;
	
	TiXmlElement* child = 0;
	
	for (int a = 0; a < e->attrc; a++) {
		proc_at(element,e->attrv + a);
	}
	
	if (e->childc) {
		for (int a = 0; a < e->childc; a++) {
			//printf ("search for '%s'\n",e->childv[a].value);
			child = element->FirstChildElement(e->childv[a].value);
			
			while (child) {
				//printf ("\tfound a(an) '%s'\n", e->childv[a].value);
				
				e->reschildv[e->reschildc] = e->childv[a];
				e->reschildv[e->reschildc].attrv = new attr[e->reschildv[e->reschildc].attrc];
				memcpy (e->reschildv[e->reschildc].attrv, e->childv[a].attrv, sizeof(attr)*(e->childv[a].attrc));
				//printf ("\t\tcopy %i attributes, %i bytes\n", e->childv[a].attrc, sizeof(attr)*(e->childv[a].attrc));
				
				proc_el (child, e->reschildv + e->reschildc);
				
				e->reschildc++;
				
				child = child->NextSiblingElement(e->childv[a].value);
			}
		}
	}
	else {
		c = element->GetText();
		if (c) {
			switch (e->type) {
			case e_DOUBLE:
				e->text = new double(atof(c));
				break;
			case e_INT:
				e->text = new int(atoi(c));
				break;
			case e_CHARSTR:
				e->text = new char[strlen(c)+1];
				memcpy(e->text,c,strlen(c)+1);
				break;
			default:
				printf ("invalid type for attribute text conversion\n");
				break;
			}
		}
		else {
			if (!e->null)
			{
				printf ("text for '%s' element not specified\n", e->value);
			}
		}
	}
}


int parse (const char *xmlfile, el *e) {
	assert (xmlfile);
	assert (e);
	
	TiXmlDocument document(xmlfile);
	if ( !document.LoadFile() ) {
		//printf ("XML file not found\n");
		return 0;
	}
	
	assert (e->value);
	//printf ("e->value='%s'\n", e->value);
	TiXmlElement* root = document.FirstChildElement(e->value);
	TiXmlElement* element = NULL;
	
	//printf ("root='%p'\n", root);
	
	if ( root )
	{
		proc_el (root, e);
	}
	
	//printf ("e->reschildv='%p'\n", e->reschildv);
	
	/*
	assert (e->reschildv);
	for (int a = 0; a < e->reschildc; a++)
	{
		el *ch = e->reschildv + a;
		
		assert (ch->value);
		//assert (ch->attrv);
		
		//printf("%s %s\n", ch->value, ch->attrv[0].text);
		
		if (strcmp(ch->value,"el")==0) {
			printf("%s %s\n", ch->value, ch->attrv[0].text);
		}
		else {
			printf("%s\n", ch->value);
		}
	}
	*/
	return 1;
}
}