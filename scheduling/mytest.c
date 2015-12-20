/***************************************************
 * * Single Author Info
 * * ssingh24 Siddharth Singh
 * *
 * * Group Info
 * * mghegde Mahendra Hegde
 * * ssingh24 Siddharth Singh
 * * skumar23 Sudhendu Kumar
 * ***************************************************/

#include <stdio.h> 
#include <stdlib.h>
#include "./mythread.h"
#include "./mymutex.h"
#define NUM_THREADS 10
long int COUNTER = 500000000;

int global_value = 0;
mythread_mutex_t lock;

void *thread1() {
   long int value = 0;
   while(value<COUNTER) {
      value++;
   }
   mythread_mutex_lock(&lock);
   if (value == COUNTER)
   global_value++;
   mythread_mutex_unlock(&lock);
   
}

int main() {
    mythread_mutex_init(&lock, NULL);
    mythread_t threads[NUM_THREADS];
    int ret,i;
    void *res;
	mythread_setconcurrency(4);
	for (i=0; i<NUM_THREADS ; i++ ) {
    		ret=mythread_create(&threads[i],NULL,&thread1,NULL);
 	}

      sleep(1); //Wait for all threads to create properly
    for (i=0; i<NUM_THREADS;i++) {
    	mythread_join(threads[i],NULL);
    }
    if (global_value == (NUM_THREADS)) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
    return 1;
}

