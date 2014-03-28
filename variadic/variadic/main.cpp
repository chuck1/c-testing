#include <stdio.h>
#include <assert.h>
#include <memory>
#include <tuple>
#include <vector>

// for unpacking tuple
template<int ...> struct seq { };

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> { };

template<int ...S> struct gens<0, S...> { typedef seq<S...> type; };

// for calling functions

struct pass {
	template<typename ...T> pass(T...) {}
};

// pointer

template<typename T> void reset(std::shared_ptr<T>& t) {
	printf("new\n");
	t.reset(new T);
}

// tuple

template<int... S, typename... Args> void reset_tuple(seq<S...>, std::tuple<Args...>& tup) {
	pass{(reset(std::get<S>(tup)), 1)...};
}

template<typename... Args> void reset_tuple(std::tuple<Args...>& tup) {
	typename gens<sizeof...(Args)>::type s;
	reset_tuple(s, tup);
}

// main
class message: public std::enable_shared_from_this<message> {};



typedef std::shared_ptr<message> message_shared;

template<class... Args> struct vector_ext {
	typedef std::tuple<std::shared_ptr<Args>...> tup;
	typedef std::vector<tup> vec;
	typedef typename vec::size_type size_type;
	typedef typename gens<sizeof...(Args)>::type seq_t;


	template<int... S> void write_expand(seq<S...>, tup t, std::shared_ptr<message> msg) {
		pass{(std::get<S>(t)->write(msg), 1)...};
	}
	template<int... S> void read_expand(seq<S...>, tup t, std::shared_ptr<message> msg) {
		pass{(std::get<S>(t)->read(msg), 1)...};
	}
	
	template<int... S> size_t size_expand(seq<S...>, tup t, message_shared msg) {
		size_t s = 0;
		pass{(s += std::get<S>(t)->write(msg), 1)...};
		return s;
	}
	
	void write(message_shared msg) {
		seq_t s;
		tup t;
		for(auto it = vec_.begin(); it != vec_.end(); ++it) {
			t = *it;
			write_expand(s, t, msg);
		}
	}
	void read(message_shared msg) {
		size_type size = 0;
		
		seq_t s;
		tup t;
		for(size_type i = 0; i < size; ++i) {
			reset_tuple(t);
			read_expand(s, t, msg);
			vec_.push_back(t);
		}
	}
	
	vec vec_;
};




template<typename... Args> struct message_ext {
	typedef typename gens<sizeof...(Args)>::type seq_t;

	message_ext() {
		//typename gens<sizeof...(Args)>::type s;
		seq_t s;
		reset_tuple(s, tup_);
	}

	void write(message_shared msg) {
		seq_t s;
		write_expand(s, msg);
	}

	template<int... S> void write_expand(seq<S...>, message_shared msg) {
		pass{(std::get<S>(tup_)->write(msg), 1)...};
	}
	
	std::tuple<std::shared_ptr<Args>...> tup_;
};



template<int i> struct ser {
	void write(std::shared_ptr<message>) {
		printf("ser%i write\n", i);
	}
	size_t size() {
		return 0;
	}
};

typedef message_ext<ser<3>,vector_ext<ser<2>,ser<1>> > me1;

int main() {

	//std::shared_ptr<vector<ser1> > v1(new vector<ser1>);
	//std::shared_ptr<ser2> s2(new ser2);

	std::shared_ptr<me1> m(new me1);
	
	
	printf("emplace_back\n");
	
	auto vec = std::get<1>(m->tup_);
	assert(vec);
	
		
	vec->vec_.emplace_back(new ser<2>,new ser<1>);
	printf("emplace_back\n");
	vec->vec_.emplace_back(new ser<2>,new ser<1>);
	
	
	message_shared msg(new message);
	
	printf("write\n");
	m->write(msg);
}








