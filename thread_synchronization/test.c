#include<stdio.h>
#include "mythread.h"
#include "mymutex.h"

mythread_mutex_t myL;

int x=0;
mythread_queue_t head=NULL;
void * Hello(void * arg) {
  mythread_mutex_lock(&myL ); 

    sleep(2);
    mythread_enter_kernel();
    printf("Inside Lock . Thread Number %d\n", *(int *)arg);
    mythread_leave_kernel();


    ++*(int *)arg;

//   mythread_leave_kernel();
   mythread_mutex_unlock(&myL );
}

int main() {
 int i;
  mythread_mutex_init(&myL,NULL);
 // printf("Mutex lock after init === %d \n", myL->lock);
  mythread_t threads[10];
  int m=1;
  for ( i=0;i<10;i++)
  	mythread_create(&threads[i], NULL,Hello,&m);

//  printf("Thread Creation Done :) \n");

  for (i=0; i<10;i++)
      mythread_join(threads[i],NULL);

  mythread_mutex_destroy(&myL);

  if (myL == NULL ) {
	printf("Destroy successfull\n");
  }
printf("Exiting Main\n");
}
