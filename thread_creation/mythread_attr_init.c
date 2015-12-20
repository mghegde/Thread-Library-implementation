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

int mythread_attr_init(mythread_attr_t *attr)
{
	attr->stacksize = STACK_SIZE;
        attr->stackbase = NULL;
	return 0;
}

