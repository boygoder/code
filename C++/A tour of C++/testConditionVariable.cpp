#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;

class Message { // object to be communicated 
// ... 
}; 

queue<Message> mqueue; // the queue of messages 

condition_variable mcond; // the variable communicating events 
mutex mmutex; // for synchronizing access to mcond

void consumer() 
{ 
	while(true) { 
		unique_lock lck {mmutex}; // acquire mmutex 
		mcond.wait(lck,[] { return !mqueue.empty(); }); // release lck and wait; 
														// re-acquire lck upon wakeup 
														// don’t wake up unless mqueue is non-empty 
		cout <<"Waiting……\n";
		auto m = mqueue.front(); // get the message 
		cout <<"Finish consumer……\n" << endl;
		mqueue.pop(); 
		lck.unlock(); // release lck 
					  // ... process m ... 
	} 
}

void producer() 
{ 

	while(true) { 
		Message m; // ... fill the message ... 
		scoped_lock lck {mmutex}; // protect operations 
		mqueue.push(m); 
		std::cout << "Notifying true change...\n";
		mcond.notify_one(); // notify 
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	//release lock (at end of scope) 
}

int main()
{
	thread t1(consumer),t2(producer);
	t1.join();
	t2.join();
	return 0;
}