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

mythread_t mythread_self(void)
{
        List *ptr;
        pid_t threadId = gettid();
        ptr = searchList(threadId);
        return * (ptr->thread_struct);
}

