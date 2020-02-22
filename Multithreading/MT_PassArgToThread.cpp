#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
int shared;
mutex mutObj;

int fun1( const string str){
    cout << std::this_thread::get_id()<<"fun1(): "<< str << endl;
}

int fun2(int x){
    cout << std::this_thread::get_id()<< "fun2(): "<< x << endl;
    x = 10;
}

int fun3(int &x){
    cout << std::this_thread::get_id()<< "fun3(): "<< x << endl;
    x = 20;
}


int main(){

    int x = 5;
    std::thread t1(fun1, "I am in Thread1.");
    //std::thread t2(fun2, (x));  

    /*  You can not simply pass a referance of a variable to a thread 
      in order to pass a ref to a thread, c++11 has std::ref()*/
    std::thread t3(fun3, std::ref(x));
    //std::thread t3(fun3, (&x));

    int *p = new int(99);
    //below commented lines will give compile time error
    //std::thread t4(fun2, p);    
    //std::thread t4(fun2, *p);  
    //std::thread t5(fun2, std::ref(p));    
    std::thread t6(fun3, std::ref(*p));    

    //std::this_thread::sleep_for(std::chrono::seconds(2));
    t1.join();
    //t2.join();
    t3.join();
    //t4.join();
    //t5.join();
    t6.join();

    cout << "main() x: "<<x << endl;
    cout << "main() *p: "<<*p << endl;

    return 0;
}