CC=gcc
CFLAGS=-Wall -ansi -pedantic -g 


hash: hash.c hash_utils.o hash.h
	$(CC) $(CFLAGS) hash_utils.o hash.c -o hash

hash_utils.o: hash_utils.c hash.h
	$(CC) -c $(CFLAGS) hash_utils.c -o hash_utils.o

clean:
	rm -f ./*.o *~ a.out hash

