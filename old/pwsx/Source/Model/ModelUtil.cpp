#include <Model/ModelUtil.h>

inline ftoid_parser::~ftoid_parser() {
}// defined even though it's pure virtual; it's faster this way; trust me


void 	ftoid_parser_parameter::parse(Model* model,TiXmlElement* element,int& state) {
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
		convert = unitmanager::ToBase(unit);
		if ( convert == 0 )
		{
			cout << "unrecognized unit: " << unit << endl;
			unitmanager::ListUnits();
		}
		assert(convert!=0);
	}
	if ( c = element->GetText() )
	{
		text = c;
	}
	
	
	
	if ( !text.empty() )
	{
		Variable* var = model->m_mapVariables[name];
		
		if ( var )
		{
			state = state | var->GetState();
			
			var->SetValue(text,convert);
			
			cout << var->m_name << " ";
			//var->PrintValue();
			cout << endl;
		}
		else
		{
			cout << "Invalid parameter: " << name << endl;
		}
	}
}
void 	ftoid_parser_spacing::parse(Model* model,TiXmlElement* element,int& state) {
	PW::Spacing* s = new PW::Spacing(element);
			
	if ( s->m_enabled )
	{
		model->m_spacings[s->m_name] = s;
	}
	else
	{
		delete s;
	}
}
void 	ftoid_parser_intvector::parse(Model* model,TiXmlElement* element,int& state) {
	const char* c = NULL;
			
			
	if ( c = element->Attribute("name") )
	{
		
		if ( strcmp( c, "Channel Group Outlet" ) == 0 )
		{
			TiXmlElement* element2 = element->FirstChildElement( "Element" );
		
			while ( element2 )
			{
				if ( c = element2->GetText() )
				{
					model->m_channel_groups_outlet.push_back(atoi(c));
				}
				
				element2 = element2->NextSiblingElement( "Element" );
			}
		}
		else if ( strcmp( c, "Channel Group Inlet" ) == 0 )
		{
			TiXmlElement* element2 = element->FirstChildElement( "Element" );
		
			while ( element2 )
			{
				if ( c = element2->GetText() )
				{
					model->m_channel_groups_inlet.push_back(atoi(c));
				}
				
				element2 = element2->NextSiblingElement( "Element" );
			}
		}
	}
}
void 	ftoid_parser_pattern::parse(Model* model,TiXmlElement* element,int& state) {
	shared_ptr<PW::Pattern> p(new PW::Pattern());
	
	p->Parse(element);
	
	if ( p->m_enabled )
	{
		model->m_cs.m_mapPatterns[p->m_dimension] = p;
	}
	
}

		Variable::Variable(){
	m_enabled = false;
}
		Variable::Variable(string name,int state){
	m_name = name;
	m_state = state;
	m_enabled = true;
}
bool 	Variable::Enabled(){
	return m_enabled;
}
int 	Variable::GetState(){
	return m_state;
}
	

		VariableD::VariableD(string name,int state): Variable( name, state ) {
};
void 	VariableD::SetValue(string str,double convert){
	m_value = atof(str.c_str()) * convert;
}
void*	VariableD::GetValue(){
	return &m_value;
}
void 	VariableD::PrintValue(){
	cout << m_value;
}
	
	
		VariableI::VariableI(string name,int state): Variable( name, state ) {};
void 	VariableI::SetValue(string str,double convert){
	m_value = atoi(str.c_str());
}
void* 	VariableI::GetValue(){
	return &m_value;
}
void 	VariableI::PrintValue(){
	cout << m_value;
}


		VariableS::VariableS(string name,int state): Variable( name, state ) {};
void 	VariableS::SetValue(string str,double convert) {
	m_value = str;
}
void* 	VariableS::GetValue() {
	return &m_value;
}
void 	VariableS::PrintValue() {
	cout << m_value;
}


		IS::IS( ISType type, int a, int b, int c, int d ){
	assert( ( type == e_MOD_AND_RANGE ) || ( type == e_MOD_AND_TRIM ) );
	
	m_type = type;
	m_a = a;
	m_b = b;
	m_c = c;
	m_d = d;
	
	assert( m_a != 0 );
}
		IS::IS( ISType type, int a, int b ){
	assert( (type == e_MOD) || ( type == e_RANGE ) || ( type == e_TRIM ) );
	
	m_type = type;
	m_a = a;
	m_b = b;
	
	if (type == e_MOD)
		assert( m_a != 0 );
}
		IS::IS( ISType type, int a ){
	assert( ( type == e_VALUE ) || ( type == e_END_MINUS ) );
	
	m_type = type;
	m_a = a;
}
		IS::IS( ISType type ){
	assert( ( type == e_ALL ) || ( type == e_BEGIN ) || ( type == e_END ) || ( type == e_EVEN ) || ( type == e_ODD ) || ( type == e_BEGIN_AND_END ) );
	
	m_type = type;
}
bool 	IS::Test(int i,int n){
	//PRNTLOC;
	
	switch (m_type)
	{
	case e_EVEN:
		return ( i % 2 == 0 );
	
	case e_ODD:
		return ( i % 2 == 1 );
		
	case e_MOD:
		assert(m_a != 0);
		return ( i % m_a == m_b );
		
	case e_RANGE:
		return (( i >= m_a )&&( i <= m_b ));
		
	case e_MOD_AND_RANGE:
		assert(m_a != 0);
		return ( ( i % m_a == m_b )&&( i >= m_c )&&( i <= m_d ));
		
	case e_ALL:
		return true;
		
	case e_VALUE:
		return ( i == m_a );
		
	case e_BEGIN:
		return ( i == 0 );
	
	case e_END:
		return ( i == ( n - 1 ) );
		
	case e_END_MINUS:
		return ( i == ( n - 1 - m_a ) );
		
	case e_TRIM:
		return ( ( i >= m_a )&&( i <= ( n - 1 - m_b ) ) );
		
	case e_MOD_AND_TRIM:
		return ( ( i % m_a == m_b )&&( i >= m_c )&&( i <= ( n - 1 - m_d ) ) );
	
	case e_BEGIN_AND_END:
		return ( ( i == 0 ) || ( i == ( n - 1 ) ) );
	
	default:
		assert(0);
		return false;
	}
}
	








