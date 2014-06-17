#include <stdlib.h>

#include "../../csvread/csvread.h"

using namespace std;

int main()
{
	vector<vector<string> > s = csvread("export.csv");
	
	cout << s.size() << endl;
	
	for ( int a = 0; a < 6; a++ )
	{
		for ( int b = 0; b < s.at(a).size(); b++ )
		{
			cout << s.at(a).at(b) << " ";
		}
		cout << endl;
	}
	
	cout << endl;
	
	for ( int a = 0; a < 6; a++ )
	{
		for ( int b = 0; b < s.at(a).size(); b++ )
		{
			cout << atof(s.at(a).at(b).c_str()) << " ";
		}
		cout << endl;
	}
	
	return 0;
}

