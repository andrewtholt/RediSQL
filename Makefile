

CC = gcc
CLAGS = -g 
BINS=RediSQL

all:	$(BINS)

RediSql:	RediSQL.c
	$(CC) $(CLAGS) RediSQL.c -o RediSQL

clean:
	rm -f *.o $(BINS)
