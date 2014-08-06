
#include <errno.h>
#include <string.h>
#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include <iostream>


#include "stat.hpp"

int main() {

	string dir = string(".");

	struct stat_dir ds;



	ifstream is(".stat", ifstream::binary);
	if(!is.is_open()) {
		exit(1);
	}
	binary_iarchive ar(is);

	ds.serialize(ar);

	cout
		<< setw(32) << ds.name
		<< setw(16) << ds.size()
		<< endl;

	for (auto d : ds.dirs) {
		cout
			<< setw(32) << d.name
			<< setw(16) << d.size()
			<< endl;
	}
	for (unsigned int i = 0;i < ds.files.size();i++) {
		cout
			<< setw(32) << ds.files[i].name
			<< setw(16) << ds.files[i].size
			<< endl;
	}


	
	return 0;
	
}



