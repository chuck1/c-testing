#ifndef _MODEL_4_H
#define _MODEL_4_H

class Model_4: public Model
{
public:
	Model_4():Model(){}
	
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

#include "Model_4.cpp"

#endif


