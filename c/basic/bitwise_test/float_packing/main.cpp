#include <cmath>
#include <iostream>
#include <iomanip>
#include <bitset>

using namespace std;

int main() {

	
	// 24 bits

	unsigned char a = 1;
	unsigned char b = 2;
	unsigned char c = 3;
	unsigned char d = 4;

	int abcd = (a << 18) | (b << 12) | (c << 6) | d;
	
	cout << setw(8) << "a" << setw(16) << hex << (int)a << endl;
	cout << setw(8) << "b" << setw(16) << hex << (int)b << endl;
	cout << setw(8) << "c" << setw(16) << hex << (int)c << endl;
	cout << setw(8) << "d" << setw(16) << hex << (int)d << endl;

	cout << setw(8) << "abcd" << setw(16) << hex << (int)abcd << endl;

	cout << setw(8) << "abcd" << setw(16) << (float)abcd << endl;

}


