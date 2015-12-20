
#include "./mythread.h"

typedef struct mythread_lst {
   mythread_t *thread_struct;
   struct mythread_lst* next;
   struct mythread_lst* prev;
} List;


//struct mythread_t;
//struct mythread_lst ;
//List *head;

void addElement(mythread_t *Ele);
int removeElement();
List * searchList(pid_t tid);
void removeProcessedNode(List * ptr);
int moveElementBack(List* ptr);

