/***************************************************
 * * Single Author Info
 * * mghegde Mahendra Hegde
 * *
 * * Group Info
 * * mghegde Mahendra Hegde
 * * ssingh24 Siddharth Singh
 * * skumar23 Sudhendu Kumar
 * ***************************************************/

#include <stdio.h>
#include "mythread.h"
#include "mymutex.h"
int Test_Test_and_Set(mythread_mutex_t *object) {

   /***  Test and Set PHASE 1  ***/
   /***  Check the lock status automically. If the lock is held by another thread, block the current thread. 
         If the lock is free access the Critical section  ***/

	if (compare_and_swap(&((*object)->lock),1,0)) {
                 //mythread_enter_kernel();
   		if ((*object)->head != NULL) {

                        mythread_enter_kernel();
			mythread_block(&((*object)->head),0);
   		}
		
                 //mythread_leave_kernel();		 
	} else {
		 return 0;
	}


    /***  Test and Set Phase 2 ***/
    /*** Wait max 50 times in busy wait state if the lock is not available. If the lock is not available even after the 50 retries block the process till somebody releases it.***/

	int count =0;
	while (compare_and_swap(&((*object)->lock),1,0)) {

      		if (count < 50) {	
        		count++;
      		} else {
			mythread_enter_kernel();
	 		mythread_block(&((*object)->head),0);
			
      		}
               
	}

	
        
         //mythread_leave_kernel();
	return 0;
 
}
