#include <iostream>
using namespace std;
class Verbose {
	public:
		Verbose() {
			cout << "ctor" << endl;
		}
		Verbose(string name): _M_name(name+" ") {
			cout << _M_name << "ctor" << endl;
		}
		~Verbose() { cout << _M_name << "dtor" << endl; }
		void	speak() {
			cout << _M_name << "hello" << endl;
		}
	private:
		std::string _M_name;
};

