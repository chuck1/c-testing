#include <unistd.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

std::mutex pm;
template<typename T>
void	print(T && t)
{
	std::lock_guard<std::mutex> lk0(pm);
	std::cout << t << std::endl;
}

template<typename T>
struct async_future
{
	struct error
	{
	};
	async_future():
		ready(false)
	{}
	void		wait()
	{

		std::unique_lock<std::mutex> lk(m);
		
		// check if ready
		if(ready) {
			return;
		}
		
		// what to do if not ready
	
		cv.wait(lk);
		
		// should new be ready
		if(!ready) {
			throw error();
		}
	}
	void		set_value()
	{
		std::lock_guard<std::mutex> lk(m);
		ready = true;
		cv.notify_all();
	}
private:
	std::condition_variable		cv;
	std::mutex			m;
	bool				ready;
};

int main()
{
	{
		async_future<void> f;

		std::thread t0([&]() { f.wait(); });
		std::thread t1([&]() { f.wait(); });
		std::thread t2([&]() { f.wait(); });

		sleep(1);	

		f.set_value();

		t0.join();
		t1.join();
		t2.join();
	}

	{
		std::promise<void> p;
		std::future<void> f = p.get_future();

		std::thread t0([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t1([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t2([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t3([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t4([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t5([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t6([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t7([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t8([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t9([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t10([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });
		std::thread t11([&]() { std::thread::id this_id = std::this_thread::get_id(); print(this_id); f.wait(); });

		sleep(1);	

		p.set_value();

		t0.join();
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
		t7.join();
		t8.join();
		t9.join();
		t10.join();
		t11.join();

	}

}


