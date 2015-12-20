/***************************************************
 * * Single Author Info
 * * skumar23 Sudhendu Kumar
 * *
 * * Group Info
 * * mghegde Mahendra Hegde
 * * ssingh24 Siddharth Singh
 * * skumar23 Sudhendu Kumar
 * ***************************************************/

#include "mythread.h"
#include "mymutex.h"

typedef struct mythread_cond {
        int condInt;
	mythread_queue_t head;
} *mythread_cond_t;

typedef struct mythread_cond mythread_condattr_t;

int mythread_cond_init(mythread_cond_t *cond, const mythread_condattr_t *attr);
int mythread_cond_destroy(mythread_cond_t *cond);
int mythread_cond_wait(mythread_cond_t *cond, mythread_mutex_t *mutex);
int mythread_cond_broadcast(mythread_cond_t *cond);
int mythread_cond_signal(mythread_cond_t *cond);
