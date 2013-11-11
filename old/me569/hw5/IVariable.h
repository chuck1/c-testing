#ifndef _IVARIABLE_H
#define _IVARIABLE_H

#include <vector>

#include "Branch.h"

class HW5;

template <class T>
class IVariable
{
public:
	IVariable(HW5* parent, const char* filename);
	bool Init();
	Branch<T>* Get();
	bool Ensure();
	
protected:
	
	virtual bool VEnsure(){return false;}
	virtual bool VInit(){return false;}
	
	Branch<T>* 		m_mat;
	string			m_filename;
	HW5*			m_parent;
};

class u: public IVariable<double>
{
public:
	u(HW5* parent);
	
	bool VEnsure();
	bool VInit();
	bool Load();
};

class umean: public IVariable<double>
{
public:
	umean(HW5* parent);
	
	bool VEnsure();
	bool VInit();
};

class up: public IVariable<double>
{
public:
	up(HW5* parent);
	
	bool VEnsure();
	bool VInit();
};

class filenames: public IVariable<string>
{
public:
	bool VEnsure();
	bool VInit();
	bool Load();
};

#endif

