CC=gcc
CFLAGS=-Wall -ansi -pedantic

translate: translate.c
	$(CC) -o translate translate.c $(CFLAGS)

debug: translate.c
	$(CC) -g translate.c

clean:
	rm -f ./*.o *~ translate

