#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void *wait(void *t)
{
    int i;
    long tid;

    tid = (long)t;
    sleep(2);
    cout << "Sleepint in thread: " << tid <<endl;
    pthread_exit(NULL);
}

int main()
{
    int rc, i;
    pthread_t thread[5];
    pthread_attr_t attr;
    void *status;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for(i=0; i<5; i++)
    {
        cout<< "main(): Creating thread: " << i<<endl;
        rc = pthread_create(&thread[i], NULL, wait, (void *)i);
        if (rc)
        {
            cout << "Failed  to creatre thread" << endl;
            exit(-1);
        }
        cout << "Completed thread id: " << i <<endl;
    }

    pthread_attr_destroy(&attr);
    for(i=0; i<5; i++)
    {
        rc = pthread_join(thread[i], &status);
        if(rc)
        {
            cout << "Unable to join"<<endl;
            exit(-1);
        }
        cout <<"Main: completed thread ID: "<< i;
        cout <<" Exiting with status" << status<<endl;
    }

    cout << "MAin Program exiting" <<endl;
    pthread_exit(NULL);
}