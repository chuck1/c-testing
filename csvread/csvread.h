#ifndef _CSV_READ_H
#define _CSV_READ_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;


vector<vector<string> > csvread(string filename)
{
	vector<vector<string> > ret;
	
	ifstream file ( filename.c_str() );
	
	string line;
	string s;
	
	while ( file.good() )
	{
		vector<string> ret_line;
		
		getline ( file, line );
		
		line = line.substr( 0, line.find_last_not_of( "\n\r" ) + 1 );
		
		stringstream ss(line);
		
		while (getline ( ss, s, ',' ))
		{
			ret_line.push_back(s);
			//cout << "000" << s << "000" << endl;
		}
		
		ret.push_back(ret_line);
	}
	
	return ret;
}



#endif