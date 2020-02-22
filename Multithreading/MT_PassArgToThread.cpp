#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
int shared;
mutex mutObj;

int fun1( const string str){
    cout << str << endl;
}

int fun2(int &x){
    cout << x << endl;
    x = 10;
}


int main(){

    int x = 5;
    std::thread t1(fun1, "I am in Thread1.");
    /*  You can not simpaly pass a referance of a variable to a thread 
        this line will give compile time error. Uncomment to check*/
    //std::thread t2(fun2, (x));  

    /*  in order to pass a ref to a thread, c++11 has std::ref()*/
    std::thread t3(fun2, std::ref(x));

    int *p = new int();
    //below commented lines will give compile time error
    //std::thread t4(fun2, p);    
    //std::thread t4(fun2, *p);  
    //std::thread t5(fun2, std::ref(*p));    
    std::thread t6(fun2, std::ref(*p));    

    cout << "main() "<<x << endl;
    t1.join();
    //t2.join();
    t3.join();
    //t4.join();
    //t5.join();
    t6.join();


    return 0;
}