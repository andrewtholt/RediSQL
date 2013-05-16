

CC = gcc
CFLAGS = -g 
BINS=RediSQL

all:	$(BINS)

RediSql:	RediSQL.c
	$(CC) $(CFLAGS) RediSQL.c -o RediSQL

clean:
	rm -f *.o $(BINS)
