#**************************************************
# Single Author Info
# skumar23 Sudhendu Kumar
#
# Group Info
# mghegde Mahendra Hegde
# ssingh24 Siddharth Singh
# skumar23 Sudhendu Kumar
#**************************************************/

EXECUTABLE    := mytest
CC            := gcc
INCLUDES      += -I. -I/ncsu/gcc346/include/c++/ -I/ncsu/gcc346/include/c++/3.4.6/backward 
LIBSTATIC     := -L/ncsu/gcc346/lib -L.
ARCHIVER_ARG  := rcs
DEBUG_FLAGS   := -v -g
COMPILE_FLAGS := -c
OBJECT_FLAGS  := -lm  -o
STATICLIB     := mysync
TEST_FILE     := mytest.c
SOURCE        := mysched.c myqueue.c 

#mysched.o : mysched.c
#	$(CC) $(COMPILE_FLAGS) mythread.a mysched.c

#myqueue.o : myqueue.c
#	$(CC) $(COMPILE_FLAGS) myqueue.c

all :
	$(CC) $(TEST_FILE) $(SOURCE) $(OBJECT_FLAGS) $(EXECUTABLE) mythread.a 

clean:
	rm -f $(EXECUTABLE) lib$(STATICLIB).a *.o

