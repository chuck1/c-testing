
#include <iostream>

using namespace std;

int main()
{
	char input[] = "hi my name is charles";
	
	int n = sizeof(input) / sizeof(char) - 1;

	char* c0 = input + n - 1;
	
	while(1) {
		if(c0 == input) {
			cout << "'" << c0 << "'" << endl;
			break;
		}
		if(*c0 == ' ') {
			cout << "'" << (c0+1) << "'" << endl;

			*c0 = '\0';
		}
		--c0;
	}
}

