CC=gcc
CFLAGS=-Wall -ansi -pedantic -g 


assembler: assembler.c assembler.h error.h assembler_logging.o assembler_tables.o
	$(CC) $(CFLAGS) assembler_logging.o assembler_tables.o assembler.c -o assembler

assembler_logging: assembler_logging.c assembler.h
	$(CC) -c $(CFLAGS) assembler_logging.c -o assembler_logging.o

assembler_tables: assembler_tables.c assembler.h
	$(CC) -c $(CFLAGS) assembler_tables.c -o assembler_tables.o

clean:
	rm -f ./*.o *~ a.out assembler

