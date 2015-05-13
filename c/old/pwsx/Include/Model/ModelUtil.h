#ifndef _MODEL_UTIL_H
#define _MODEL_UTIL_H

#include <MyLib/external/tinyxml.h>

enum ParameterName {
	e_X_CHANNEL				= (1 << 0),
	e_X_WALL 				= (1 << 1),
	e_X_HEATED 				= (1 << 2),
	e_X_HEADER_INLET_EXT 	= (1 << 3),
	e_X_HEADER_OUTLET_EXT 	= (1 << 4),
	e_Y_HEATED 				= (1 << 5),
	e_Y_HEADER_INLET 		= (1 << 6),
	e_Y_HEADER_OUTLET 		= (1 << 7),
	e_Z_FLUX_PLATE 			= (1 << 8),
	e_Z_CHANNEL 			= (1 << 9),
	e_Z_HEADER 				= (1 << 10),
	e_NB_OF_CHANNELS 		= (1 << 11),
	e_NB_OF_HEADER_PLATES 	= (1 << 12),
	e_TITLE 				= (1 << 13),
	e_ROOT 					= (1 << 14),
	e_Y_NEG_SYM				= (1 << 15),
	e_Y_HEADER_INLET_2 		= (1 << 16),
	e_Y_HEADER_OUTLET_2		= (1 << 17)
};
class ftoid_parser {
public:
	virtual void parse(Model*,TiXmlElement*,int&) = 0;
	virtual ~ftoid_parser() = 0;
};
class ftoid_parser_parameter: public ftoid_parser {
public:
	virtual void parse(Model*,TiXmlElement*,int&);
};
class ftoid_parser_spacing: public ftoid_parser {
public:
	virtual void parse(Model*,TiXmlElement*,int&);
};
class ftoid_parser_intvector: public ftoid_parser {
public:
	virtual void parse(Model*,TiXmlElement*,int&);
};
class ftoid_parser_pattern: public ftoid_parser {
public:
	virtual void parse(Model*,TiXmlElement*,int&);
};
class Variable {
public:
	Variable();
	Variable(string name,int state);
	int GetState();
	virtual void* GetValue() = 0;
	virtual void PrintValue() = 0;
	
	string m_name;
	virtual void SetValue(string str,double convert) = 0;
	
	bool m_enabled;
	int m_state;
};
class VariableD: public Variable {
public:
	VariableD(string name,int state);
	void SetValue(string str,double convert);
	void* GetValue();
	void PrintValue();
	double m_value;
};
class VariableI: public Variable {
public:
	VariableI(string name,int state);
	
	void SetValue(string str,double convert);
	
	void* GetValue();
	
	void PrintValue();
	
	int m_value;
};
class VariableS: public Variable {
public:
	VariableS(string name,int state);
	void SetValue(string str,double convert);
	void* GetValue();
	void PrintValue();
	string m_value;
};
class IS {
public:
	enum ISType
	{
		e_MOD,
		e_RANGE,
		e_MOD_AND_RANGE,
		e_ALL,
		e_VALUE,
		e_BEGIN,
		e_END,
		e_BEGIN_AND_END,
		e_END_MINUS,
		e_TRIM,
		e_MOD_AND_TRIM,
		e_EVEN,
		e_ODD,
		e_NB_TYPES
	};
	IS( ISType type, int a, int b, int c, int d );
	IS( ISType type, int a, int b );
	IS( ISType type, int a );
	IS( ISType type );
	bool Test(int i,int n);
	
	int m_type;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
};


#endif
