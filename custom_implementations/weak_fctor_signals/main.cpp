#include <iostream>
#include <memory>
#include <boost/signals2.hpp>
#include <boost/signals2/signal_type.hpp>

class foo {
	public:
		foo() { std::cout << "foo c" << std::endl; }
		~foo() { std::cout << "foo d" << std::endl; }


		void func() { std::cout << "func" << std::endl; }
};

class wrapper {
	public:
		wrapper() { std::cout << "wrapper c" << std::endl; }
		~wrapper() { std::cout << "wrapper d" << std::endl; }

		
		void func() {
			std::cout << "wrapper func" << std::endl;
			auto s = w_.lock();
			if(s) {
				s->func();
			} else {
				c_.disconnect();
			}
		}
		
		boost::signals2::connection c_;
		std::weak_ptr<foo> w_;
};

void bar() { std::cout << "sig" << std::endl; }

int main () {

	typedef boost::signals2::signal<void()> Sig_Type;
	
	Sig_Type sig;

	sig.connect(&bar);

	boost::shared_ptr<wrapper> w(new wrapper);

	{


		std::shared_ptr<foo> s(new foo);

		w->w_ = s;

		w->c_ = sig.connect(
				Sig_Type::slot_type(&wrapper::func, w.get()).track(w)
				);

		sig();

	}
	sig();
	sig();

	std::cout << "exit" << std::endl;

	return 0;
}

