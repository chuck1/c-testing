#ifndef _UNIT_H
#define _UNIT_H

#include <iostream>
#include <map>
#include <string>
#include <assert.h>
#include <memory>

using namespace std;




class unit
{
public:
	struct Prefix {
		enum {
			e_PREFIX_INVALID,
			e_MILLI,
			e_CENTI,
			e_KILO,
			e_NONE
		};
	};
	struct Name {
		enum {
			e_NAME_INVALID,
			e_METER,
			e_SECOND,
			e_CELSIUS,
			e_KELVIN,
			e_COMPOUND
		};
	};
	struct Basic {
		enum {
			e_BASIC_INVALID,
			e_LENGTH,
			e_TIME,
			e_MASS,
			e_TEMPERATURE,
			e_COMPOUND
		};
	};
	
			unit();
			unit(int prefix, int name, int basic, double toBase);
	
	bool 	Enabled();
	double 	Convert(shared_ptr<unit> to);
	double 	ToBase();
	
	int		GetPrefix(){ return m_prefix; }
	int		GetName(){ return m_name; }
	int		GetBasic(){ return m_basic; }
	
private:
	double 	m_toBase;
	int		m_prefix;
	int 	m_name;
	int 	m_basic;
	bool 	m_enabled;
};


		unit::unit() {
	m_enabled = false;
	
	m_toBase = 0;
	m_prefix = Prefix::e_PREFIX_INVALID;
	m_name = Name::e_NAME_INVALID;
	m_basic = Basic::e_BASIC_INVALID;
};
		unit::unit(int prefix, int name, int basic, double toBase): 
	m_enabled(true),
	m_toBase(toBase),
	m_prefix(prefix),
	m_name(name),
	m_basic(basic)
{
}
bool 	unit::Enabled() {
	return m_enabled;
}
double 	unit::Convert(shared_ptr<unit> to) {
	assert( to->m_toBase != 0 );
	assert( m_toBase != 0 );
	
	return m_toBase/to->m_toBase;
}
double 	unit::ToBase() {
	return m_toBase;
}


#include "unitmanager.h"


#endif

