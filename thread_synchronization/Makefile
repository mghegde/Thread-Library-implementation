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
OBJECT_FLAGS  := -o
STATICLIB     := mysync
TEST_FILE     := mytest
OBJECTS       := mybarrier.o mycond.o mymutex.o test_and_set.o

mybarrier.o : mybarrier.c
	$(CC) $(COMPILE_FLAGS) mybarrier.c

test_and_set.o : test_and_set.c
	$(CC) $(COMPILE_FLAGS) test_and_set.c

mycond.o : mycond.c
	$(CC) $(COMPILE_FLAGS) mycond.c

mymutex.o : mymutex.c
	$(CC) $(COMPILE_FLAGS) mymutex.c

library: $(OBJECTS)
	ar $(ARCHIVER_ARG) lib$(STATICLIB).a $(OBJECTS)

binary:
	$(CC) $(TEST_FILE).c -o $(EXECUTABLE) $(OBJECTS) mythread.a libmysync.a

clean:
	rm -f $(EXECUTABLE) lib$(STATICLIB).a *.o

