/*
 * mythread.h -- interface of user threads library
 */

#ifndef MYTHREAD_H
#define MYTHREAD_H

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#include <sys/types.h>
#include <sys/syscall.h>

//#include "myqueue.h"
#include "futex.h"
#include<signal.h>

#define SUCCESS 0
#define FAILURE -1

#define STACK_SIZE SIGSTKSZ

typedef int mythread_key_t;

typedef struct mythread_attr {    /* thread attributes */
	int stacksize;
        void * stackbase;                  /* stack size in bytes */
} mythread_attr_t;

typedef struct mythread {         /* thread control block */
  pid_t tid;
  void * (*start_func)(void*);    /* thread_func to be called */
  void *arg;                      /* thread_arg arguments of thread_func */
//  mythread_queue_t joinq;         /* Q of threads waiting for my return */
  void *returnValue;              /* Pointer to the detached function's return value */
  struct futex futex;
  int state;                      /* state of execution */
  mythread_attr_t attr;

} mythread_t;

/*
 * mythread_self - thread id of running thread
 */
mythread_t mythread_self(void);

/*
 * mythread_create - prepares context of new_thread_ID as start_func(arg),
 * attr is ignored right now.
 * Threads are activated (run) according to the number of available LWPs
 * or are marked as ready.
 */
int mythread_create(mythread_t *new_thread_ID,
		    mythread_attr_t *attr,
		    void * (*start_func)(void *),
		    void *arg);

/*
 * mythread_yield - switch from running thread to the next ready one
 */
int mythread_yield(void);

/*
 * mythread_join - suspend calling thread if target_thread has not finished,
 * enqueue on the join Q of the target thread, then dispatch ready thread;
 * once target_thread finishes, it activates the calling thread / marks it
 * as ready.
 */
int mythread_join(mythread_t target_thread, void **status);

/*
 * mythread_exit - exit thread, awakes joiners on return
 * from thread_func and dequeue itself from run Q before dispatching run->next
 */
void mythread_exit(void *retval);

int mythread_attr_init(mythread_attr_t *attr);
int mythread_attr_destroy(mythread_attr_t *attr);
int mythread_attr_getstack(const mythread_attr_t *attr,
			   void **stackaddr,
			   size_t *stacksize);
int mythread_attr_setstack(mythread_attr_t *attr, void *stackaddr,
			   size_t stacksize);
int mythread_attr_getstacksize(const mythread_attr_t *attr, 
			       size_t *stacksize);
int mythread_attr_setstacksize(mythread_attr_t *attr, size_t stacksize);

static pid_t gettid(void) {
  return (pid_t) syscall(SYS_gettid);
}

#endif /* MYTHREAD_H */

