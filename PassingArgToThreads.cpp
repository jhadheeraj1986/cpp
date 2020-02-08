#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

struct thread_data
{
    int thread_id;
    char *msg;
};

void *printHello(void *threadarg)
{
    thread_data *my_data = (thread_data *) threadarg;

    cout << "Thread ID: " << my_data->thread_id;
    cout << " Message: " << my_data->msg << endl;

    pthread_exit(NULL);
}

int main()
{
    pthread_t thread[5];
    thread_data td[5];
    int rc, i;

    for (i=0; i<5; i++)
    {
        cout <<"main(): Creating thread, " << i <<endl;
        td[i].thread_id = i;
        td[i].msg = "this is a thread";
        rc = pthread_create(&thread[i], NULL, printHello, (void *)&td[i]);

        if (rc)
        {
            cout << "Error." << rc <<endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

