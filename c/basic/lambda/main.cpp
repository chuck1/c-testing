#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	
	vector<int> v;

	for_each(v.begin(), v.end(), [] (int i) {
		cout << i << endl;
	} );


}

