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

int mythread_attr_destroy(mythread_attr_t *attr)
{
	attr->stacksize = -1;
        attr->stackbase = NULL;
	return 0;
}
