/***************************************************
* Single Author Info
* ssingh24 Siddharth Singh
*
* Group Info
* mghegde Mahendra Hegde
* ssingh24 Siddharth Singh
* skumar23 Sudhendu Kumar
***************************************************/

#include "./mythread.h"
#include "./myqueue.h"
#include <sys/wait.h>
#include <stdlib.h>

#define READY 1
#define RUNNING 2
#define FINISHED 3
#define WAIT 4

int mythread_join(mythread_t target_thread, void **retVal)
{
    int wait_ret=0;
    int target_stat=0;
    //wait for thread tid to finish
    wait_ret = waitpid(target_thread.tid, &target_stat, 0);
    if (wait_ret > 0) {
       if (WIFEXITED(target_stat)) {
          //Get the TCB node in the queue
          List* tcb_node = searchList(target_thread.tid);
          if (retVal != NULL){
          //Set and return the retval from TCB Node in the parameter
             *retVal = tcb_node->thread_struct->returnValue;
          } 
       }
       return SUCCESS;
    }
    return FAILURE;
}
