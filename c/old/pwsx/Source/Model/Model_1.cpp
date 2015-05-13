#include <Model/Model_1.h>
#include <Model/ModelUtil.h>
#include <PW/PW.h>
#include <PW/CartSet/CartSet.h>
#include <PW/BoundaryCondition/BoundaryCondition.h>
#include <PW/VolumeCondition/VolumeCondition.h>
#include <PW/ConnectionBoundaryCondition/ConnectionBoundaryCondition.h>

void Model_1::PopulateVariableMap() {
	
	m_mapVariables["root"] = 					new VariableS( "root", e_ROOT );
	
	m_condition = ( e_ROOT );
}
void Model_1::ProcessVariables() {
	PRNTLOC;
	
	m_root = 				*((string*)(m_mapVariables["root"]->GetValue()));
	
}
void Model_1::Process() {
	// process cartset
	m_cs.DefaultProcess();
	
	SetVolumeConditions();
	
	SetBoundaryConditions();
}
void Model_1::SetVolumeConditions() {
	PRNTLOC;
	
	m_VC_solid = new pw::VolumeCondition("solid",pw::VCType::e_SOLID);
	m_VC_fluid = new pw::VolumeCondition("fluid",pw::VCType::e_FLUID);
	/*
	int n0 = m_cs.GetN(0);
	int n1 = m_cs.GetN(1);
	int n2 = m_cs.GetN(2);
	*/
	// solid
	PRNTLOC;
	SetVolumeCondition( m_VC_solid, 	IS(IS::e_ALL),				IS(IS::e_ALL),			IS(IS::e_ALL) );
	
	// fluid
	PRNTLOC;
	// channel layer
	SetVolumeCondition( m_VC_fluid, 	IS(IS::e_ODD),				IS(IS::e_RANGE,0,2),	IS(IS::e_VALUE,1) );
	
	// first header layer
	SetVolumeCondition( m_VC_fluid, 	IS(IS::e_TRIM,	1,1),		IS(IS::e_VALUE,0),		IS(IS::e_VALUE,2) ); 	// outlet slot
	SetVolumeCondition( m_VC_fluid, 	IS(IS::e_TRIM,	1,1),		IS(IS::e_VALUE,2),		IS(IS::e_VALUE,2) );	// inlet slot
	
	// second header layer
	SetVolumeCondition( m_VC_fluid, 	IS(IS::e_TRIM,	1,0),		IS(IS::e_VALUE,0),		IS(IS::e_VALUE,3) ); 	// outlet slot	
	SetVolumeCondition( m_VC_fluid, 	IS(IS::e_TRIM,	0,1),		IS(IS::e_VALUE,2),		IS(IS::e_VALUE,3) );	// inlet slot
	PRNTLOC;
	
	
	// solid
	// outlet slot ribs
	vector<int> v = ConvertChannelCountToWallIndices(m_channel_groups_outlet,1);
	for ( int a = 0; a < v.size(); a++ )
	{
		cout << "outlet rib at i=" << v.at(a) << endl;
		SetVolumeCondition( m_VC_solid, IS(IS::e_VALUE,v.at(a)),	IS(IS::e_VALUE,0),		IS(IS::e_VALUE,2) ); 	
	}
	
	PRNTLOC;
	
	// inlet slot ribs
	v = ConvertChannelCountToWallIndices(m_channel_groups_inlet,1);
	for ( int a = 0; a < v.size(); a++ )
	{
		cout << "inlet rib at i=" << v.at(a) << endl;
		SetVolumeCondition( m_VC_solid, IS(IS::e_VALUE,v.at(a)),	IS(IS::e_VALUE,2),		IS(IS::e_VALUE,2) ); 	
	}
	
}
void Model_1::SetBoundaryConditions() {
	PRNTLOC;
	// initialize
	
	m_BC_inlet = new pw::BoundaryCondition("inlet",pw::BCType::e_MASS_FLOW_INLET);
	m_BC_outlet = new pw::BoundaryCondition("outlet",pw::BCType::e_PRESSURE_OUTLET);
	m_BC_sym = new pw::BoundaryCondition("symmetry",pw::BCType::e_SYMMETRY);
	m_BC_heated = new pw::BoundaryCondition("heated",pw::BCType::e_WALL);
	
	m_BC_int_wall = new pw::ConnectionBoundaryCondition("interior_wall",pw::BCType::e_INTERFACE);
	
	// get array size
	/*
	int n0 = m_cs.GetN(0);
	int n1 = m_cs.GetN(1);
	int n2 = m_cs.GetN(2);	
	*/
	// inlet
	SetBoundaryCondition( m_BC_inlet,1,			IS(IS::e_VALUE,0),	IS(IS::e_VALUE,0),			IS(IS::e_VALUE,2),		IS(IS::e_VALUE,3) );
	
	// outlet
	SetBoundaryCondition( m_BC_outlet,-1,		IS(IS::e_VALUE,0),	IS(IS::e_END),				IS(IS::e_BEGIN),		IS(IS::e_VALUE,3) );
	
	// symmetry
	SetBoundaryCondition( m_BC_sym,1,			IS(IS::e_VALUE,1),	IS(IS::e_ALL),				IS(IS::e_BEGIN),		IS(IS::e_ALL) );
	
	// heated
	SetBoundaryCondition( m_BC_heated,1,		IS(IS::e_VALUE,2),	IS(IS::e_TRIM,1,1),			IS(IS::e_RANGE,0,2),	IS(IS::e_BEGIN) );
	
	// interior wall
	SetConnectionBoundaryConditionAuto(m_BC_int_wall,m_VC_solid,m_VC_fluid);
	
}













