

class unitmanager {
	public:
		friend class unit;

		static void 			Init();
		static double 			ToBase(string name);
		static double			ToBase(string strfrom,double dfrom);
		static shared_ptr<unit>	MakeUnit(string name);
		static void 			ListUnits();
		static double			Convert(string strfrom,double dfrom,string strto);
	private:
		static map<string,shared_ptr<unit> > m_mapUnits;
};

map<string,shared_ptr<unit>> unitmanager::m_mapUnits = map<string,shared_ptr<unit> >();

void 				unitmanager::Init() {
	unitmanager::m_mapUnits["millimeter"].		reset(new unit(unit::Prefix::e_MILLI,	unit::Name::e_METER,	unit::Basic::e_LENGTH,			0.001));
	unitmanager::m_mapUnits["centimeter"].		reset(new unit(unit::Prefix::e_CENTI,	unit::Name::e_METER,	unit::Basic::e_LENGTH,			0.01));
	unitmanager::m_mapUnits["meter"].		reset(new unit(unit::Prefix::e_NONE,	unit::Name::e_METER,	unit::Basic::e_LENGTH,			1));
	unitmanager::m_mapUnits["kelvin"].		reset(new unit(unit::Prefix::e_NONE,	unit::Name::e_KELVIN,	unit::Basic::e_TEMPERATURE,		0));
	unitmanager::m_mapUnits["celsius"].		reset(new unit(unit::Prefix::e_NONE,	unit::Name::e_CELSIUS,	unit::Basic::e_TEMPERATURE,		0));

	unitmanager::m_mapUnits["W m-1 K-1"].		reset(new unit(unit::Prefix::e_NONE,	unit::Name::e_COMPOUND,	unit::Basic::e_COMPOUND,		1));
	unitmanager::m_mapUnits["W m-2"].		reset(new unit(unit::Prefix::e_NONE,	unit::Name::e_COMPOUND,	unit::Basic::e_COMPOUND,		1));
	unitmanager::m_mapUnits["bar"].			reset(new unit(unit::Prefix::e_NONE,	unit::Name::e_COMPOUND,	unit::Basic::e_COMPOUND,		100000));
}
double 				unitmanager::ToBase(string name) {
	shared_ptr<unit> u = m_mapUnits[name];

	if ( u->Enabled() )
	{
		return u->ToBase();
	}
}
shared_ptr<unit>	unitmanager::MakeUnit(string name) {
	shared_ptr<unit> u = m_mapUnits[name];

	if ( u->Enabled() )
	{
		return u;
	}
	else
	{
		return shared_ptr<unit>();
	}
}
void 				unitmanager::ListUnits() {
	for ( map<string,shared_ptr<unit> >::iterator it=m_mapUnits.begin(); it!=m_mapUnits.end(); ++it )
	{
		printf ("'%s' %i %i %i %f\n", it->first.c_str(), it->second->GetPrefix(), it->second->GetName(), it->second->GetBasic(), it->second->ToBase());
	}
}
double 				unitmanager::Convert(string strfrom,double dfrom,string strto) {
	shared_ptr<unit> ufrom 	= m_mapUnits[strfrom];
	shared_ptr<unit> uto 	= m_mapUnits[strto];

	if ( ufrom->Enabled() && uto->Enabled() )
	{
		if ( ( ufrom->GetBasic() == unit::Basic::e_TEMPERATURE ) || ( uto->GetBasic() == unit::Basic::e_TEMPERATURE ) )
		{
			if ( ( ufrom->GetBasic() == unit::Basic::e_TEMPERATURE ) && ( uto->GetBasic() == unit::Basic::e_TEMPERATURE ) )
			{
				switch ( ufrom->GetBasic() )
				{
					case unit::Name::e_CELSIUS:
						switch ( uto->GetBasic() )
						{
							case unit::Name::e_KELVIN:
								return dfrom + 273.15;
						}
					case unit::Name::e_KELVIN:
						switch ( uto->GetBasic() )
						{
							case unit::Name::e_CELSIUS:
								return dfrom - 273.15;
						}
				}

				assert( 0 );
			}
			else
			{
				assert( 0 );
			}
		}

		return dfrom * ufrom->Convert(uto);
	}

	ListUnits();

	assert( 0 );
	return 0;
}
double 				unitmanager::ToBase(string strfrom,double dfrom) {
	//printf ("ToBase('%s',%f)\n",strfrom.c_str(),dfrom);
	shared_ptr<unit> ufrom 	= m_mapUnits[strfrom];
	if (ufrom) {
		if (ufrom->Enabled()) {
			//printf ("'%s' %i %i %i %f\n", strfrom.c_str(), ufrom->GetPrefix(), ufrom->GetName(), ufrom->GetBasic(), ufrom->ToBase());
			if (ufrom->GetBasic() == unit::Basic::e_TEMPERATURE) {
				switch ( ufrom->GetName() ) {
					case unit::Name::e_CELSIUS:
						//printf ("converting celsius to kelvin %i\n",ufrom->GetBasic());
						return (dfrom + 273.15);
					case unit::Name::e_KELVIN:
						//printf ("converting kelvin to kelvin %i\n",ufrom->GetBasic());
						return dfrom;
				}

				assert( 0 );
			}

			//printf ("converting '%s' to base\n",strfrom.c_str());
			return dfrom * ufrom->ToBase();
		}
	}
	printf ("unknown unit '%s'\n", strfrom.c_str());
	ListUnits();

	exit(0);
	return 0;
}

