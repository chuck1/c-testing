/*struct attr {
	const char	*c;
	
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
};*/

#include "myxml.h"

int main() {
	
	attr a[] = {
		{"name",0,e_CHARSTR,0},
		{"sex",0,e_CHARSTR,0}
	};
	
	el e[] = {
		{"parent",a,2,0,0,0,0,0,e_INT,0},
		{"child",a,2,0,0,0,0,0,e_INT,0}
	};
	
	el fam = {"fam",0,0,e,2,0,0,0,0,0};
	
	parse ("test.xml",&fam);
	
	return 1;
}