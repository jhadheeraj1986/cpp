#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
using namespace std;

int count;
mutex mutObj;
vector<int> que;
condition_variable CondVar;

int fun1(){
	
	std::this_thread::sleep_for(std::chrono::seconds(2));
	while(count < 100){
		cout<<"Fun1: count: "<<count<<endl;
		count++;
		unique_lock<mutex> lock(mutObj);
		que.push_back(count);
		if(count == 50){
		 	std::this_thread::sleep_for(std::chrono::seconds(5));}
		CondVar.notify_all();
	}
}

int fun2(){
	unique_lock<mutex> lock1(mutObj);
	while(count < 100){
		if((que.size() == 0)){
			CondVar.wait(lock1);
		}
		cout<<"fun2: que size:  "<< que.size()<<endl;
		for(auto itr : que){
			if(que.size() > 0){
				cout<<"Count: "<<itr<<endl;
				que.pop_back();
			}
		}
	}
}

int main(){
	cout<<"Inside Main()"<<endl;
    std::thread t1(fun1);
    std::thread t2(fun2);
	cout <<"Joining to main()"<<endl;
    t1.join();
    t2.join();

    return 0;
}

