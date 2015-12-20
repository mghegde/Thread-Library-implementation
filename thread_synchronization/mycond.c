/***************************************************
 * * Single Author Info
 * * skumar23 Sudhendu Kumar
 * *
 * * Group Info
 * * mghegde Mahendra Hegde
 * * ssingh24 Siddharth Singh
 * * skumar23 Sudhendu Kumar
 * ***************************************************/

#include "mycond.h"

int mythread_cond_init(mythread_cond_t *cond, const mythread_condattr_t *attr)
{
	if(attr != NULL)
	{
		write(1,"WARNING : Supports only default attributes.\n",50);
		write(1,"WARNING : Ignoring Thread attributes from user.\n",50);
		attr=NULL;
	}
        //Initialize cond parameters with values
	*cond = (mythread_cond_t) malloc (sizeof(struct mythread_cond));
        (*cond)->condInt = 0;
        (*cond)->head = NULL;
	return SUCCESS;
}

int mythread_cond_destroy(mythread_cond_t *cond)
{
	//Set the cond parameters to -1 and NULL`
        (*cond)->condInt = -1;
        mythread_enter_kernel();
        free((*cond)->head);
        (*cond)->head = NULL;
        free(*cond);
        mythread_leave_kernel();
	return SUCCESS;
}

int mythread_cond_wait(mythread_cond_t *cond, mythread_mutex_t *mutex)
{
        mythread_enter_kernel();
        (*cond)->condInt = 1;
        //Block Phase1
        mythread_block_phase1(&((*cond)->head),1);
	mythread_mutex_unlock(mutex);
        //Check if any signal is received, else go to suspend
   	if((*cond)->condInt == 1)
        {
           mythread_enter_kernel();
           mythread_block_phase2();
	}
	//gain mutex on reciept of signal
   	Test_Test_and_Set(mutex);
        return SUCCESS;
}

int mythread_cond_broadcast(mythread_cond_t *cond)
{
        //unblock all the threads one by one
        while(NULL != (*cond)->head)
        {
        	mythread_enter_kernel();
                (*cond)->condInt = 0;
        	mythread_unblock(&((*cond)->head),1);
        }
	return SUCCESS;
}

int mythread_cond_signal(mythread_cond_t *cond)
{
        //Unblock only the first thread structure
        mythread_enter_kernel();
        (*cond)->condInt = 0;
        mythread_unblock(&((*cond)->head),1);
	return SUCCESS;
}

