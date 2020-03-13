#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <shared_mutex>
#include <ctime>
using namespace std;

int shared;
//shared_timed_mutex mutObj;
mutex mutObj;
int count;

void fun1(){
        while(count < 10){
            cout<<"Fun1:threadID"<<this_thread::get_id()<<" count: "<<count<<endl;
            count++;
	    {
		mutObj.lock();
            	shared++;
		mutObj.unlock();
	    }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
}

void fun2(){
        while(count < 10){
		mutObj.lock();
//		mutObj.lock_shared();
	        cout<<"fun2: ThreadID: "<<this_thread::get_id() <<" shared:  "<< shared<<" count: "<<count<<endl;
		count++;
	    	std::this_thread::sleep_for(std::chrono::seconds(1));
	    	mutObj.unlock();
//	    	mutObj.unlock_shared();
        }
}

void fun3(){
        while(count < 10){
		mutObj.lock();
//		mutObj.lock_shared();
            	cout<<"fun3: ThreadID: "<<this_thread::get_id() <<" shared:  "<< shared<<" count: "<<count<<endl;
	    	count++;
	    	std::this_thread::sleep_for(std::chrono::seconds(1));
	    	mutObj.unlock();
//	    	mutObj.unlock_shared();
        }
}



int main(){
    time_t result = std::time(nullptr);
    cout <<"Start time:"<< std::asctime(std::localtime(&result))<< result <<endl;

    cout<<"Inside Main()"<<endl;
    count = 0;
    thread t1(fun1);
//    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    thread t2(fun2);
    thread t3(fun3);
    cout <<"Joining to main()"<<endl;
    
    t1.join();
    t2.join();
    t3.join();
	
    time_t result1 = std::time(nullptr);
    std::cout <<"End Time: "<< std::asctime(std::localtime(&result))<< result <<endl;
    std::cout<<"Time taken: "<<result1-result<<endl;

    return 0;
}





