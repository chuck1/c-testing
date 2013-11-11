#include <Model/Model_6.h>
#include <Model/ModelUtil.h>
#include <PW/PW.h>
#include <PW/CartSet/CartSet.h>
#include <PW/BoundaryCondition/BoundaryCondition.h>
#include <PW/VolumeCondition/VolumeCondition.h>
#include <PW/ConnectionBoundaryCondition/ConnectionBoundaryCondition.h>


void Model_6::PopulateVariableMap() {
	
	m_mapVariables["root"] = 					new VariableS( "root", e_ROOT );
	
	m_condition = ( e_ROOT );
}
void Model_6::ProcessVariables() {
	PRNTLOC;
	
	m_root = 				*((string*)(m_mapVariables["root"]->GetValue()));
	
}
void Model_6::Process() {
	// process cartset
	m_cs->DefaultProcess();
	
	SetVolumeConditions();
	
	SetBoundaryConditions();
}
void Model_6::SetVolumeConditions() {
	PRNTLOC;
	
	m_VC_solid = new PW::VolumeCondition("solid",PW::VCType::e_SOLID);
	m_VC_fluid = new PW::VolumeCondition("fluid",PW::VCType::e_FLUID);
	
	// solid
	PRNTLOC;
	SetVolumeCondition( m_VC_solid, 	IS(IS::e_ALL),				IS(IS::e_ALL),			IS(IS::e_ALL) );
	
	// fluid
	PRNTLOC;
	// channel layer
	SetVolumeCondition( m_VC_fluid, 	IS(IS::e_ODD),				IS(IS::e_RANGE,1,3),	IS(IS::e_VALUE,1) );
	
	// header layer
	SetVolumeCondition( m_VC_fluid, 	IS(IS::e_TRIM,	1,0),		IS(IS::e_VALUE,1),		IS(IS::e_VALUE,2) ); 	// outlet slot	
	SetVolumeCondition( m_VC_fluid, 	IS(IS::e_TRIM,	0,1),		IS(IS::e_VALUE,3),		IS(IS::e_VALUE,2) );	// inlet slot
	PRNTLOC;
	
}
void Model_6::SetBoundaryConditions() {
	PRNTLOC;
	// initialize
	
	m_BC_inlet = new PW::BoundaryCondition("inlet",PW::BCType::e_MASS_FLOW_INLET);
	m_BC_outlet = new PW::BoundaryCondition("outlet",PW::BCType::e_PRESSURE_OUTLET);
	m_BC_heated = new PW::BoundaryCondition("heated",PW::BCType::e_WALL);
	
	m_BC_int_wall = new PW::ConnectionBoundaryCondition("interior_wall",PW::BCType::e_INTERFACE);
	
	// get array size
	
	int n0 = m_cs->GetN(0);
	int n1 = m_cs->GetN(1);
	int n2 = m_cs->GetN(2);	
	
	// inlet
	SetBoundaryCondition( m_BC_inlet,1,			IS(IS::e_VALUE,0),	IS(IS::e_BEGIN),			IS(IS::e_VALUE,3),		IS(IS::e_VALUE,2) );
	
	// outlet
	SetBoundaryCondition( m_BC_outlet,-1,		IS(IS::e_VALUE,0),	IS(IS::e_END),				IS(IS::e_VALUE,1),		IS(IS::e_VALUE,2) );
	
	// heated
	SetBoundaryCondition( m_BC_heated,1,		IS(IS::e_VALUE,2),	IS(IS::e_TRIM,1,1),			IS(IS::e_VALUE,2),		IS(IS::e_BEGIN) );
	
	// interior wall
	SetConnectionBoundaryConditionAuto(m_BC_int_wall,m_VC_solid,m_VC_fluid);
	
}













