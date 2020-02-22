#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
int shared;
mutex mutObj;

int fun1(){

    //std::this_thread::sleep_for(std::chrono::seconds(2));
    for(;shared < 10;){
        if(0 == (shared%2)){
            mutObj.lock();
            shared++;
            cout<< std::this_thread::get_id() <<" fun1(): "<< shared<<endl;
            mutObj.unlock();
        }
    }
}

int fun2(){

    //std::this_thread::sleep_for(std::chrono::seconds(2));
    for(;shared < 10;){
        if(0 != (shared%2)){
            mutObj.lock();
            shared++;
            cout<< std::this_thread::get_id() <<"  fun2(): "<< shared<<endl;
            mutObj.unlock();
        }
    }
}


int main(){
    std::thread t1(fun1);
    std::thread t2(fun2);

    t1.join();
    t2.join();

    return 0;
}