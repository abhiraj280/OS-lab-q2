#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

int avail = 5;
sem_t sema;

void * first(void *) {
    int q;
    sem_getvalue(&sema, &q);
    cout << "Semaphore F1 = " << q << endl << endl;
    while (q <= 0)
        ;

    cout << "Lock on semaphore" << endl
         << endl;
    sem_wait(&sema);
    avail++;
    sleep(2);
    sem_post(&sema);
    cout << "Lock released" << endl;
    cout << "Current value of avail is " << avail << endl;
}

void * second(void *) {
    int p;
    sem_getvalue(&sema, &p);
    cout << "Semaphore F2 = " << p << endl << endl;
    while (p <= 0)
        ;
    cout << "Lock on semaphore" << endl
         << endl;
    sem_wait(&sema);
    avail--;
    sleep(2);
    sem_post(&sema);
    cout << "Lock released" << endl;
    cout << "Current value of avail is " << avail << endl;

}
int32_t main() {
    pthread_t thread1, thread2;
    sem_init( & sema, 0, 1);

    int i = 3;
    while (i--)
    {
        pthread_create( & thread1, NULL, first, NULL);
        pthread_create( & thread2, NULL, second, NULL);
        sleep(5);
        cout << endl
             << "Loop = " << i << endl
             << endl;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    cout << "Current value of avail = " << avail << endl;

    return 0;
}
