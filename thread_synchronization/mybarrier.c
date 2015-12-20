/***************************************************
 * * Single Author Info
 * * ssingh24 Siddharth Singh
 * *
 * * Group Info
 * * mghegde Mahendra Hegde
 * * ssingh24 Siddharth Singh
 * * skumar23 Sudhendu Kumar
 * ***************************************************/

#include "mybarrier.h"

int mythread_barrier_init(mythread_barrier_t *barrier, const mythread_barrierattr_t *attr, unsigned count) {
    int count1 = (unsigned int)count;
    /*Sid:Initialize the barrier count with the number of threads to wait on 
     *    
     */
    if (barrier != NULL && count1 > 0) {
       mythread_mutex_init(&barrier->lock, NULL);
       mythread_cond_init(&barrier->cond,NULL);
       barrier->total_count = count1;
       barrier->current_count = 0;
       return SUCCESS;
    }

    return FAILURE;
}

int mythread_barrier_wait(mythread_barrier_t *barrier) {
    if (barrier != NULL) {
       /*Sid: Increase barrier value by 1 indicating this thread has reached the barrier location.
        *     Put these transactions in mutex lock so that the wrong value of count is not used
        */
       mythread_mutex_lock(&barrier->lock);
       barrier->current_count+=1;
       /*Sid: Check barrier value if it is still less than the total number of threads to call barrier
        *     wait on a conditional variable, else if this is the last thread to hit the barrier
        *     Do not put the thread to wait on condition, instead increment the value of count and broadcast to waiting threads to wake up.
        */
       while (barrier->current_count < barrier->total_count) {
           int retur = mythread_cond_wait(&barrier->cond, &barrier->lock);
       }
       if (barrier->current_count == barrier->total_count){
          barrier->current_count++ ;
          mythread_cond_broadcast(&barrier->cond);
       }

       //Sid: Release lock on transactions
       mythread_mutex_unlock(&barrier->lock);

       return SUCCESS;
    }
    
    return FAILURE;
}

int mythread_barrier_destroy(mythread_barrier_t *barrier) {
    if (barrier != NULL) {
       mythread_mutex_destroy(&barrier->lock);
       mythread_cond_destroy(&barrier->cond);
       //Sid: Reinitialize barrier with 0
       barrier->total_count = 0;
       barrier->current_count = 0;
       return SUCCESS;
    }

    return FAILURE;
}
