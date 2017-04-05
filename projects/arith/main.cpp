#include <math.h>
#include <string.h>
#include <stdio.h>

template<typename T>
T	max(T a, T b)
{
	if(a > b) return a;
	return b;
}
template<typename T>
T	min(T a, T b)
{
	if(a < b) return a;
	return b;
}

struct SHORT
{
	union {
		unsigned short s;
		struct {
			unsigned char c[2];
		};
	};
};

class UINT
{
public:
	UINT(unsigned int const & i):
		_M_n(sizeof(unsigned int))
	{
		_M_bytes = new unsigned char[_M_n];
		memcpy(_M_bytes, &i, _M_n);
	}
	/* copy b and set number of bytes to n */
	UINT(UINT const & b, int n):
		_M_n(n)
	{
		_M_bytes = new unsigned char[_M_n];

		memcpy(_M_bytes, b._M_bytes, b._M_n);
	}
	UINT 	operator+(UINT const & b)
	{
		unsigned int n0 = min(_M_n, b._M_n);
		unsigned int n = max(_M_n, b._M_n);
		

		UINT ret(*this, n + 1);
		
		unsigned char carry = 0;
		SHORT s;
		
		unsigned int i = 0;
		for(; i < n0; ++i) {
			
			s.s = _M_bytes[i] + b._M_bytes[i] + carry;
			
			carry = s.c[1];
			
			ret._M_bytes[i] = s.c[0];
			
			//ret._M_bytes[i] = _M_bytes[i] + b._M_bytes[i];
			//__builtin_add_overflow(_M_bytes[i], b._M_bytes[i], ret._M_bytes[i]);
		}
		for(; i < n; ++i) {
			if(_M_n > b._M_n) {
				s.s = _M_bytes[i] + carry;
			} else {
				s.s = b._M_bytes[i] + carry;
			}
			
			carry = s.c[1];
			
			ret._M_bytes[i] = s.c[0];
		}
		// last step
		if(_M_n > b._M_n) {
			s.s = _M_bytes[i] + carry;
		} else {
			s.s = b._M_bytes[i] + carry;
		}

		carry = s.c[1];

		ret._M_bytes[i] = s.c[0];


		return ret;
	}

	char*	str()
	{
		char* buf = new char[2*_M_n+1];
		char buf0[3];
		for(unsigned int i = 0; i < _M_n; i++) {
			sprintf(buf0, "%02X", _M_bytes[i]);
			//printf("%s %u %u\n", buf0, i, (2 * _M_n) - (2 * i) - 2);
			memcpy(buf + ((2 * _M_n) - (2 * i) - 2), buf0, 2);
		}
		buf[2*_M_n] = '\0';
		return buf;
	}

	unsigned char *		_M_bytes;
	unsigned int		_M_n;
};



int main()
{
	UINT a(0xFF000000);
	UINT b(0x01000000);

	UINT c = a + b;
	UINT d = c + a;

	printf("%16s\n", a.str());
	printf("%16s\n", b.str());
	printf("%16s\n", c.str());
	printf("%16s\n", d.str());

	return 0;

	SHORT a3;

	unsigned char a0 = 0xFF;
	unsigned char a1 = 0xFF;
	unsigned char a2 = a0+a1;
	a3.s = a0+a1;

	//__builtin_add_overflow(a0, a1, &a2);



	printf("%i\n", a2);
	printf("%i\n", a3.s);
	printf("%i\n", a3.c[0]);
	printf("%i\n", a3.c[1]);
}

