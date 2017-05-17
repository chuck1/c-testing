#ifndef _MODEL_2_H
#define _MODEL_2_H

#include "../Model.h"

class Model_2: public Model
{
public:
	Model_2():Model(){}
	
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

#include "Model_2.cpp"

#endif

