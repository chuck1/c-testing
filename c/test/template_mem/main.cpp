#include <iostream>
#include <vector>

using namespace std;



template <class T> class Vec {
public:
	void	Create(T*&);


			vector<T*> m_v;
};

template class Vec<int>;
template class Vec<double>;



class Derived: public Vec<int>, public Vec<double> {
public:
	
};





template <class T> void	Vec<T>::Create(T*& t) {
	t = new T;
	m_v.push_back(t);
}





int	main() {
	Derived der;

	double* d = 0;

	der.Vec<double>::Create(d);



	cout << d << endl;
	
	cout << der.Vec<double>::m_v.at(0) << endl;

	return 0;
}



