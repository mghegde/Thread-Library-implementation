/**************************************************
* Single Author Info
* mghegde Mahendra Hegde
* ssingh24 Siddharth Singh
* skumar23 Sudhendu Kumar
*
* Group Info
* mghegde Mahendra Hegde
* ssingh24 Siddharth Singh
* skumar23 Sudhendu Kumar
***************************************************/

#include "mythread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void *PrintHello(void* arg)
{
   char str[80];
   sprintf(str, "Hello World! It's me, thread #%d \n", *(int*)arg);
   write(2, str, strlen(str));
   mythread_t str2 = mythread_self();
   char str1[80];
   sprintf(str1,"mythread_self() :: self tid %d \n",str2.tid);
   write(2, str1, strlen(str));
   mythread_exit((void *)&(str2.tid));
}

int main(int argc, char *argv[])
{
   if(argc < 2)
   {
	printf("Usage : ./p5 <number of threads> . Please see the README file for more\n");
        return FAILURE;
   }
   int NUM_THREADS = atoi(argv[1]);
   int thread_count[NUM_THREADS];
   mythread_t threads[NUM_THREADS];
   int rc;
   int retVal = 555;
   int *pRetVal = &retVal;
   int i;
   for (i = 0; i<NUM_THREADS; i++)
   {
        thread_count[i] = i;
        printf("mythread_create() :: Createing thread number : %d\n", i);
   	rc = mythread_create(&threads[i], NULL, PrintHello, (void *)&thread_count[i]);
     	if (rc){
       		printf("ERROR; return code from pthread_create() is %d\n", rc);
       		return FAILURE;
        }
   }
   sleep(1);
   mythread_join(threads[NUM_THREADS - 1], (void **)&pRetVal);
   printf("\nReturn Value from Thread is its TID :: %d\n\n",*(int*)pRetVal);
   printf("\n-----------------------------------------\n");
   printf("Test Run with mythread_attr_setstack, mythread_attr_getstack, mythread_attr_init, mythread_attr_destroy, mythread_attr_getstacksize, mythread_attr_setstacksize\n");
   printf("-----------------------------------------\n");
   void *mem = malloc(sizeof(char)*5000);
   void *mem1;
   size_t size1;
   mythread_attr_t attr,attr1;
   int size = 5000*sizeof(char);

   mythread_attr_init(&attr);
   printf("mythread_init() : Thread initialized with stacksize %d and base NULL\n\n",attr.stacksize);

   mythread_attr_setstack(&attr,mem,size);
   printf("mythread_attr_setstack() : Thread initialized with base %p size %d\n\n",attr.stackbase, attr.stacksize);

   int token = 999; 
   rc = mythread_create(&threads[i], &attr, PrintHello, &token);
   if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       return FAILURE;
   }
   mythread_attr_getstack(&attr,&mem,&size1);
   printf("mythread_attr_getstack() : Thread Size %d and base %p\n\n",size1, mem);

   mythread_attr_getstacksize(&attr,&size1);
   printf("mythread_attr_getstacksize() : Thread Size %d\n\n",size1);


   mythread_attr_destroy(&attr);
   printf("mythread_attr_destroy() : All attributes back to initialized value Size %d and base %p\n",attr.stacksize, attr.stackbase);

   return SUCCESS;
}
