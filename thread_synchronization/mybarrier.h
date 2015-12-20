/***************************************************
 * * Single Author Info
 * * ssingh24 Siddharth Singh
 * *
 * * Group Info
 * * mghegde Mahendra Hegde
 * * ssingh24 Siddharth Singh
 * * skumar23 Sudhendu Kumar
 * ***************************************************/


#include "mythread.h"
#include <pthread.h>
#include "mycond.h"

//Sid: Structure to hold barrier attributres
typedef struct mythread_barrierattr{
        char value;
} mythread_barrierattr_t;

//Sid: Barrier Structure
typedef struct mythread_barrier {
    mythread_mutex_t lock;
    mythread_cond_t cond;
    int total_count;
    int current_count;
    mythread_barrierattr_t* attr;
} mythread_barrier_t;

/*Sid: init will initialize the condition value to number of threads to wait for as provided by count. Set the barrier_q to NULL
*/
int mythread_barrier_init(mythread_barrier_t *barrier, const mythread_barrierattr_t *attr, unsigned count);

/*Sid: Will suspend the thread to wait for all the threads to finish. It will check if the value has been set to number of threads and then resume function.
 */
int mythread_barrier_wait(mythread_barrier_t *barrier);

/*Sid: Releases the memory allocated to barrier
 */
int mythread_barrier_destroy(mythread_barrier_t *barrier);
