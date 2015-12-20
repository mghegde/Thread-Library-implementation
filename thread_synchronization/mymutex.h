/***************************************************
 * * Single Author Info
 * * mghegde Mahendra Hegde
 * *
 * * Group Info
 * * mghegde Mahendra Hegde
 * * ssingh24 Siddharth Singh
 * * skumar23 Sudhendu Kumar
 * ***************************************************/


#include<stdio.h>
#include "mythread.h"

typedef struct mythread_mutex {
  int lock;
  mythread_queue_t head; 
} *mythread_mutex_t; 

typedef struct mythread_mutex mythread_mutexattr_t;


int mythread_mutex_init(mythread_mutex_t * mutex, const mythread_mutexattr_t *attr);

int mythread_mutex_lock(mythread_mutex_t *mutex);

int mythread_mutex_unlock(mythread_mutex_t *mutex);
