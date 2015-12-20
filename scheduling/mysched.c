/***************************************************
 * * Author info/Group Info. 
 * * mghegde Mahendra Hegde
 * * ssingh24 Siddharth Singh
 * * skumar23 Sudhendu Kumar
 * ***************************************************/

#include <signal.h>
#include <stdlib.h>
#include "mythread.h"
#include "myqueue.h"
#include <string.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <math.h>
#include "mymutex.h"

#define SUCCESS 0
int gcount=1;

mythread_mutex_t _lock;

void mythread_init_sched(void);
void mythread_exit_sched(void);
void mythread_leave_kernel(void);


int scheduler(mythread_t thread) {
    int duration;
    mythread_t readyThread;
    mythread_queue_t  *readyQ = mythread_readyq();
    mythread_queue_t  *runQ = mythread_runq();

    /*Sid:Get the number of preemptions of the thread*/
    int preemptions = thread->preemptions;

    /*Sid:Get the current time. Calculate time passed since the process has been running*/
    duration = thread->attr.attr;
    /*Sid:Check the current time of thread with the 2^preemption. If crossed time Remove the thread from runQ and place it on ReadyQ.*/
    if (duration > pow(2, preemptions)) {
       /*Sid: Check if readyQ has someone waiting to be brought in to Run*/
       if (mythread_readyq() != NULL && mythread_lenq(mythread_readyq()) == 0){
          
          /*Sid:Reset current threads duration to 0 and keep running till the next time slice*/
          mythread_mutex_lock(&_lock);
          thread->attr.attr=0;
          mythread_mutex_unlock(&_lock);
       } else if(thread->reschedule != 1){
          /*Sid:Set the current thread's duration to 0. Increment its preemption value*/
          mythread_mutex_lock(&_lock);
          thread->attr.attr=0;
          /*Sid: If thread has not been preempted more than 10 times increment preemption count by 1*/
          if (thread->preemptions < 10) {
              thread->preemptions++;
          } 
          /*Sid:Get the item in the head of the ReadyQueue and bring it to the runQ and dequeue from ReadyQueue.*/
          readyThread = (mythread_t)((*readyQ)->item);
          readyThread->attr.attr = 0;
          mythread_mutex_unlock(&_lock);
          
          /*Sid: unblock the new thread and block the current thread*/
          mythread_block(mythread_readyq(), 1);
       }
    }

	return SUCCESS;
}


void sigusrhandler()
{
        /*Handler Code for SIGUSR1*/
	mythread_t thread_id = mythread_self();

        mythread_mutex_lock(&_lock);
	thread_id->attr.attr++;
        mythread_mutex_unlock(&_lock);

	scheduler(mythread_self());

}


void sigalarmhandler()
{
        /*Handler Code for SIGALRM*/
	mythread_t thread_id = mythread_self();

	mythread_queue_t *runQ = mythread_runq();

	mythread_queue_t *runQ1 = runQ;

	do {

		if (((mythread_t)((*runQ1)->item))->tid == mythread_self()->tid)
		{
			*runQ1 =(*runQ1)->next;
			continue;

		}
 
                pid_t pid = ((mythread_t)((*runQ1)->item))->tid;
                *runQ1 =(*runQ1)->next;
	

		if(kill(pid, SIGUSR1) == -1 ) {
			printf("SIGUSER1 SEND Failed \n");
		}

	} while (*runQ1 != *runQ) ;
	int status = FALSE;

	while(status == FALSE)
        {       
                status = mythread_tryenter_kernel();
                
                if(status == FALSE)
                {       
                        mythread_self()->reschedule = 1;

		}
	}

	scheduler(mythread_self());
	mythread_leave_kernel();
}

void signal_handler() {

	struct itimerval timer;
	struct sigaction actions, action1;

        /*Register threads for SIGALRM */
       memset(&actions, 0, sizeof(actions));
       sigemptyset(&actions.sa_mask);
       actions.sa_flags = 0;
       sigaddset (&actions.sa_mask, SIGALRM);
       sigprocmask(SIG_UNBLOCK, &actions.sa_mask, NULL);
       actions.sa_handler = sigalarmhandler;
       sigaction(SIGALRM,&actions,NULL);

      /*Register the threads to receive SIGUSR*/

       memset(&action1, 0, sizeof(action1));
       sigemptyset(&action1.sa_mask);
       action1.sa_flags = 0;
       action1.sa_handler = sigusrhandler;
       sigaddset (&action1.sa_mask, SIGUSR1);
       sigprocmask(SIG_UNBLOCK, &action1.sa_mask, NULL);
       sigaction(SIGUSR1,&action1,NULL);

        /* Start Settitimer and send timeout signals for every x seconds */

	if (gcount == 1) {
         mythread_mutex_init(&_lock, NULL);
        /* Configure the timer to expire after 1 msec... */
         timer.it_value.tv_sec = 0;
         timer.it_value.tv_usec = 1000;
        /* ... and every 1 msec after that. */
         timer.it_interval.tv_sec = 0;
         timer.it_interval.tv_usec = 1000;

        /* Start a virtual timer. It counts down whenever this process is
          executing. */

         setitimer (ITIMER_REAL, &timer, NULL);
	 gcount++;
	}
}

void mythread_init_sched(void)
{

	/* Enter the monolitic kernel */

	signal_handler();	
     
}

void mythread_exit_sched(void)
{
        /* Reset Handlers upon exiting scheduler */
	if((mythread_lenq(mythread_readyq()) == 0) && mythread_lenq(mythread_runq()))
        {
		sigaction(SIGALRM, (void*)SIG_DFL, NULL);
		sigaction(SIGUSR1, (void*)SIG_DFL, NULL);
        }
}

void mythread_leave_kernel(void)
{
   /* Leave the Kernel */
   mythread_queue_t *runQ = mythread_runq();
   mythread_queue_t *runQ1 = runQ;

  do {
	  if (((mythread_t)((*runQ1)->item))->reschedule == 1)
  	{
      		((mythread_t)((*runQ1)->item))->reschedule = 0;
  	} 
      		mythread_leave_kernel_nonpreemptive();
  

	*runQ1 =(*runQ1)->next;

  } while (*runQ1 != *runQ) ;

}
