#include <iostream>
#include <string>
#include <regex>
#include <functional>
#include <string.h>
#include <vector>

using namespace std;

int scan_to( char const * cstr, int a, char c )
{
	while ( a < strlen(cstr) )
	{
		//cout << a << " \"" << cstr[a] << "\"" << endl;
		if ( cstr[a] == '(' )
		{
			a = scan_to( cstr, ++a, ')' );
		}
		if ( cstr[a] == '[' )
		{
			a = scan_to( cstr, ++a, ']' );
		}
		if ( cstr[a] == '<' )
		{
			a = scan_to( cstr, ++a, '>' );
		}
		
		if ( cstr[a] == c )
		{
			return a;
		}
		
		++a;
	}
	
	return a;
}

void funcsig( char const * cstr_base )
{
	cout << cstr_base << endl;
	int l = strlen(cstr_base);
	cout << "len=" << l << endl;
	char cstr[l+1];
	cstr[l] = '\0';
	
	memcpy( cstr, cstr_base, l );
	
	
	vector<int> loc;
	loc.push_back(0);
	
	int loc_func = 0;
	
	int a = 0;
	while ( a < strlen(cstr_base) )
	{
		a = scan_to( cstr_base, a, ' ' );
		
		if ( a >= strlen(cstr_base) ) break;
		
		cstr[a] = '\0';
		
		loc.push_back(a+1);
		
		++a;
	}
	
	for( int b = 0; b < loc.size(); ++b )
	{
		cout << loc.at(b) << "\"" << cstr+loc.at(b) << "\"" << endl;
	}
	
	auto it = loc.end() - 1;
	if ( cstr_base[*it] == '[' )
	{
		loc_func = *(--it);
	}
	else
	{
		loc_func = *(it);
	}
	cout << "func=\"" << cstr+loc_func << "\"" << endl;
	/*
	   regex base_regex("[^\\s]");
	   smatch base_match;

	   regex_match( str, base_match, base_regex );

	   for ( int a = 0; a < base_match.size(); a++ )
	   {
	   ssub_match base_sub_match = base_match[a];
	   cout << base_sub_match.str() << endl;
	   }*/

}

class foo
{
	public:
		virtual function<int(int)> doit( function<int(int)> )
		{
			funcsig( __PRETTY_FUNCTION__ );
			return function<int(int)>();
		}
};

template <typename A> void doit(A)
{
	funcsig( __PRETTY_FUNCTION__ );
}

int bar( int )
{
	return 0;
}

int main()
{
	foo f;

	function<int(int)> func = f.doit( function<int(int)>(bar) );

	doit<int>(0);

	return 0;
}
