CC=gcc
CFLAGS=-Wall -ansi -pedantic -g 


myset: myset.c set.o set_utils.o set.h
	$(CC) $(CFLAGS) set.o set_utils.o myset.c -o myset

set.o: set.c set.h
	$(CC) -c $(CFLAGS) set.c -o set.o

set_utils.o: set_utils.c set.h
	$(CC) -c $(CFLAGS) set_utils.c -o set_utils.o	

clean:
	rm -f ./*.o *~ a.out myset

