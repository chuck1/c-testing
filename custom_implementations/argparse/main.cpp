#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>

struct Tag
{
	std::string	short_;
	std::string	long_;
};

struct Arg
{
	virtual std::string	name() = 0;
};

struct Arg_tag: Arg
{
	// -a --apple
	Tag	tag_;
	virtual std::string	name()
	{
		return tag_.short_;
	}
};

struct Arg_positional: Arg
{
	// file
	std::string	name_;
};

typedef std::vector< std::string > vec_str;

struct Args
{
	void	help()
	{
	}

	std::map< std::string, Arg* >	arg_map_;
};


Tag	process_tag(std::string w)
{
	Tag t;
	if(w[1] == '-')
	{
		assert(w.size() > 2);
		t.long_ = w.substr(2);
	}
	else
	{
		assert(w.size() > 1);
		t.short_ = w.substr(1);
	}
	return t;
}

Arg*	make_arg(vec_str words)
{
	std::cout << "make_arg" << std::endl;
	for(auto w : words)
		std::cout << "'" << w << "'" << std::endl;
	
	assert(!words.empty());
	
	if(words[0][0] == '-')
	{
		Tag t = process_tag(words[0]);
		Arg_tag* a = new Arg_tag;
		return a;
	}

	assert(0);
	return 0;
}

Args Parse(int ac, char ** av, char const * format)
{
	vec_str words;

	Args ret;

	char * buf = new char[strlen(format)+1];
	strcpy(buf, format);

	char * c = buf;
	char * head = buf;
	for(; c < (buf + strlen(format) + 1); c++)
	{
		std::cout << *c << std::endl;
		if(*c == ' ' || *c == 0)
		{
			*c = 0;
			words.push_back(head);
			head = c+1;
		}
	}
	for(auto w : words)
		std::cout << w << std::endl;

	vec_str temp;
	for(int i = 0; i < words.size(); i++)
	{
		if(words[i][0] == '-')
		{
			std::cout << "tag " << words[i] << std::endl;
			if(temp.empty()) temp.push_back(words[i]);
			else {
				Arg* a = make_arg(temp);
				ret.arg_map_[a->name()] = a;
				temp.clear();
				temp.push_back(words[i]);
			}
		}
		else
		{
			temp.push_back(words[i]);
		}
	}
	
	if(!temp.empty())
	{
		Arg* a = make_arg(temp);
		ret.arg_map_[a->name()] = a;
	}

	Args.help();

	return ret;
};


int main(int ac, char ** av)
{

	Args args = Parse(ac,av,"-a a -b --hello");





}

