#include "../../../mylib.h"

int main()
{
	Engr::TF::Material m("ms1");
	
	m.Print();
	
	cout << "density=" << m.Get("density","T",800) << endl;
	
	m.WriteFluentDatabase();
	
	return 0;
}
