#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdio.h>

using namespace std;

void *PrintHello(void *threadID)
{
    long tid;
    tid = (long)threadID;
    cout <<"Hello! This is thread "<<tid<<endl;
    pthread_exit(NULL);
}

int main(){
	pthread_t threads[5];
    int rc;
    int i;

    for(i=0; i<5; i++)
    {
        cout<<"main(): creating thread "<< i<< endl;
        rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
        if (rc)
        {
            cout << "Error: unable to create thread" <<rc<<endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

