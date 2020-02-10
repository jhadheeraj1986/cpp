#include <iostream>
#include <thread>
using namespace std;


/******Create Thread with function pointer**********/
/*void fun1()
{
	cout << "This is fun1()" <<  endl;
}

int main()
{
	thread t1(fun1);
	t1.join();
	cout << "This is main()" << endl;
}
*/

/******Create Thread with function Object(functor)**********/
/*class counter
{
	public:
	counter(int i) : iID(i)
	{	}

	void operator() () const
	{
		cout << "This is Counter object no: " << iID << endl;
	}

	private:
	int iID;
};

int main()
{
	thread t1{counter {1}};
	counter obj(2);
	thread t2(obj);
	thread t3(counter(3));

	t1.join();
	t2.join();
	t3.join();
}*/

/******Create Thread with Member Function**********/
/*class temp
{
	public:
	temp(int i) : mID(i) {}
	void func()
	{ cout << "This is func()" << endl;}

	private:
	int mID;
};

int main()
{
	temp obj(1);
	thread t1(&temp::func, &obj);
	t1.join();
	cout<<"This is main()"<<endl;
}*/

/******Thread Local storage**********/
/*thread_local int x;	//mark variable as local to thread meanseach thread will have it own variable.
int y;

void func(int i)
{
	//x = i;
	cout<<"add of x = " << &x<<endl;
	cout<<"add of y = " << &y<<endl;
}

int main()
{
	x = 11;
	y = 10;
	thread t1(func, 1);
	thread t2(func, 2);

	t1.join();
	t2.join();
}*/



