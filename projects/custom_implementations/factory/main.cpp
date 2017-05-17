#include <iostream>
#include <memory>
#include <map>
using namespace std;

template<class T> class Factory {
	private:
	public:
		struct __base_function {
			virtual ~__base_function() {}
		};
		template<class... A> struct __function: __base_function {
			__function(function<T*(A...)> f): f_(f) {}
			function<T*(A...)>		f_;
		};
	public:
		Factory() {}
		virtual ~Factory() {}

		template<class... Args> void	add(long int hash_code, function<T*(Args...)> f) {
			std::shared_ptr<__base_function> b(new __function<Args...>(f));
			
			map_[hash_code] = b;
		}

		template<class... Args> T*	alloc(long hash_code, Args&&... args) {
			auto it = map_.find(hash_code);
			if(it == map_.cend()) {
				cout << "no alloc for " << hash_code << endl;
				return 0;
			} else {
				std::shared_ptr< __function<Args...> > f = std::dynamic_pointer_cast< __function<Args...> >(it->second);

				if(f == NULL) {
					cout << "wrong arg list" << endl;
					return 0;
				}
				
				return (f->f_)(forward<Args>(args)...);
			}
		}

		//static shared_ptr< Factory<T> >				global_;

		map<long int, shared_ptr<__base_function> >		map_;
};


class foo {
	private:
		friend void setup(Factory<foo>& f);
		friend class Factory<foo>;
		foo(int) {}
	//public:
		static foo* alloc(int i) {
			cout << "alloc " << i << endl;
			return new foo(1);
		}

};

void setup(Factory<foo>& f) {
	f.add(1, std::function<foo*(int)>(&foo::alloc));
}

class der1: public Factory<foo> {
	
};

class der2: public Factory<foo> {
	
};

//template<> shared_ptr< Factory<foo> > Factory<foo>::global_(new Factory<foo>);

int main() {

	Factory<foo> fact;
	
	der1 d;

	setup(d);
	setup(

	foo* f;
       	
	f = fact.alloc(1,1);
	f = fact.alloc(1,2);
	f = fact.alloc(2,2);
	f = fact.alloc(1);

	f = d.alloc(1,1);



}




