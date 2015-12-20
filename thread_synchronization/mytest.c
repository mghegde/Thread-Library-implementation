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
#include "./mybarrier.h"
#include "./mythread.h"

int value = 0;
mythread_barrier_t barrier;
mythread_mutex_t lock;
mythread_cond_t condition;

//Sid: Testing mutex lock explicitly in the threads. Value should be updated by a single thread
void *thread1() {
    mythread_mutex_lock(&lock);
    value++;
    mythread_mutex_unlock(&lock);
    mythread_barrier_wait(&barrier);
}


void *thread2() {
    mythread_mutex_lock(&lock);
    value++;
    mythread_mutex_unlock(&lock);
    mythread_barrier_wait(&barrier);
}

void *thread3() {
    mythread_mutex_lock(&lock);
    value++;
    mythread_mutex_unlock(&lock);
    if(mythread_barrier_wait(&barrier) == SUCCESS) {
       printf("Barrier Wait Test: PASSED\n");
    } else {
       printf("Barrier Wait Test: FAILED\n");
    }
}

void *thread4() {
    mythread_mutex_lock(&lock);
    value++;
    mythread_mutex_unlock(&lock);
    mythread_barrier_wait(&barrier);
}

//Sid: Thread signals main to wake up
void *thread5() {
    mythread_mutex_lock(&lock);
    value++;
    if(mythread_cond_signal(&condition) == SUCCESS){
       printf("Condition Signal Test: PASSED\n");
    } else {
       printf("Condition Signal Test: FAILED\n");
    }
    mythread_mutex_unlock(&lock);
}

void *thread6() {
    if (!mythread_mutex_lock(&lock)){
       printf("Mutex Lock Test: PASSED\n");
    } else {
       printf("Mutex Lock Test: FAILED\n");
    }

    while(value<5){
         if (mythread_cond_wait(&condition,&lock)==SUCCESS) {
            printf("Condition Wait Test: PASSED\n");
         } else {
            printf("Condition Wait Test: FAILED\n");
         }
    }
    
    if (value==5){
       printf("Condition Variable Test: PASSED\n");
    } else {
       printf("Condition Variable Test: FAILED\n");
    }
    if (!mythread_mutex_unlock(&lock)) {
       printf("Mutex UnLock Test: PASSED\n");
    } else {
       printf("Mutex UnLock Test: FAILED\n");
    }
}

int main() {

    mythread_t thread_1,thread_2,thread_3,thread_4,thread_5,thread_6;
    int ret;
    void *res;
    mythread_mutex_init(&lock, NULL);
    //Sid:Test Barrier with 4 threads
    if (mythread_barrier_init(&barrier,NULL,4) == SUCCESS){
       printf("Barrier Init Test: PASSED\n");
    } else {
       printf("Barrier Init Test: FAILED\n");
    }
    ret=mythread_create(&thread_1,NULL,&thread1,NULL);
    ret=mythread_create(&thread_2,NULL,&thread2,NULL);
    ret=mythread_create(&thread_3,NULL,&thread3,NULL);
    ret=mythread_create(&thread_4,NULL,&thread4,NULL);

    if (ret!=0) {
     
       printf("Thread Creation: FAILED\n");
    }
    //Sid: After thread create sleep for 2 seconds
    sleep(2);
    mythread_join(thread_1,NULL);
    mythread_join(thread_2,NULL);
    mythread_join(thread_3,NULL);
    if (value == 4) {
       printf("Barrier Test: PASS\n");
    }else{
       printf("Barrier Test: FAIL\n");
    }   
    mythread_join(thread_4,NULL);
    mythread_mutex_destroy(&lock);
    if(mythread_barrier_destroy(&barrier) == SUCCESS) {
       printf("Barrier Destory Test: PASSED\n");
    } else {
       printf("Barrier Destory Test: FAILED\n");
    }
    //Sid:Test Condition Variable
    if (mythread_cond_init(&condition,NULL)==SUCCESS) {
       printf("Cond Init Test: PASSED\n");
    } else {
       printf("Cond Init Test: FAILED\n");
    }
    if(!mythread_mutex_init(&lock,NULL)) {
       printf("Mutex Init Test: PASSED\n");
    } else {
       printf("Mutex Init Test: FAILED\n");
    }
      
    ret = mythread_create(&thread_5,NULL,&thread6,NULL);
    ret = mythread_create(&thread_6,NULL,&thread5,NULL);
    if (ret!=0) {
       printf("Thread Creation: FAILED\n");
    }
    mythread_join(thread_5,NULL);
    mythread_join(thread_6,NULL);
    if (mythread_cond_destroy(&condition) == SUCCESS){
       printf("Condition Variable Destory Test: PASSED\n");
    } else {
       printf("Condition Variable Destory Test: FAILED\n");
    }
    mythread_mutex_destroy(&lock);
    if (lock==NULL){
       printf("Mutex Destroy Test: PASSED\n");
    }else{
       printf("Mutex Destroy Test: FAILED\n");
    }
    return 1;
}

