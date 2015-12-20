/***************************************************
* Single Author Info
* skumar23 Sudhendu Kumar
* mghegde Mahendra Hegde
*
* Group Info
* mghegde Mahendra Hegde
* ssingh24 Siddharth Singh
* skumar23 Sudhendu Kumar
***************************************************/

#include "./mythread.h"
#include<signal.h>
#include "./futex.h"


//futex_init(&f,1);

int mythread_attr_setstack(mythread_attr_t *attr,
                           void *stackaddr,
                           size_t stacksize) {
   if (stacksize <= 2*sizeof(sigset_t)) {
     /*Stack size is too small. So setting minimum 2048 bytes as stack size */
      attr->stacksize = SIGSTKSZ ;
   } else {
      attr->stacksize = stacksize ;
   }
   attr->stackbase = stackaddr ;
   return SUCCESS;
}


int mythread_attr_getstack(const mythread_attr_t *attr,
                           void **stackaddr,
                           size_t *stacksize) {
 *stackaddr = attr->stackbase;
 *stacksize = attr->stacksize;
 return SUCCESS;
}
