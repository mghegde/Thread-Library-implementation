/***************************************************
* Single Author Info
* skumar23 Sudhendu Kumar
*
* Group Info
* mghegde Mahendra Hegde
* ssingh24 Siddharth Singh
* skumar23 Sudhendu Kumar
***************************************************/

#include "./mythread.h"
#include "./myqueue.h"
#include <unistd.h>
#include <stdlib.h>

void mythread_exit(void *retval)
{
	extern List* head;
        List *ptr = head;
        pid_t threadId = gettid();
	//Search and sets the return value in TCB
        ptr = searchList(threadId);
        ptr->thread_struct->returnValue = retval;
	return;
}

