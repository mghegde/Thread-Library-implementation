/***************************************************
* Single Author Info
* mghegde Mahendra Hegde
*
* Group Info
* mghegde Mahendra Hegde
* ssingh24 Siddharth Singh
* skumar23 Sudhendu Kumar
***************************************************/


#include<stdio.h>
#include "mymutex.h"


int mythread_mutex_init(mythread_mutex_t * mutex,
              const mythread_mutexattr_t *attr) {
 
   	*mutex = (mythread_mutex_t) malloc(sizeof(struct mythread_mutex));	
   	(*mutex)->lock =0;
   	(*mutex)->head=NULL;
        return 0;
}


int mythread_mutex_lock(mythread_mutex_t *mutex) {

   	return Test_Test_and_Set(mutex);

}


int mythread_mutex_unlock(mythread_mutex_t *mutex) {
   	//mythread_enter_kernel();
  	//(*mutex)->lock=0;

         
     /*** Release the lock from the current thread And unblock the process which is waiting in the head of the que ***/	
  	if ((*mutex)->head != NULL ) {
		mythread_enter_kernel();
                (*mutex)->lock=0;
  		mythread_unblock(&(*mutex)->head, 1);  
  	} else {
	    (*mutex)->lock=0;
	}

//  	mythread_leave_kernel();
	return 0;
}

int mythread_mutex_destroy(mythread_mutex_t *mutex) {
  /*** Release the mutex and set the value to NULL ***/
	free(*mutex) ;
	*mutex = NULL;

	return 0;
}
