CC=gcc
CFLAGS=-Wall -ansi -pedantic -g 


assembler: assembler.c assembler.h error.h assembler_logging.o 
	$(CC) $(CFLAGS) assembler_logging.o assembler.c -o assembler

assembler_logging: assembler_logging.c assembler.h
	$(CC) -c $(CFLAGS) assembler_logging.c -o assembler_logging.o

clean:
	rm -f ./*.o *~ a.out assembler

