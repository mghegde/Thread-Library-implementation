#**************************************************
# Single Author Info
# skumar23 Sudhendu Kumar
#
# Group Info
# mghegde Mahendra Hegde
# ssingh24 Siddharth Singh
# skumar23 Sudhendu Kumar
#**************************************************/

EXECUTABLE    := p5
CC            := gcc
INCLUDES      += -I. -I/ncsu/gcc346/include/c++/ -I/ncsu/gcc346/include/c++/3.4.6/backward 
LIBSTATIC     := -L/ncsu/gcc346/lib -L.
#LIBNCSU       := -L/ncsu/gcc346/lib
ARCHIVER_ARG  := rcs
DEBUG_FLAGS   := -v -g
COMPILE_FLAGS := -c
OBJECT_FLAGS  := -o
STATICLIB     := mythread
TEST_FILE     := p5
OBJECTS       := mythread_exit.o mythread_set_getstk_size.o mythread_create.o mythread_self.o mythread_attr_init.o myqueue.o mythread_yield.o mythread_set_stack.o futex.o mythread_attr_destroy.o mythread_join.o

mythread_yield.o : mythread_yield.c
	$(CC) $(COMPILE_FLAGS) mythread_yield.c

futex.o : futex.c
	$(CC) $(COMPILE_FLAGS) futex.c

mythread_set_stack.o : mythread_set_stack.c
	$(CC) $(COMPILE_FLAGS) mythread_set_stack.c

mythread_attr_destroy.o : mythread_attr_destroy.c
	$(CC) $(COMPILE_FLAGS) mythread_attr_destroy.c

mythread_exit.o : mythread_exit.c
	$(CC) $(COMPILE_FLAGS) mythread_exit.c

mythread_join.o : mythread_join.c
	$(CC) $(COMPILE_FLAGS) mythread_join.c

mythread_set_getstk_size.o : mythread_set_getstk_size.c
	$(CC) $(COMPILE_FLAGS) mythread_set_getstk_size.c

myqueue.o : myqueue.c
	$(CC) $(COMPILE_FLAGS) myqueue.c

mythread_create.o : mythread_create.c
	$(CC) $(COMPILE_FLAGS) mythread_create.c

mythread_self.o : mythread_self.c
	$(CC) $(COMPILE_FLAGS) mythread_self.c

mythread_attr_init.o : mythread_attr_init.c
	$(CC) $(COMPILE_FLAGS) mythread_attr_init.c

library: $(OBJECTS)
	ar $(ARCHIVER_ARG) lib$(STATICLIB).a $(OBJECTS)

binary:
	$(CC) $(TEST_FILE).c -o $(EXECUTABLE) lib$(STATICLIB).a

clean:
	rm -f $(EXECUTABLE) lib$(STATICLIB).a *.o

