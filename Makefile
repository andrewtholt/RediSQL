

CC = gcc
CFLAGS = -g 

CPP=g++

LIBS= -lpthread

BINS=tst RediSQL_T # RediSQL

all:	$(BINS)

RediSQL:	RediSQL.c
	$(CC) $(CFLAGS) RediSQL.c -o RediSQL

RediSQL_T.o:	RediSQL_T.cpp
	$(CPP) $(CFLAGS) -c $(LIBS) RediSQL_T.cpp -o RediSQL_T.o

queue.o:	queue.cpp queue.h
	$(CPP) -c $(CFLAGS) queue.cpp -o queue.o

tst:	queue.o tst.cpp
	$(CPP) $(CFLAGS) tst.cpp queue.o -o tst

RediSQL_T:	RediSQL_T.o
	$(CPP) $(CFLAGS) RediSQL_T.o -o RediSQL_T -lpthread

clean:
	rm -f *.o $(BINS)
