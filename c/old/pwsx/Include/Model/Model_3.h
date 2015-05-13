#ifndef _MODEL_3_H
#define _MODEL_3_H

class Model_3: public Model
{
public:
	Model_3():Model(){}
	
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

#include "Model_3.cpp"

#endif


