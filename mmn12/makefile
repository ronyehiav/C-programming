CC=gcc
CFLAGS=-Wall -ansi -pedantic

get_name: get_name.c
	$(CC) -o get_name get_name.c $(CFLAGS)

debug: get_name.c
	$(CC) -g get_name.c

clean:
	rm -f ./*.o *~ a.out get_name

