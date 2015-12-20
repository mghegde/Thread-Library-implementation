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
#include <stdio.h>
#include <stdlib.h>

int mythread_attr_getstacksize(const mythread_attr_t *attr,
                               size_t *stacksize)
{
   stacksize = (size_t*) &attr->stacksize;
   return SUCCESS;  
}

int mythread_attr_setstacksize(mythread_attr_t *attr, size_t stacksize)
{
  attr->stacksize = stacksize;
  return SUCCESS; 
}
