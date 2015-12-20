/***************************************************
* Single Author Info
* mghegde Mahendra Hegde
*
* Group Info
* mghegde Mahendra Hegde
* ssingh24 Siddharth Singh
* skumar23 Sudhendu Kumar
***************************************************/


#include <sched.h>
#include <signal.h>
#include <stdlib.h>
#include "./mythread.h"
#include "./myqueue.h"
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include<string.h>
/*
 * mythread_create - prepares context of new_thread_ID as start_func(arg),
 * attr is ignored right now.
 * Threads are activated (run) according to the number of available LWPs
 * or are marked as ready.
 */


extern List * head;
int scheduled =0;

void print (const void *buf, size_t count)
{
   write(1,buf,count);
}

//Wrapper function calls the function pointer specified by the user.
int wrap_fun (void * args) {
   mythread_t *thrd_id =(mythread_t *) args;
   pid_t a =(pid_t)syscall(SYS_gettid);
//Call the user function pointer
   thrd_id->start_func(thrd_id->arg);
   return 1;
}


int thread_sched(void * arg) {
   //Stay in while loop to check if there is anything in thread queue
   while(1) { 
  //Head of queue is NULL means that schedular has not scheduled any thread. Wait for it.
    while(head==NULL);
 
    void *user_stack = NULL;
    int ssize;
    mythread_t * Node =  head->thread_struct;

//Initialize the thread stack attribute given by user
    user_stack = (Node->attr).stackbase;
    if ( (Node->attr).stacksize <=sizeof(sigset_t)) {
             ssize =SIGSTKSZ;
    } else {
             ssize =(Node->attr).stacksize;
    }

    if(user_stack == NULL) {
             user_stack =malloc(ssize);
    }

//Schedule a thread from the list of thread queues 
    head->thread_struct->tid = clone (wrap_fun,(void * )((char *) user_stack + ssize) ,SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM | CLONE_PARENT, (void *) Node);

//Since the thread is scheduled now, forward the head pointer in queue
    removeElement();
   }
    return SUCCESS;     
}

 
     
int mythread_create(mythread_t *new_thread_ID,
                    mythread_attr_t *attr,
                    void * (*start_func)(void *),
                    void *arg) {

//   void *user_stack = malloc(STACK_SIZE);
   //pid_t child_tid;
//   void *user_stack = new char[STACK_SIZE];
//If User has not given attribute details, populate own attribute.
   if (attr == NULL) {
        attr = (mythread_attr_t *) malloc(sizeof(mythread_attr_t));
        mythread_attr_init(attr);
   }


//Initiate the scheduler thread
   if (head == NULL && scheduled ==0) {
      void *user_stack = malloc(STACK_SIZE);
      scheduled=1;
     // printf("Cloen created!!!!!!!!!!!\n");
      //clone (thread_sched,(void * )((char *) user_stack + STACK_SIZE) ,CLONE_FILES | CLONE_FS |CLONE_VM |CLONE_SIGHAND|SIGCHLD ,NULL);
      clone (thread_sched,(void * )((char *) user_stack + STACK_SIZE) ,SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM,NULL); 
   }

//Populate thread attributes into the queue of threads 
   new_thread_ID->start_func = start_func;
   new_thread_ID->arg=arg; 
   new_thread_ID->tid=-999;
   addElement(new_thread_ID);
   memcpy(&new_thread_ID->attr, attr, sizeof(mythread_attr_t));
 
   return SUCCESS;  
}


