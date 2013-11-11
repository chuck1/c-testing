#include <Model/Model_5.h>

		Model_5::Model_5( double x_channel, double x_wall, double y_header_inlet, double y_header_outlet, double y_heated, double z_flux_plate, double z_channel, double z_header, double x_header_inlet_ext, double x_header_outlet_ext, int n, string title, string root ) {
	m_x_channel = x_channel;
	m_x_wall = x_wall;
	m_x_header_inlet_ext = x_header_inlet_ext;
	m_x_header_outlet_ext = x_header_outlet_ext;
	
	m_y_header_inlet = y_header_inlet;
	m_y_header_outlet = y_header_outlet;
	m_y_heated = y_heated;
	
	m_z_flux_plate = z_flux_plate;
	m_z_channel = z_channel;
	m_z_header = z_header;
	
	m_title = title;
	m_root = root;
}
void 	Model_5::PopulateVariableMap() {
	//m_mapVariables["x wall"] = 					new VariableD( "x wall", e_X_WALL );
	
	/*
	m_condition = (
		e_X_WALL | e_X_CHANNEL | e_X_HEATED | e_X_HEADER_INLET_EXT | e_X_HEADER_OUTLET_EXT | 
		
		e_Y_NEG_SYM );
	*/
}
void 	Model_5::ProcessVariables() {
	cout << "Processing Variables" << endl;
	
	//m_x_header_inlet_ext = 	*((double*)m_mapVariables["x header inlet ext"]->GetValue());
	
	
}
void 	Model_5::Process() {
	// create x-vector
	vector<double> x,xs1,xs2,xs3;
	
	x.push_back(0.0);
	
	x.push_back( x.back() + 10.0 );
	xs1.push_back( m_x_header_outlet_ext/40.0 );
	xs2.push_back( m_x_header_outlet_ext/40.0 );
	xs3.push_back( m_x_header_outlet_ext/40.0 );
	
	
	
	m_cs.ResetCoor(0,x); // x
	
	m_cs.ResetSpace(0,0,xs1); // x begin
	m_cs.ResetSpace(0,1,xs2); // x mid
	m_cs.ResetSpace(0,2,xs3); // x end
	
	// create y-vector
	vector<double> y,ys1,ys2,ys3;
	
	y.push_back(0.0);
	
	y.push_back( y.back() + m_y_header_outlet );
	ys1.push_back( m_y_header_outlet/30.0 );
	ys2.push_back( m_y_header_outlet/15.0 );
	ys3.push_back( m_y_header_outlet/30.0 );
	
	
	m_cs.ResetCoor(1,y); // y
	
	m_cs.ResetSpace(1,0,ys1); // y begin
	m_cs.ResetSpace(1,1,ys2); // y mid
	m_cs.ResetSpace(1,2,ys3); // y end
	
	// create z-vector
	vector<double> z,zs1,zs2,zs3;
	
	z.push_back(0.0);
	
	z.push_back( z.back() + m_z_flux_plate );
	zs1.push_back( m_z_flux_plate/10.0 );
	zs2.push_back( m_z_flux_plate/10.0 );
	zs3.push_back( m_z_flux_plate/10.0 );
	
	m_cs.ResetCoor(2,z); // z
	
	m_cs.ResetSpace(2,0,zs1); // z begin
	m_cs.ResetSpace(2,1,zs2); // z mid
	m_cs.ResetSpace(2,2,zs3); // z end
	
	// process
	
	m_cs.DefaultProcess();
	
	SetVolumeConditions();
	
	SetBoundaryConditions();
}
void 	Model_5::SetVolumeConditions() {
	PRNTLOC;
	
	m_VC_solid = new pw::VolumeCondition("solid",pw::VCType::e_SOLID);
	m_VC_fluid = new pw::VolumeCondition("fluid",pw::VCType::e_FLUID);
	
	int n0 = m_cs.GetN(0);
	int n1 = m_cs.GetN(1);
	int n2 = m_cs.GetN(2);
	
	// solid
	PRNTLOC;
	SetVolumeCondition( m_VC_solid, IS(IS::e_ALL), 			IS(IS::e_ALL),				IS(IS::e_VALUE,0) ); 	// plate 1
	
	SetVolumeCondition( m_VC_solid, IS(IS::e_EVEN),			IS(IS::e_ALL),				IS(IS::e_VALUE,1) ); 	// plate 2 channel wall
	SetVolumeCondition( m_VC_solid, IS(IS::e_ODD),			IS(IS::e_END),				IS(IS::e_VALUE,1) ); 	// palte 2 outer y-edge
	
	SetVolumeCondition( m_VC_solid, IS(IS::e_ALL),			IS(IS::e_TRIM,1,2),			IS(IS::e_VALUE,2) ); 	// plate 3 middle
	SetVolumeCondition( m_VC_solid, IS(IS::e_ALL),			IS(IS::e_END),				IS(IS::e_VALUE,2) ); 	// plate 3 outer y-edge
	SetVolumeCondition( m_VC_solid, IS(IS::e_BEGIN),		IS(IS::e_BEGIN),			IS(IS::e_VALUE,2) ); 	// plate 3 outlet
	SetVolumeCondition( m_VC_solid, IS(IS::e_END),			IS(IS::e_END_MINUS,1),		IS(IS::e_VALUE,2) ); 	// plate 3 inlet
	
	SetVolumeCondition( m_VC_solid, IS(IS::e_ALL),			IS(IS::e_VALUE,2),			IS(IS::e_VALUE,3) ); 	// plate 4 middle
	SetVolumeCondition( m_VC_solid, IS(IS::e_BEGIN),		IS(IS::e_RANGE,0,1),		IS(IS::e_VALUE,3) ); 	// plate 4 outlet
	SetVolumeCondition( m_VC_solid, IS(IS::e_END),			IS(IS::e_RANGE,3,5),		IS(IS::e_VALUE,3) ); 	// plate 4 inlet
	
	// fluid
	PRNTLOC;
	SetVolumeCondition( m_VC_fluid, IS(IS::e_ODD),			IS(IS::e_TRIM,0,1),			IS(IS::e_VALUE,1) ); 	// plate 2 channel
	
	SetVolumeCondition( m_VC_fluid, IS(IS::e_TRIM,1,0),		IS(IS::e_BEGIN),			IS(IS::e_VALUE,2) ); 	// plate 3 header outlet slot
	SetVolumeCondition( m_VC_fluid, IS(IS::e_TRIM,0,1),		IS(IS::e_END_MINUS,1),		IS(IS::e_VALUE,2) ); 	// plate 3 header inlet slot
	
	SetVolumeCondition( m_VC_fluid, IS(IS::e_TRIM,1,0),		IS(IS::e_RANGE,0,1),		IS(IS::e_VALUE,3) ); 	// plate 4 header outlet slot
	SetVolumeCondition( m_VC_fluid, IS(IS::e_TRIM,0,1),		IS(IS::e_RANGE,3,5),		IS(IS::e_VALUE,3) ); 	// plate 4 header inlet slot
	PRNTLOC;
}
void 	Model_5::SetBoundaryConditions() {
	PRNTLOC;
	// initialize
	
	m_BC_inlet = 	new pw::BoundaryCondition("inlet",pw::BCType::e_MASS_FLOW_INLET);
	m_BC_outlet = 	new pw::BoundaryCondition("outlet",pw::BCType::e_PRESSURE_OUTLET);
	m_BC_sym = 		new pw::BoundaryCondition("symmetry",pw::BCType::e_SYMMETRY);
	m_BC_heated = 	new pw::BoundaryCondition("heated",pw::BCType::e_WALL);
	
	m_BC_int_wall = new pw::ConnectionBoundaryCondition("interior_wall",pw::BCType::e_INTERFACE);
	
	// get array size
	
	int n0 = m_cs.GetN(0);
	int n1 = m_cs.GetN(1);
	int n2 = m_cs.GetN(2);	
	
	// inlet
	SetBoundaryCondition( m_BC_inlet,1,				IS(IS::e_VALUE,0),	IS(IS::e_BEGIN),								IS(IS::e_RANGE,3,5),	IS(IS::e_VALUE,m_k_inlet) );
	
	// outlet
	SetBoundaryCondition( m_BC_outlet,-1,			IS(IS::e_VALUE,0),	IS(IS::e_END),									IS(IS::e_RANGE,0,1),	IS(IS::e_VALUE,m_k_inlet) );
	
	// symmetry
	SetBoundaryCondition( m_BC_sym,1,				IS(IS::e_VALUE,1),	IS(IS::e_ALL),									IS(IS::e_BEGIN),		IS(IS::e_ALL) );
	
	// heated
	SetBoundaryCondition( m_BC_heated,1,			IS(IS::e_VALUE,2),	IS(IS::e_TRIM,1,1),								IS(IS::e_TRIM,0,1),		IS(IS::e_VALUE,0) );
	
	// interior wall
	PRNTLOC;
	SetConnectionBoundaryConditionAuto(m_BC_int_wall,m_VC_solid,m_VC_fluid);
	/*
	SetConnectionBoundaryCondition( m_BC_int_wall,	IS(IS::e_VALUE,0),	IS(IS::e_TRIM,2,2),								IS(IS::e_ALL),			IS(IS::e_VALUE,1) ); // channel side walls
	
	SetConnectionBoundaryCondition( m_BC_int_wall,	IS(IS::e_VALUE,1),	IS(IS::e_TRIM,1,1),								IS(IS::e_RANGE,1,2),	IS(IS::e_RANGE,2,3) ); // header wall
	
	SetConnectionBoundaryCondition( m_BC_int_wall,	IS(IS::e_VALUE,2),	IS(IS::e_MOD_AND_TRIM,2,m_x_channelMod,1,1),		IS(IS::e_ALL),			IS(IS::e_VALUE,1) ); // channel bottom
	SetConnectionBoundaryCondition( m_BC_int_wall,	IS(IS::e_VALUE,2),	IS(IS::e_MOD_AND_TRIM,2,m_x_channelMod,1,1),		IS(IS::e_VALUE,1),		IS(IS::e_VALUE,2) ); // channel top
	
	SetConnectionBoundaryCondition( m_BC_int_wall,	IS(IS::e_VALUE,2),	IS(IS::e_MOD_AND_TRIM,2,m_x_wallMod,1,1),			IS(IS::e_VALUE,0),		IS(IS::e_VALUE,2) ); // header outlet channel wall top
	SetConnectionBoundaryCondition( m_BC_int_wall,	IS(IS::e_VALUE,2),	IS(IS::e_MOD_AND_TRIM,2,m_x_wallMod,1,1),			IS(IS::e_VALUE,2),		IS(IS::e_VALUE,2) ); // header inlet channel wall top
	*/
	
}













