#ifndef _MODEL_1_H
#define _MODEL_1_H

class Model_1: public Model
{
public:
	Model_1():Model(){}
	
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


