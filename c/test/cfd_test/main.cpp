
#include "../../mylib/mylib.h"

int main() {
	Engr::TF::Flow::CFD cfd;
	
	cfd.GenerateSquare(10,1);
	
	
	
	
	
	
	
	//cfd.m_mesh->Print();
	
	
	
	cfd.Iter();
	
	
	cfd.Write();
	
	
	
	
	
	
	return 0;
}