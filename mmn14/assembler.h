#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "error.h"

#define MIN_NUMBER_OF_ARGS 2 /* includes the command itself */
#define MAX_MESSAGE_SIZE 50
#define NUM_OF_OPCODE 16
#define MAX_BUFER_LENGTH 50
#define LINE "--------------------------------------------------"

typedef enum {CODE, DATA} symbol_type;
typedef enum {ENTRY, EXTERNAL, NONE=0} symbol_location;


/* opcode struct definition */
typedef struct opcode {
	int value;
	char * name;
	} opcode;

/* symbot struct definition */
typedef struct symbol {
	char * name;
	int value;
	symbol_type type;
	symbol_location location;
	struct symbol * next;
	} symbol;
	


/* function prototype */
void _message(char [],char []);
void _WARNING(char []);
void _ERROR(char []);
void _DEBUG(char []);
int add_to_symbol_table(char *, int, symbol_type, symbol_location);
void print_symbol_table();
void free_symbol_table();


/* opcodes_table declaration */
opcode opcodes_table[NUM_OF_OPCODE];

/* symbol table declaration */
symbol * symbol_table;
