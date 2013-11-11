#ifndef _Model_6_H
#define _Model_6_H

#include <Model/Model.h>

class Model_6: public Model
{
public:
	Model_6():Model(){}
	
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


#endif










