#include <iostream>

using namespace std;

struct pass {template<typename ...T> pass(T...) {}};

class msg_base {};

template<typename... Args> class msg: public msg_base
{
public:
	void write(void*){}
	inline void write_expand(Args&... args)
	{
		pass{(args.write(this), 1)...};
	}
};

struct ser1 {
	void write(msg_base*){cout << "ser1\n";}
};
struct ser2 {
	void write(msg_base*){cout << "ser2\n";}
};









int main() {
	
	msg<ser2,ser1> m;
	
	ser1 a;
	ser2 b;

	m.write_expand(b,a);
}


