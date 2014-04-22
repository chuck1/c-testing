#include <map>

using namespace std;

int main() {
	
	map<int,int> m;

	m[0] = 0;
	m[1] = 1;
	
	map<int,int>::iterator a = m.find(0);
	
	
	map<int,int>::const_iterator it = m.erase(a);

	//map<int,int>::iterator it = m.erase(a);

	
}



