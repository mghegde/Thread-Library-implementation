/**************************************************
* Single Author Info
* mghegde Mahendra Hegde -- > Created Basic Structure of Queue
* ssingh24 Siddharth Singh --> Added functions searchList and removeProcessedNode and moveElementBack as per project requirement
* skumar23 Sudhendu Kumar --> Fixed Bugs 
*
* Group Info
* mghegde Mahendra Hegde
* ssingh24 Siddharth Singh
* skumar23 Sudhendu Kumar
***************************************************/

#include<stdio.h>
#include<string.h>
#include "./mythread.h"
#include "./myqueue.h"
#include <stdlib.h>


List *head = NULL;
List *startPtr = NULL;
//Adds element to the TCB queue
void addElement(mythread_t *Ele)
{
   List *pLst = (List *)malloc(sizeof(List));
   List * ptr = NULL;
   //memcpy(&(pLst->thread_struct), (const void *)Ele, sizeof(List));
   pLst->thread_struct = Ele ; 
   if (head == NULL)
   {
      head = pLst;
      startPtr = head;
      head->next = head->prev = NULL;
      return ;
   }
   ptr = head;
   while(ptr->next != NULL)
        ptr = ptr->next ;

   ptr->next = pLst;
   pLst->next = NULL;
   pLst->prev = ptr;
}

//Moves head forward in the queue. Note:No removal
int removeElement()
{
    if (head == NULL)
        return -1;

    List *ptr = head;

    if(head->next != NULL)
    {
        head = head->next;
        head->prev = NULL;
    }
    else
    {
	head = NULL;
    }
//    free(ptr);
//    ptr = NULL;
    return 0;
}

//Search for element in TCB queue based on its TID
List * searchList(pid_t tid)
{
    if (startPtr == NULL)
    {
      // mythread_t *dummy = (mythread_t *)malloc(sizeof(mythread_t)) ;
 //	dummy.tid = -1;
       //ToDo:Handle when scheduler is empty
       return startPtr;
    }
    List *ptr = startPtr;

    while (ptr->next != NULL)
    {
          if (ptr->thread_struct->tid == tid)
          {
             return ptr;
          }
	  ptr = ptr->next;
    }

   if (ptr->thread_struct->tid == tid)
    {
         return ptr;
    }
   //ToDo: Handle when search fails
}

//Removes any Node that has been processed from the TCB queue
void removeProcessedNode(List * ptr) {

   if (ptr-> prev == NULL && ptr->next == NULL) {
      ptr = startPtr = NULL;
      free(ptr);
      return;
   }

   if (ptr->prev == NULL) {
       ptr = ptr->next;
       startPtr = ptr;
       free(ptr->prev);
       ptr->prev=NULL;
       return;
   }

   if (ptr->next == NULL) {
      ptr = ptr->prev;
      free(ptr->next);
      ptr->next=NULL;
      return;
   }
   ptr->prev->next = ptr->next;
   ptr->next->prev = ptr->prev;
   free(ptr);
   return;
}

//Moves Node to the end of queue
int moveElementBack (List *ptr) {
    
    if (ptr == NULL) {
       return FAILURE;
    }
    if (ptr->prev == NULL && ptr->next == NULL) {
       return FAILURE;
    }
    List *prevNode = ptr->prev;
    List *nextNode = ptr->next;
    List *current = ptr;
    while (current->next != NULL) {
          current = current->next;
    }
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    ptr->prev = current;
    ptr->next = NULL;
    current->next = ptr;
}
