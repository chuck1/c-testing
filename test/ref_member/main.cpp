
#include <stdio.h>



class foo {
public:
	foo(): v{0,0,0,0}, x(v[0]), s{1,1} { //row{Row(v), Row(v+2)}
		
	}

	int v[4];
	int &x;

	S s[2];

	/*
	struct Row {
		Row( int* v ): x(v[0]), y(v[1]) {
		}
		int &x;
		int &y;
	} row[2];
	*/

};



int main() {
	foo f;

	return 0;
}