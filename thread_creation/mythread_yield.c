
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

#define READY 1
#define RUNNING 2
#define FINISHED 3
#define WAIT 4

int mythread_yield()
{

   int ret = 0;
   mythread_t self = mythread_self();
   //Searched for tnode in  TCB queue
   List *tcb_node = searchList(self.tid);
   if ( tcb_node == NULL ) {
      return 1;
   }
   tcb_node->thread_struct->state = WAIT;
   //Searched for tnode successfully

   List *next_node = tcb_node->next;

   if ( next_node == NULL ) {
     // If this is the only thread in queue. Do not yield.
      return 0;
   } else {
      //Move this thread's TCB to back of queue so it can be resumed by the scheduler by doing a futex up once the thread is reached.
      ret = moveElementBack(tcb_node);
      if (ret == FAILURE) {
         //Move to back of queue failed, so return without yieding
         return FAILURE;
      } else {
         //Call futex down and suspends itself
         futex_down(&(tcb_node->thread_struct->futex));
      }
   }
   return SUCCESS;
}
