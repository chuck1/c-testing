#ifndef _MODEL_5_H
#define _MODEL_5_H

#include "../Model.h"

/*
enum ParameterName
{
	e_X_CHANNEL				= (1 << 0),
	
};
*/

class Model_5: public Model
{
public:
	Model_5(){}
	Model_5( double x_channel, double x_wall, 
		double y_header_inlet, double y_header_outlet, 
		double y_heated, double z_flux_plate, double z_channel, double z_header, double x_header_inlet_ext, double x_header_outlet_ext, int n, string title, string root );
	
	void PopulateVariableMap();
	void ProcessVariables();
	
	void Process();
	
	void SetVolumeConditions();
	void SetBoundaryConditions();
	
	
private:
	// geometric variables in additional to those inherited from Model
	
	
	// variables in additional to those inherited from Model
	int m_k_inlet;
	
};

#include "Model_5.cpp"

#endif



