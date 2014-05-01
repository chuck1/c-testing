#include <iostream>
#include <sstream>

using namespace std;

void ReadString(stringstream& ss, string& s) {
	char c;
	while(1) {
		ss.get(c);
		//cout << c << endl;
		if(c==0) break;
		s.push_back(c);
	}
	
}

void WriteString(stringstream& ss, string& s) {
	
	ss.write(s.c_str(),s.size());

	cout << ss.str().size() << endl;
	
	ss.write("\0",1);
	
	cout << ss.str().size() << endl;

}

int main() {
	
	stringstream oss;//(std::string("some\0data\0"));
	
	std::string out1("Hello");
	//char out1[] = "Hello";
	std::string out2("World");

	cout << oss.str().size() << endl;
	
	WriteString(oss,out1);
	WriteString(oss,out2);
	
	// copy
	stringstream iss(oss.str());


	std::string in1;
	std::string in2;

	ReadString(iss,in1);
	ReadString(iss,in2);

	cout << in1 << endl;
	cout << in2 << endl;
}


