#include <iostream>
#include <string>

using namespace std;

int main () {
	
	
	string s("ab");
	
	cout << s << endl;
	
	s.push_back('c');
	
	cout << s << endl;

	s.pop_back();
	
	cout << s << endl;

}

