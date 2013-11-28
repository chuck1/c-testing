#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/regex.hpp>

using namespace std;

class cppMember
{
public:
	string type;
	string name;
};

class cppClass : public cppMember
{
public:
	vector<cppMember> members;
};

class cppVariable;

class cppFunctionm : public cppMember
{
public:
	vector<cppVariable> args;
};

class cppVariable : public cppMember
{
public:
	
};

enum STRING_TYPE {
	WORD=0,
	P_OPEN=1,
	P_CLOSE=2,
	B_OPEN=3,
	B_CLOSE=4,
	C_OPEN=5,
	C_CLOSE=6,
	ASTRISK=7,
	SEMICOLON=8,
	ERROR=9
};

enum KEYWORD {
	CLASS=0,
	KEYWORD_ERROR=1
};

int classify (string str, STRING_TYPE &string_type)
{
	boost::regex e[9];
	e[0] = ("\\w+");
	e[1] = ("\\(");
	e[2] = ("\\)");
	e[3] = ("\\[");
	e[4] = ("\\]");
	e[5] = ("\\}");
	e[6] = ("\\{");
	e[7] = ("\\*");
	e[8] = (";");
	for (int i=0; i<9; i++) {
		if (boost::regex_match(str,e[i]))
		{
			string_type=(STRING_TYPE)i;
		}
	}
	return 0;
}

int classifyword (string str, KEYWORD &keyword)
{
	boost::regex e[1];
	e[0] = ("class");
	for (int i=0; i<1; i++) {
		if (boost::regex_match(str,e[i]))
		{
			keyword=(KEYWORD)i;
		}
	}
	return 0;
}

int sub (string str,string &match,string &remainder,STRING_TYPE &string_type)
{
	boost::regex e (".*(\\b\\w+\\b|\\(|\\)|\\{|\\}|;|\\*)(.*)");
	boost::smatch sm;
	
	string_type = ERROR;
	
	
	if (boost::regex_match(str,sm,e,boost::regex_constants::match_any))
	{
		classify(sm[1],string_type);
		cout << sm[1] << "\t" << string_type << endl;
		
		remainder=sm[2];
		
	}
	else
	{
		cout << "no match" << endl;
		return 1;
	}
	
	return 0;
}

int main ()
{
	string str = "class physics{ void step(); double dt; }";
	string remainder;
	string match;
	
	vector<cppClass*> classes;
	
	cppClass* current_class;
	
	STRING_TYPE string_type;
	KEYWORD keyword;
	
	while ( true )
	{
		if (sub(str,match,remainder,string_type)==1) break;
		if ( remainder.empty() ) break;
		
		switch (string_type)
		{
		case WORD:
			classifyword(match,keyword);
			
			switch (keyword)
			{
			case CLASS:
				current_class=new cppClass();
				classes.push_back(current_class);
				break;
			}
			
			break;
		}
		
		
		
		str=remainder;
	}
	
	
	return 0;
}
